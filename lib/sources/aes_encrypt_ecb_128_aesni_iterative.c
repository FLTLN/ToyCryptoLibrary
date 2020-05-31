#include "tcl.h"

#include "aes_defines.h"
#include <wmmintrin.h> 

void aes_encrypt_ecb_128_aesni_iterative(uint8_t* input, uint8_t* output, uint32_t byteLen, uint8_t* keySchedule)
{
    uint32_t nBlocks = byteLen / AES_BLOCK_SIZE;

    __m128i block;
    __m128i* in = (__m128i*)input;
    __m128i* out = (__m128i*)output;
    __m128i* w = (__m128i*)keySchedule;
    __m128i roundKey;

    for(uint32_t i=0; i < nBlocks; i++)
    {
        roundKey = _mm_loadu_si128(&w[0]);
        block = _mm_loadu_si128(&in[i]);
        block = _mm_xor_si128(block, roundKey);

        for (uint32_t round = 1; round < NR128; round++)
        {
            roundKey = _mm_loadu_si128(&w[round]);
            block = _mm_aesenc_si128(block, roundKey);
        }
        
        roundKey = _mm_loadu_si128(&w[NR128]);
        block = _mm_aesenclast_si128(block, roundKey);
        _mm_storeu_si128(&out[i], block);
    }
}
