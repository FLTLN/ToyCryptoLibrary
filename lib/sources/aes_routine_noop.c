#include "tcl.h"

#include "aes_defines.h"
#include "aes_routine_noop.h"
 
void rotWord(uint32_t* src, uint32_t* dst)
{
    uint8_t tmp = *((uint8_t*)src + 0);
    *((uint8_t*)dst + 0) = *((uint8_t*)src + 1);
    *((uint8_t*)dst + 1) = *((uint8_t*)src + 2);
    *((uint8_t*)dst + 2) = *((uint8_t*)src + 3);
    *((uint8_t*)dst + 3) = tmp;
};

void addRoundKey(uint32_t* state, uint32_t* w, uint32_t round)
{
    for (uint32_t i = 0; i < NB; i++)
    {
        state[i] = state[i] ^ w[round * NB + i];
    }   
};

void shiftRows(uint32_t* state)
{
    uint32_t tmpState[4];

    uint8_t* from = (uint8_t*)(state);
    uint8_t* to = (uint8_t*)(tmpState);

    to[0]  = from[0];
    to[1]  = from[5];
    to[2]  = from[10];
    to[3]  = from[15];
    to[4]  = from[4];
    to[5]  = from[9];
    to[6]  = from[14];
    to[7]  = from[3];
    to[8]  = from[8];
    to[9]  = from[13];
    to[10] = from[2];
    to[11] = from[7];
    to[12] = from[12];
    to[13] = from[1];
    to[14] = from[6];
    to[15] = from[11];

    for (uint32_t i = 0; i < NB; i++)
    {
        state[i] = tmpState[i];
    }
};

// The following two functions are implementing some polynomial arithmetic.

// This function perform the carry-less multiplication of two 8 bit values.
// In this scope, the carry-less multiplication is used in polynomial multiplication.
uint16_t clMul(uint8_t multiplicand, uint8_t multiplier)
{
    uint16_t product = 0;
    uint8_t* pProduct = (uint8_t*)(&product);

    for(uint8_t i = 0; i < 8; i++ )
    {
        uint8_t lo = 0;
        uint8_t hi = 0;

        if((multiplier >> i) & 1)
        {
            lo = multiplicand << i;
            hi = multiplicand >> (8 - i);

            pProduct[0] = pProduct[0] ^ hi;
            pProduct[1] = pProduct[1] ^ lo;
        }
    }

    return product;
};

// This function perform the modular reduction by polynomial modulo [x^8 + x^4 + x^3 + x + 1].
uint8_t polyMod(uint16_t value)
{
    uint8_t digitMaskUnc = 0x80;
    uint8_t hiMaskUnc = 0x8D;
    uint8_t loMaskUnc = 0x80;

    uint8_t* pValue = (uint8_t*)(&value);

    for(uint8_t i = 0; i < 8; i++ )
    {
        uint8_t hiMask = hiMaskUnc >> i;
        uint8_t loMask = (loMaskUnc >> i) | (hiMaskUnc << (8 - i));
        uint8_t digitMask = digitMaskUnc >> i;

        if(pValue[0] & digitMask)
        {
           pValue[0] = pValue[0] ^  hiMask;
           pValue[1] = pValue[1] ^  loMask;
        } 
    }

    return pValue[1];
};

// Polynomial multiplication 
#define polyMul(a, b) polyMod(clMul(a, b))

void mixColumn(uint32_t* column)
{
    uint32_t tmp = *column;
    uint8_t* src = (uint8_t*)(&tmp);
    uint8_t* dst = (uint8_t*)(column);

    dst[0] = polyMul(0x02, src[0]) ^ polyMul(0x03, src[1]) ^ src[2] ^ src[3];
    dst[1] = src[0] ^ polyMul(0x02, src[1]) ^ polyMul(0x03, src[2]) ^ src[3];
    dst[2] = src[0] ^ src[1] ^ polyMul(0x02, src[2]) ^ polyMul(0x03, src[3]);
    dst[3] = polyMul(0x03, src[0]) ^ src[1] ^ src[2] ^ polyMul(0x02, src[3]);
}

void mixColumns(uint32_t* state)
{
    for (uint32_t i = 0; i < NB; i++)
    {
        mixColumn(state + i);
    }
}

void invShiftRows(uint32_t* state)
{
    uint32_t tmpState[4];

    uint8_t* from = (uint8_t*)(state);
    uint8_t* to = (uint8_t*)(tmpState);

    to[0]  = from[0];
    to[1]  = from[13];
    to[2]  = from[10];
    to[3]  = from[7];
    to[4]  = from[4];
    to[5]  = from[1];
    to[6]  = from[14];
    to[7]  = from[11];
    to[8]  = from[8];
    to[9]  = from[5];
    to[10] = from[2];
    to[11] = from[15];
    to[12] = from[12];
    to[13] = from[9];
    to[14] = from[6];
    to[15] = from[3];

    for (uint32_t i = 0; i < NB; i++)
    {
        state[i] = tmpState[i];
    }
};

void invMixColumn(uint32_t* column)
{
    uint32_t tmp = *column;
    uint8_t* src = (uint8_t*)(&tmp);
    uint8_t* dst = (uint8_t*)(column);

    dst[0] = polyMul(0x0e, src[0]) ^ polyMul(0x0b, src[1]) ^ polyMul(0x0d, src[2]) ^ polyMul(0x09, src[3]);
    dst[1] = polyMul(0x09, src[0]) ^ polyMul(0x0e, src[1]) ^ polyMul(0x0b, src[2]) ^ polyMul(0x0d, src[3]);
    dst[2] = polyMul(0x0d, src[0]) ^ polyMul(0x09, src[1]) ^ polyMul(0x0e, src[2]) ^ polyMul(0x0b, src[3]);
    dst[3] = polyMul(0x0b, src[0]) ^ polyMul(0x0d, src[1]) ^ polyMul(0x09, src[2]) ^ polyMul(0x0e, src[3]);
}

void invMixColumns(uint32_t* state)
{
    for (uint32_t i = 0; i < NB; i++)
    {
        invMixColumn(state + i);
    }
}
