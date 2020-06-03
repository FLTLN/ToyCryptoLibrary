#include "tcl.h"

#include "aes_defines.h"
#include "aes_routine_noop.h"
#include "aes_lookup_tables.h"

// AES 128 ECB decryption. No optimizations.

void aes_decrypt_ecb_128_noop(uint8_t* input, uint8_t* output, uint32_t byteLen, uint8_t* keySchedule)
{
    return;
    uint32_t nBlocks = byteLen / AES_BLOCK_SIZE;

    uint32_t* in  = (uint32_t*)input;
    uint32_t* out = (uint32_t*)output;
    uint32_t* w = (uint32_t*)keySchedule;
    uint32_t state[NB];

    for(uint32_t i = 0; i < nBlocks; i++)
    {
        // Load block of cipher text into State
        for (uint32_t j = 0; j < NB; j++)
        {
            state[j]  = in[NB * i + j];
        }
        
        addRoundKey(state, w, NR128);

        for (uint32_t round = 1; round < NR128; round++)
        {
            invShiftRows(state);
            invSubBytes(state);
            addRoundKey(state, w, NR128 - round);
            invMixColumns(state);
        }
        
        invShiftRows(state);
        invSubBytes(state);
        addRoundKey(state, w, 0);

        // Store state as a block of plain text
        for (uint32_t j = 0; j < NB; j++)
        {
            out[NB * i + j] = state[j];
        }
    }
}