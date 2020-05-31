#include "tests.h"

bool t_aes_decrypt_ecb_128_noop()
{
    uint8_t key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    uint8_t cipher[] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};
    uint8_t expectedPlain[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    
    uint8_t plain[16];
    uint8_t keySchedule[176];

    std::cout << "128 bit key decryption example from NIST FIPS 197.\n\n";

    bufWipe(keySchedule, 176);
    bufWipe(plain, 16);

    aes_expandKey_128_noop(key, keySchedule);
    aes_decrypt_ecb_128_noop(cipher, plain, 16, keySchedule);

    bool isPassed = bufCmp(plain, expectedPlain, 16);

    if(!isPassed)
    {   std::cout << "key                  : \n";
        std::cout << hexDump(key, 16) << "\n";
        std::cout << "cipher text          : \n";
        std::cout << hexDump(cipher, 16) << "\n";
        std::cout << "expected plain text  : \n";
        std::cout << hexDump(expectedPlain, 16) << "\n";
        std::cout << "get plain text       : \n";
        std::cout << hexDump(plain, 16) << "\n";
    }

    return isPassed;
};

static bool t_aes_decrypt_ecb_128(void (*decrypt)(uint8_t*, uint8_t*, uint32_t, uint8_t*))
{
    uint8_t key[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
    uint8_t cipher1[] = {0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef,0x97};
    uint8_t cipher2[] = {0xf5,0xd3,0xd5,0x85,0x03,0xb9,0x69,0x9d,0xe7,0x85,0x89,0x5a,0x96,0xfd,0xba,0xaf};
    uint8_t cipher3[] = {0x43,0xb1,0xcd,0x7f,0x59,0x8e,0xce,0x23,0x88,0x1b,0x00,0xe3,0xed,0x03,0x06,0x88};
    uint8_t cipher4[] = {0x7b,0x0c,0x78,0x5e,0x27,0xe8,0xad,0x3f,0x82,0x23,0x20,0x71,0x04,0x72,0x5d,0xd4};
    uint8_t expectedexpectedPlain1[] = {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a};
    uint8_t expectedexpectedPlain2[] = {0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51};
    uint8_t expectedexpectedPlain3[] = {0x30,0xc8,0x1c,0x46,0xa3,0x5c,0xe4,0x11,0xe5,0xfb,0xc1,0x19,0x1a,0x0a,0x52,0xef};
    uint8_t expectedexpectedPlain4[] = {0xf6,0x9f,0x24,0x45,0xdf,0x4f,0x9b,0x17,0xad,0x2b,0x41,0x7b,0xe6,0x6c,0x37,0x10};

    uint8_t* ptxts[] = {expectedexpectedPlain1,expectedexpectedPlain2,expectedexpectedPlain3,expectedexpectedPlain4};
    uint8_t* ctxts[] = {cipher1,cipher2,cipher3,cipher4};
    
    uint8_t expectedPlain[16];
    uint8_t keySchedule[176];

    std::cout << "128 bit key ECB decryption test vectors from NIST SP 800-38A.\n\n";

    bufWipe(keySchedule, 176);
    aes_expandKey_128_noop(key, keySchedule);

    bool isPassed = true;
    for (size_t i = 0; i < 4; i++)
    {
        bufWipe(expectedPlain, 16);
        decrypt(ctxts[i], expectedPlain, 16, keySchedule);

        isPassed = bufCmp(ptxts[i], expectedPlain, 16);
        std::cout << "test " << i;
        if(!isPassed)
        {   
            std::cout << " failed\n";
            std::cout << "key                  : \n";
            std::cout << hexDump(key, 16) << "\n";
            std::cout << "cipher text          : \n";
            std::cout << hexDump(ctxts[i], 16) << "\n";
            std::cout << "expected plain text  : \n";
            std::cout << hexDump(ptxts[i], 16) << "\n";
            std::cout << "get plain text       : \n";
            std::cout << hexDump(expectedPlain, 16) << "\n";
            return isPassed;
        }
        else
        {
            std::cout << " passed\n";
        }
        
    }
    return isPassed;
};

// non-optimized
bool t_aes_decrypt_ecb_128_noop_cat()
{
    return t_aes_decrypt_ecb_128(aes_decrypt_ecb_128_noop);  
};

// pure c with optimization
bool t_aes_decrypt_ecb_128_pure_c_cat()
{
    return t_aes_decrypt_ecb_128(aes_decrypt_ecb_128_pure_c);  
};

// aesni without pipeline
bool t_aes_decrypt_ecb_128_aesni_iterative_cat()
{
    return t_aes_decrypt_ecb_128(aes_decrypt_ecb_128_aesni_iterative);
};

// pipelined aesni
bool t_aes_decrypt_ecb_128_aesni_pipelined_cat()
{
    return t_aes_decrypt_ecb_128(aes_decrypt_ecb_128_aesni_pipelined);
};

bool t_aes_decrypt_ecb_128_long(void (*decrypt)(uint8_t*, uint8_t*, uint32_t, uint8_t*))
{
    uint8_t key[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
    uint8_t shortCipher1[] = {0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef,0x97};
    uint8_t shortCipher2[] = {0xf5,0xd3,0xd5,0x85,0x03,0xb9,0x69,0x9d,0xe7,0x85,0x89,0x5a,0x96,0xfd,0xba,0xaf};
    uint8_t shortCipher3[] = {0x43,0xb1,0xcd,0x7f,0x59,0x8e,0xce,0x23,0x88,0x1b,0x00,0xe3,0xed,0x03,0x06,0x88};
    uint8_t shortCipher4[] = {0x7b,0x0c,0x78,0x5e,0x27,0xe8,0xad,0x3f,0x82,0x23,0x20,0x71,0x04,0x72,0x5d,0xd4};
    uint8_t shortExpectedexpectedPlain1[] = {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a};
    uint8_t shortExpectedexpectedPlain2[] = {0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51};
    uint8_t shortExpectedexpectedPlain3[] = {0x30,0xc8,0x1c,0x46,0xa3,0x5c,0xe4,0x11,0xe5,0xfb,0xc1,0x19,0x1a,0x0a,0x52,0xef};
    uint8_t shortExpectedexpectedPlain4[] = {0xf6,0x9f,0x24,0x45,0xdf,0x4f,0x9b,0x17,0xad,0x2b,0x41,0x7b,0xe6,0x6c,0x37,0x10};

    uint8_t* shortPtxts[] = {shortExpectedexpectedPlain1,shortExpectedexpectedPlain2,shortExpectedexpectedPlain3,shortExpectedexpectedPlain4};
    uint8_t* shortCtxts[] = {shortCipher1,shortCipher2,shortCipher3,shortCipher4};

    size_t longPayloadSize = 16 * 16;

    uint8_t cipher1[longPayloadSize];
    uint8_t cipher2[longPayloadSize];
    uint8_t cipher3[longPayloadSize];
    uint8_t cipher4[longPayloadSize];
    uint8_t expectedexpectedPlain1[longPayloadSize];
    uint8_t expectedexpectedPlain2[longPayloadSize];
    uint8_t expectedexpectedPlain3[longPayloadSize];
    uint8_t expectedexpectedPlain4[longPayloadSize];

    for (size_t i = 0; i < longPayloadSize; i++)
    {
        cipher1[i] = shortCipher1[i % 16];
        cipher2[i] = shortCipher2[i % 16];
        cipher3[i] = shortCipher3[i % 16];
        cipher4[i] = shortCipher4[i % 16];
        expectedexpectedPlain1[i] = shortExpectedexpectedPlain1[i % 16];
        expectedexpectedPlain2[i] = shortExpectedexpectedPlain2[i % 16];
        expectedexpectedPlain3[i] = shortExpectedexpectedPlain3[i % 16];
        expectedexpectedPlain4[i] = shortExpectedexpectedPlain4[i % 16];
    }

    uint8_t* ptxts[] = {expectedexpectedPlain1,expectedexpectedPlain2,expectedexpectedPlain3,expectedexpectedPlain4};
    uint8_t* ctxts[] = {cipher1,cipher2,cipher3,cipher4};
    
    uint8_t expectedPlain[16];
    uint8_t keySchedule[176];

    std::cout << "128 bit key ECB decryption test vectors from NIST SP 800-38A.\n";
    std::cout << "Each vector repeated 16 times to provide long payload.\n\n";

    bufWipe(keySchedule, 176);
    aes_expandKey_128_noop(key, keySchedule);

    bool isPassed = true;
    for (size_t i = 0; i < 4; i++)
    {
        bufWipe(expectedPlain, 16);
        decrypt(ctxts[i], expectedPlain, 16, keySchedule);

        isPassed = bufCmp(ptxts[i], expectedPlain, 16);
        std::cout << "test " << i;
        if(!isPassed)
        {   
            std::cout << " failed\n";
            std::cout << "key                  : \n";
            std::cout << hexDump(key, 16) << "\n";
            std::cout << "cipher text          : \n";
            std::cout << hexDump(ctxts[i], 16) << "\n";
            std::cout << "expected plain text  : \n";
            std::cout << hexDump(ptxts[i], 16) << "\n";
            std::cout << "get plain text       : \n";
            std::cout << hexDump(expectedPlain, 16) << "\n";
            return isPassed;
        }
        else
        {
            std::cout << " passed\n";
        }
        
    }
    return isPassed;
};

// pipelined aesni, long payload test
bool t_aes_decrypt_ecb_128_aesni_pipelined_cat_long()
{
    return t_aes_decrypt_ecb_128_long(aes_decrypt_ecb_128_aesni_pipelined);
};

