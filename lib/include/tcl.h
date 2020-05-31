#ifndef _TKL_H_
#define _TKL_H_

#include <stdint.h>

//
// AES Block Sipher. 
//

// No optimizations.

void aes_expandKey_128_noop(uint8_t* key, uint8_t* keySchedule);        // This function perform Key Expansion routine for 128 bit key
                                                                        // to generate a key schedule.

void aes_encrypt_ecb_128_noop(uint8_t* input, uint8_t* output,          // This function perform encryption of given input in ECB mode
                              uint32_t byteLen, uint8_t* keySchedule);  // with a given key schedule and store result into output.

void aes_decrypt_ecb_128_noop(uint8_t* input, uint8_t* output,          // This function perform decryption of given input in ECB mode
                              uint32_t byteLen, uint8_t* keySchedule);  // with a given key schedule and store result into output.

// specific assembly instructions, no pipeline

void aes_encrypt_ecb_128_aesni_iterative(uint8_t* input, uint8_t* output, 
                                         uint32_t byteLen, uint8_t* keySchedule);

void aes_decrypt_ecb_128_aesni_iterative(uint8_t* input, uint8_t* output, 
                                         uint32_t byteLen, uint8_t* keySchedule);

// specific assembly instructions, pipelined

void aes_encrypt_ecb_128_aesni_pipelined(uint8_t* input, uint8_t* output, 
                                         uint32_t byteLen, uint8_t* keySchedule);

void aes_decrypt_ecb_128_aesni_pipelined(uint8_t* input, uint8_t* output, 
                                         uint32_t byteLen, uint8_t* keySchedule);

#endif
