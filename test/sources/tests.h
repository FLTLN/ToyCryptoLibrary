#ifndef __TESTS_H_
#define __TESTS_H_

extern "C"
{
#include "tcl.h"
}

#include "test_common.h"
#include <stdint.h>

bool t_aes_expandKey_128_noop();
bool t_aes_encrypt_ecb_128_noop();
bool t_aes_encrypt_ecb_128_noop_cat();
bool t_aes_decrypt_ecb_128_noop();
bool t_aes_decrypt_ecb_128_noop_cat();

#endif // __TESTS_H_
