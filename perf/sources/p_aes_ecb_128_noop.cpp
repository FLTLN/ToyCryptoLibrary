#include "tests.h"

double p_aes_encrypt_ecb_128_noop(size_t payloadLen, size_t nIterations)
{
    uint8_t keySchedule[176];
    uint8_t* input = new uint8_t[payloadLen];
    uint8_t* output = new uint8_t[payloadLen];

    clock_t start, stop;
    start = clock();

    for (size_t i = 0; i < nIterations; i++)
    {
        aes_encrypt_ecb_128_noop(input, output, payloadLen, keySchedule);
    }

    stop = clock();
    return (double)(stop - start) / CLOCKS_PER_SEC;
}

double p_aes_decrypt_ecb_128_noop(size_t payloadLen, size_t nIterations)
{
    uint8_t keySchedule[176];
    uint8_t* input = new uint8_t[payloadLen];
    uint8_t* output = new uint8_t[payloadLen];

    clock_t start, stop;
    start = clock();

    for (size_t i = 0; i < nIterations; i++)
    {
        aes_decrypt_ecb_128_noop(input, output, payloadLen, keySchedule);
    }

    stop = clock();
    return (double)(stop - start) / CLOCKS_PER_SEC;
}
