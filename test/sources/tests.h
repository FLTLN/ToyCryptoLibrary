#ifndef __TESTS_H_
#define __TESTS_H_

extern "C"
{
#include "tcl.h"
}

#include "test_common.h"
#include <stdint.h>

// key expansion
bool t_aes_expandKey_128_noop();

// non-optimized
bool t_aes_encrypt_ecb_128_noop();
bool t_aes_encrypt_ecb_128_noop_cat();
bool t_aes_decrypt_ecb_128_noop();
bool t_aes_decrypt_ecb_128_noop_cat();

// pure c with optimization
bool t_aes_encrypt_ecb_128_pure_c_cat();

// aesni without pipeline
bool t_aes_encrypt_ecb_128_aesni_iterative_cat();
bool t_aes_decrypt_ecb_128_aesni_iterative_cat();

// pipelined aesni
bool t_aes_encrypt_ecb_128_aesni_pipelined_cat();
bool t_aes_decrypt_ecb_128_aesni_pipelined_cat();

#endif // __TESTS_H_
