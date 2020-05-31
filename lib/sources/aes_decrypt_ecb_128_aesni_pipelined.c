#include "tcl.h"

#include "aes_defines.h"
#include <wmmintrin.h> 

// AES 128 ECB decryption. Use pipelined AES instructions. Load key schedule once.

void aes_decrypt_ecb_128_aesni_pipelined(uint8_t* input, uint8_t* output, uint32_t byteLen, uint8_t* keySchedule)
{
    uint32_t nBlocks = byteLen / AES_BLOCK_SIZE;
    uint32_t nPipeRepeat = nBlocks / AES_PIPELINE_SIZE;

    __m128i block0, block1, block2, block3;
    __m128i* in = (__m128i*)input;
    __m128i* out = (__m128i*)output;
    __m128i* w = (__m128i*)keySchedule;
    __m128i roundKeys[NR128 + 1];

    // Load key schedule from memory. 
    // In best case, all key schedule blocks will not be removed from registers during function execution.
    roundKeys[0] = _mm_loadu_si128(&w[NR128]);

    for (uint32_t round = 1; round < NR128; round++)
    {
        // Translate key scedule from nornal form
        // to equivalent inverse cipher form
        // using invMixColumns transformation.
        roundKeys[round] = _mm_aesimc_si128(_mm_loadu_si128(&w[NR128 - round]));
    }
    
    roundKeys[NR128] = _mm_loadu_si128(&w[0]);

    // Decrypt 4 blocks together using pipeline.
    for(uint32_t i=0; i < nPipeRepeat; i++)
    {
        block0 = _mm_loadu_si128(&in[i * AES_PIPELINE_SIZE + 0]);
        block1 = _mm_loadu_si128(&in[i * AES_PIPELINE_SIZE + 1]);
        block2 = _mm_loadu_si128(&in[i * AES_PIPELINE_SIZE + 2]);
        block3 = _mm_loadu_si128(&in[i * AES_PIPELINE_SIZE + 3]);

        block0 = _mm_xor_si128(block0, roundKeys[0]);
        block1 = _mm_xor_si128(block1, roundKeys[0]);
        block2 = _mm_xor_si128(block2, roundKeys[0]);
        block3 = _mm_xor_si128(block3, roundKeys[0]);

        for (uint32_t round = 1; round < NR128; round++)
        {
            block0 = _mm_aesdec_si128(block0, roundKeys[round]);
            block1 = _mm_aesdec_si128(block1, roundKeys[round]);
            block2 = _mm_aesdec_si128(block2, roundKeys[round]);
            block3 = _mm_aesdec_si128(block3, roundKeys[round]);
        }
        
        block0 = _mm_aesdeclast_si128(block0, roundKeys[NR128]);
        block1 = _mm_aesdeclast_si128(block1, roundKeys[NR128]);
        block2 = _mm_aesdeclast_si128(block2, roundKeys[NR128]);
        block3 = _mm_aesdeclast_si128(block3, roundKeys[NR128]);
        
        _mm_storeu_si128(&out[i * AES_PIPELINE_SIZE + 0], block0);
        _mm_storeu_si128(&out[i * AES_PIPELINE_SIZE + 1], block1);
        _mm_storeu_si128(&out[i * AES_PIPELINE_SIZE + 2], block2);
        _mm_storeu_si128(&out[i * AES_PIPELINE_SIZE + 3], block3);
    }

    // Encrypt tail.
    for(uint32_t i=nPipeRepeat * AES_PIPELINE_SIZE; i < nBlocks; i++)
    {
        block0 = _mm_loadu_si128(&in[i]);
        block0 = _mm_xor_si128(block0, roundKeys[0]);

        for (uint32_t round = 1; round < NR128; round++)
        {
            block0 = _mm_aesdec_si128(block0, roundKeys[round]);
        }
        
        block0 = _mm_aesdeclast_si128(block0, roundKeys[NR128]);
        _mm_storeu_si128(&out[i], block0);
    }
}
