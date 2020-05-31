#ifndef __AES_DEFINES_H_
#define __AES_DEFINES_H_

// This header contain common defines for AES cipher.

#define NB (4)      // Number of columns (32-bit words) comprising the State. 
                    // For this standard, Nb = 4.
                    // State is an Intermediate Cipher result that can be pictured as a rectangular array of bytes, 
                    // having four rows and Nb columns.

#define NK128 (4)   // Number of 32-bit words comprising the Cipher Key.
                    // For 128 bit key, Nk = 4.

#define NR128 (10)  // Number of rounds, which is a function of Nk and Nb (which is fixed). 
                    // For 128 bit key, Nr = 10.

#define AES_BLOCK_SIZE    (16)  // AES block size in bytes.
#define AES_PIPELINE_SIZE (4)   // Number of blocks processed together in pipelined version.

#if AES_PIPELINE_SIZE != 4
    #error  AES_PIPELINE_SIZE value is changed. Pipelined version of AES might be broken. \
            Code for pipelined version do not automatically scaled to pipeline size. \
            Please, take a look to aes_*_aesni_pipelined.c files, if you change this value.
#endif

#endif // __AES_DEFINES_H_
