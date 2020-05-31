#include "tcl.h"

#include "aes_defines.h"
#include "aes_lookup_tables.h"

void aes_decrypt_ecb_128_pure_c(uint8_t* input, uint8_t* output, uint32_t byteLen, uint8_t* keySchedule)
{
    uint32_t nBlocks = byteLen / AES_BLOCK_SIZE;

    uint32_t* in  = (uint32_t*)input;
    uint32_t* out = (uint32_t*)output;
    uint32_t* w = (uint32_t*)keySchedule;
    uint32_t state[NB];
    uint32_t tmpState[NB];
    uint8_t* shiftRowsFromState = (uint8_t*)(state);
    uint8_t* shiftRowsToState = (uint8_t*)(tmpState);

    uint32_t srcColumn;
    uint8_t* pSrcColumn = (uint8_t*)(&srcColumn);
    uint8_t* dstColumn;

    for(uint32_t i = 0; i < nBlocks; i++)
    {
        // Load block of plain text into State with unrolled loop.
        state[0]  = in[NB * i + 0];
        state[1]  = in[NB * i + 1];
        state[2]  = in[NB * i + 2];
        state[3]  = in[NB * i + 3];
        
        // addRoundKey(state, w, NR128) with unrolled loop.
        state[0] = state[0] ^ w[NR128 * NB + 0];
        state[1] = state[1] ^ w[NR128 * NB + 1];
        state[2] = state[2] ^ w[NR128 * NB + 2];
        state[3] = state[3] ^ w[NR128 * NB + 3];

        for (uint32_t round = 1; round < NR128; round++)
        {
            //invShiftRows(state);
            shiftRowsToState[0]  = shiftRowsFromState[0];
            shiftRowsToState[1]  = shiftRowsFromState[13];
            shiftRowsToState[2]  = shiftRowsFromState[10];
            shiftRowsToState[3]  = shiftRowsFromState[7];
            shiftRowsToState[4]  = shiftRowsFromState[4];
            shiftRowsToState[5]  = shiftRowsFromState[1];
            shiftRowsToState[6]  = shiftRowsFromState[14];
            shiftRowsToState[7]  = shiftRowsFromState[11];
            shiftRowsToState[8]  = shiftRowsFromState[8];
            shiftRowsToState[9]  = shiftRowsFromState[5];
            shiftRowsToState[10] = shiftRowsFromState[2];
            shiftRowsToState[11] = shiftRowsFromState[15];
            shiftRowsToState[12] = shiftRowsFromState[12];
            shiftRowsToState[13] = shiftRowsFromState[9];
            shiftRowsToState[14] = shiftRowsFromState[6];
            shiftRowsToState[15] = shiftRowsFromState[3];

            state[0] = tmpState[0];
            state[1] = tmpState[1];
            state[2] = tmpState[2];
            state[3] = tmpState[3];

            // Use lookup table.
            invSubBytes(state);

            // addRoundKey(state, w, NR128 - round);
            state[0] = state[0] ^ w[(NR128 - round) * NB + 0];
            state[1] = state[1] ^ w[(NR128 - round) * NB + 1];
            state[2] = state[2] ^ w[(NR128 - round) * NB + 2];
            state[3] = state[3] ^ w[(NR128 - round) * NB + 3];

            // invMixColumns(state);

            srcColumn = *(state + 0);
            dstColumn = (uint8_t*)(state + 0);

            dstColumn[0] = polyMul_0x0E(pSrcColumn[0]) ^ polyMul_0x0B(pSrcColumn[1]) ^ polyMul_0x0D(pSrcColumn[2]) ^ polyMul_0x09(pSrcColumn[3]);
            dstColumn[1] = polyMul_0x09(pSrcColumn[0]) ^ polyMul_0x0E(pSrcColumn[1]) ^ polyMul_0x0B(pSrcColumn[2]) ^ polyMul_0x0D(pSrcColumn[3]);
            dstColumn[2] = polyMul_0x0D(pSrcColumn[0]) ^ polyMul_0x09(pSrcColumn[1]) ^ polyMul_0x0E(pSrcColumn[2]) ^ polyMul_0x0B(pSrcColumn[3]);
            dstColumn[3] = polyMul_0x0B(pSrcColumn[0]) ^ polyMul_0x0D(pSrcColumn[1]) ^ polyMul_0x09(pSrcColumn[2]) ^ polyMul_0x0E(pSrcColumn[3]);

            srcColumn = *(state + 1);
            dstColumn = (uint8_t*)(state + 1);

            dstColumn[0] = polyMul_0x0E(pSrcColumn[0]) ^ polyMul_0x0B(pSrcColumn[1]) ^ polyMul_0x0D(pSrcColumn[2]) ^ polyMul_0x09(pSrcColumn[3]);
            dstColumn[1] = polyMul_0x09(pSrcColumn[0]) ^ polyMul_0x0E(pSrcColumn[1]) ^ polyMul_0x0B(pSrcColumn[2]) ^ polyMul_0x0D(pSrcColumn[3]);
            dstColumn[2] = polyMul_0x0D(pSrcColumn[0]) ^ polyMul_0x09(pSrcColumn[1]) ^ polyMul_0x0E(pSrcColumn[2]) ^ polyMul_0x0B(pSrcColumn[3]);
            dstColumn[3] = polyMul_0x0B(pSrcColumn[0]) ^ polyMul_0x0D(pSrcColumn[1]) ^ polyMul_0x09(pSrcColumn[2]) ^ polyMul_0x0E(pSrcColumn[3]);

            srcColumn = *(state + 2);
            dstColumn = (uint8_t*)(state + 2);

            dstColumn[0] = polyMul_0x0E(pSrcColumn[0]) ^ polyMul_0x0B(pSrcColumn[1]) ^ polyMul_0x0D(pSrcColumn[2]) ^ polyMul_0x09(pSrcColumn[3]);
            dstColumn[1] = polyMul_0x09(pSrcColumn[0]) ^ polyMul_0x0E(pSrcColumn[1]) ^ polyMul_0x0B(pSrcColumn[2]) ^ polyMul_0x0D(pSrcColumn[3]);
            dstColumn[2] = polyMul_0x0D(pSrcColumn[0]) ^ polyMul_0x09(pSrcColumn[1]) ^ polyMul_0x0E(pSrcColumn[2]) ^ polyMul_0x0B(pSrcColumn[3]);
            dstColumn[3] = polyMul_0x0B(pSrcColumn[0]) ^ polyMul_0x0D(pSrcColumn[1]) ^ polyMul_0x09(pSrcColumn[2]) ^ polyMul_0x0E(pSrcColumn[3]);

            srcColumn = *(state + 3);
            dstColumn = (uint8_t*)(state + 3);

            dstColumn[0] = polyMul_0x0E(pSrcColumn[0]) ^ polyMul_0x0B(pSrcColumn[1]) ^ polyMul_0x0D(pSrcColumn[2]) ^ polyMul_0x09(pSrcColumn[3]);
            dstColumn[1] = polyMul_0x09(pSrcColumn[0]) ^ polyMul_0x0E(pSrcColumn[1]) ^ polyMul_0x0B(pSrcColumn[2]) ^ polyMul_0x0D(pSrcColumn[3]);
            dstColumn[2] = polyMul_0x0D(pSrcColumn[0]) ^ polyMul_0x09(pSrcColumn[1]) ^ polyMul_0x0E(pSrcColumn[2]) ^ polyMul_0x0B(pSrcColumn[3]);
            dstColumn[3] = polyMul_0x0B(pSrcColumn[0]) ^ polyMul_0x0D(pSrcColumn[1]) ^ polyMul_0x09(pSrcColumn[2]) ^ polyMul_0x0E(pSrcColumn[3]);
        }
        
        //invShiftRows(state);
        shiftRowsToState[0]  = shiftRowsFromState[0];
        shiftRowsToState[1]  = shiftRowsFromState[13];
        shiftRowsToState[2]  = shiftRowsFromState[10];
        shiftRowsToState[3]  = shiftRowsFromState[7];
        shiftRowsToState[4]  = shiftRowsFromState[4];
        shiftRowsToState[5]  = shiftRowsFromState[1];
        shiftRowsToState[6]  = shiftRowsFromState[14];
        shiftRowsToState[7]  = shiftRowsFromState[11];
        shiftRowsToState[8]  = shiftRowsFromState[8];
        shiftRowsToState[9]  = shiftRowsFromState[5];
        shiftRowsToState[10] = shiftRowsFromState[2];
        shiftRowsToState[11] = shiftRowsFromState[15];
        shiftRowsToState[12] = shiftRowsFromState[12];
        shiftRowsToState[13] = shiftRowsFromState[9];
        shiftRowsToState[14] = shiftRowsFromState[6];
        shiftRowsToState[15] = shiftRowsFromState[3];

        state[0] = tmpState[0];
        state[1] = tmpState[1];
        state[2] = tmpState[2];
        state[3] = tmpState[3];

        // Use lookup table.
        invSubBytes(state);
        // addRoundKey(state, w, 0) with unrolled loop.
        state[0] = state[0] ^ w[0 * NB + 0];
        state[1] = state[1] ^ w[0 * NB + 1];
        state[2] = state[2] ^ w[0 * NB + 2];
        state[3] = state[3] ^ w[0 * NB + 3];

        // Store state as a block of cipher text with unrolled loop.
        out[NB * i + 0] = state[0];
        out[NB * i + 1] = state[1];
        out[NB * i + 2] = state[2];
        out[NB * i + 3] = state[3];
    }
}
