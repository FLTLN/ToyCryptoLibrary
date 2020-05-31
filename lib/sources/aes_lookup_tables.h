#ifndef __AES_LOOKUP_TABLES_H_
#define __AES_LOOKUP_TABLES_H_

// subWord() transformation is a non-linear byte substitution that operates independently
// on each byte of a word using a substitution table (S-box).
void subWord(uint32_t* src, uint32_t* dst);

// Get element with index n from round constant word array. 
uint32_t rcon(uint32_t n);

// Apply subWord() to each word in State.
void subBytes(uint32_t* state);

// invSubBytes() is the inverse of the subBytes() transformation.
void invSubBytes(uint32_t* state);

#endif // __AES_LOOKUP_TABLES_H_
