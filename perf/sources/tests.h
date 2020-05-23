#ifndef __PERF_TESTS_H_
#define __PERF_TESTS_H_

extern "C"
{
#include "tcl.h"
}

#include <time.h>
#include <stdint.h>
#include <iostream>

double p_aes_encrypt_ecb_128_noop(size_t payloadLen, size_t nIterations);
double p_aes_decrypt_ecb_128_noop(size_t payloadLen, size_t nIterations);

#endif
