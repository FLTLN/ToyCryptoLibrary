#include "tests.h"

bool t_aes_encrypt_ecb_128_noop()
{
    uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    uint8_t plain[] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    uint8_t expextedCipher[] = {0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb, 0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32};
    
    uint8_t cipher[16];
    uint8_t keySchedule[176];

    std::cout << "128 bit key encryption example from NIST FIPS 197.\n\n";

    bufWipe(keySchedule, 176);
    bufWipe(cipher, 16);

    aes_expandKey_128_noop(key, keySchedule);
    aes_encrypt_ecb_128_noop(plain, cipher, 16, keySchedule);

    bool isPassed = bufCmp(expextedCipher, cipher, 16);

    if(!isPassed)
    {   std::cout << "key                  : \n";
        std::cout << hexDump(key, 16) << "\n";
        std::cout << "plain text           : \n";
        std::cout << hexDump(plain, 16) << "\n";
        std::cout << "expected cipher text : \n";
        std::cout << hexDump(expextedCipher, 16) << "\n";
        std::cout << "get cipher text      : \n";
        std::cout << hexDump(cipher, 16) << "\n";
    }

    return isPassed;
};

bool t_aes_encrypt_ecb_128(void (*encrypt)(uint8_t*, uint8_t*, uint32_t, uint8_t*))
{
    uint8_t key[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
    uint8_t plain1[] = {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a};
    uint8_t plain2[] = {0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51};
    uint8_t plain3[] = {0x30,0xc8,0x1c,0x46,0xa3,0x5c,0xe4,0x11,0xe5,0xfb,0xc1,0x19,0x1a,0x0a,0x52,0xef};
    uint8_t plain4[] = {0xf6,0x9f,0x24,0x45,0xdf,0x4f,0x9b,0x17,0xad,0x2b,0x41,0x7b,0xe6,0x6c,0x37,0x10};
    uint8_t expextedCipher1[] = {0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef,0x97};
    uint8_t expextedCipher2[] = {0xf5,0xd3,0xd5,0x85,0x03,0xb9,0x69,0x9d,0xe7,0x85,0x89,0x5a,0x96,0xfd,0xba,0xaf};
    uint8_t expextedCipher3[] = {0x43,0xb1,0xcd,0x7f,0x59,0x8e,0xce,0x23,0x88,0x1b,0x00,0xe3,0xed,0x03,0x06,0x88};
    uint8_t expextedCipher4[] = {0x7b,0x0c,0x78,0x5e,0x27,0xe8,0xad,0x3f,0x82,0x23,0x20,0x71,0x04,0x72,0x5d,0xd4};

    uint8_t* ptxts[] = {plain1,plain2,plain3,plain4};
    uint8_t* ctxts[] = {expextedCipher1,expextedCipher2,expextedCipher3,expextedCipher4};
    
    uint8_t cipher[16];
    uint8_t keySchedule[176];

    std::cout << "128 bit key ECB encryption test vectors from NIST SP 800-38A.\n\n";

    bufWipe(keySchedule, 176);
    aes_expandKey_128_noop(key, keySchedule);

    bool isPassed = true;
    for (size_t i = 0; i < 4; i++)
    {
        bufWipe(cipher, 16);
        encrypt(ptxts[i], cipher, 16, keySchedule);

        isPassed = bufCmp(ctxts[i], cipher, 16);
        std::cout << "test " << i;
        if(!isPassed)
        {   
            std::cout << " failed\n";
            std::cout << "key                  : \n";
            std::cout << hexDump(key, 16) << "\n";
            std::cout << "plain text           : \n";
            std::cout << hexDump(ptxts[i], 16) << "\n";
            std::cout << "expected cipher text : \n";
            std::cout << hexDump(ctxts[i], 16) << "\n";
            std::cout << "get cipher text      : \n";
            std::cout << hexDump(cipher, 16) << "\n";
            return isPassed;
        }
        else
        {
            std::cout << " passed\n";
        }
        
    }
    return isPassed;
};

bool t_aes_encrypt_ecb_128_noop_cat()
{
    return t_aes_encrypt_ecb_128(aes_encrypt_ecb_128_noop);  
};

bool t_aes_encrypt_ecb_128_pure_c_cat()
{
    return t_aes_encrypt_ecb_128(aes_encrypt_ecb_128_pure_c);  
};

bool t_aes_encrypt_ecb_128_aesni_iterative_cat()
{
    return t_aes_encrypt_ecb_128(aes_encrypt_ecb_128_aesni_iterative);
};

bool t_aes_encrypt_ecb_128_aesni_pipelined_cat()
{
    return t_aes_encrypt_ecb_128(aes_encrypt_ecb_128_aesni_pipelined);
};
