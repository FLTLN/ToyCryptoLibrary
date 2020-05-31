#ifndef __AES_ROUTINE_H_
#define __AES_ROUTINE_H_

// This header contain functions that performs transformations described in standart.

// rotWord() is a function used in the Key Expansion routine that takes a four-byte
// word and performs a cyclic permutation. 
void rotWord(uint32_t* src, uint32_t* dst);

// In the addRoundKey() transformation, a Round Key is added to the State by a simple bitwise XOR operation.
void addRoundKey(uint32_t* state, uint32_t* w, uint32_t round);

// In the shiftRows() transformation, the bytes in the last three rows of the State are cyclically
// shifted over different numbers of bytes (offsets).
void shiftRows(uint32_t* state);

// shiftRows() performs the following shuffle of 16 bytes of state:
// [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
// to 
// [0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12, 1, 6, 11]

// The MixColumns() transformation operates on the State column-by-column, treating each
// column as a four-term polynomial as described in NIST FIPS 197 Sec. 4.3.
void mixColumns(uint32_t* state);

// invShiftRows() is the inverse of the shiftRows() transformation. 
void invShiftRows(uint32_t* state);

// invMixColumns() is the inverse of the mixColumns() transformation.
void invMixColumns(uint32_t* state);

#endif // __AES_ROUTINE_H_
