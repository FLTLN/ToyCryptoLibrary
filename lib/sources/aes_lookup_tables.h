#ifndef __AES_LOOKUP_TABLES_H_
#define __AES_LOOKUP_TABLES_H_

// This header contain functions that gives access to lookup tables.

// Sdandart-defined lookup tables.

// subWord() transformation is a non-linear byte substitution that operates independently
// on each byte of a word using a substitution table (S-box).
void subWord(uint32_t* src, uint32_t* dst);

// Get element with index n from round constant word array. 
uint32_t rcon(uint32_t n);

// Apply subWord() to each word in State.
void subBytes(uint32_t* state);

// invSubBytes() is the inverse of the subBytes() transformation.
void invSubBytes(uint32_t* state);

// Precomputed tables used for performanse improoving.

// Polynomial multiplication using precomputed lookup table.
// For encryption.
uint8_t polyMul_0x02(uint8_t value);
uint8_t polyMul_0x03(uint8_t value);
// For decryption.
uint8_t polyMul_0x0E(uint8_t value);
uint8_t polyMul_0x09(uint8_t value);
uint8_t polyMul_0x0D(uint8_t value);
uint8_t polyMul_0x0B(uint8_t value);

#endif // __AES_LOOKUP_TABLES_H_
