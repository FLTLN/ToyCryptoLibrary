#include "tests.h"

unsigned long long p_aes_ecb(void (*func)(uint8_t*, uint8_t*, uint32_t, uint8_t*), size_t payloadLen, size_t nIterations)
{
    uint8_t keySchedule[176];
    uint8_t* input = new uint8_t[payloadLen];
    uint8_t* output = new uint8_t[payloadLen];

    unsigned long long start, stop;
    start = rdtsc();

    for (size_t i = 0; i < nIterations; i++)
    {
        func(input, output, payloadLen, keySchedule);
    }

    stop = rdtsc();
    return (unsigned long long)(stop - start);
};

// non-optimized
unsigned long long p_aes_encrypt_ecb_128_noop(size_t payloadLen, size_t nIterations)
{
    return p_aes_ecb(aes_encrypt_ecb_128_noop, payloadLen, nIterations);
};

unsigned long long p_aes_decrypt_ecb_128_noop(size_t payloadLen, size_t nIterations)
{
    return p_aes_ecb(aes_decrypt_ecb_128_noop, payloadLen, nIterations);
};

// pure c with optimization
unsigned long long p_aes_encrypt_ecb_128_pure_c(size_t payloadLen, size_t nIterations)
{
    return p_aes_ecb(aes_encrypt_ecb_128_pure_c, payloadLen, nIterations);
};

unsigned long long p_aes_decrypt_ecb_128_pure_c(size_t payloadLen, size_t nIterations)
{
    return p_aes_ecb(aes_decrypt_ecb_128_pure_c, payloadLen, nIterations);
};

// aesni without pipeline
unsigned long long p_aes_encrypt_ecb_128_aesni_iterative(size_t payloadLen, size_t nIterations)
{
    return p_aes_ecb(aes_encrypt_ecb_128_aesni_iterative, payloadLen, nIterations);
};

unsigned long long p_aes_decrypt_ecb_128_aesni_iterative(size_t payloadLen, size_t nIterations)
{
    return p_aes_ecb(aes_decrypt_ecb_128_aesni_iterative, payloadLen, nIterations);
};

// pipelined aesni
unsigned long long p_aes_encrypt_ecb_128_aesni_pipelined(size_t payloadLen, size_t nIterations)
{
    return p_aes_ecb(aes_encrypt_ecb_128_aesni_pipelined, payloadLen, nIterations);
};

unsigned long long p_aes_decrypt_ecb_128_aesni_pipelined(size_t payloadLen, size_t nIterations)
{
    return p_aes_ecb(aes_decrypt_ecb_128_aesni_pipelined, payloadLen, nIterations);
};
