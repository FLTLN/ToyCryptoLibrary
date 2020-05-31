#ifndef __PERF_TESTS_H_
#define __PERF_TESTS_H_

extern "C"
{
#include "tcl.h"
}

#include <time.h>
#include <stdint.h>
#include <iostream>

static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

// non-optimized
unsigned long long p_aes_encrypt_ecb_128_noop(size_t payloadLen, size_t nIterations);
unsigned long long p_aes_decrypt_ecb_128_noop(size_t payloadLen, size_t nIterations);

// pure c with optimization
unsigned long long p_aes_encrypt_ecb_128_pure_c(size_t payloadLen, size_t nIterations);

// aesni without pipeline
unsigned long long p_aes_encrypt_ecb_128_aesni_iterative(size_t payloadLen, size_t nIterations);
unsigned long long p_aes_decrypt_ecb_128_aesni_iterative(size_t payloadLen, size_t nIterations);

// pipelined aesni
unsigned long long p_aes_encrypt_ecb_128_aesni_pipelined(size_t payloadLen, size_t nIterations);
unsigned long long p_aes_decrypt_ecb_128_aesni_pipelined(size_t payloadLen, size_t nIterations);

#endif
