# ToyCryptoLibrary
## Introduction.
Small toy cryptographic library. My term paper at the 2nd year of university.    

This software should not be used for cryptography purpose, because it developed only for demonstrate performance benefits of using special assembly instructions. If you accidentally find this repository when looking for cryptography library, I advise to look [Intel IPP Crypto](https://github.com/intel/ipp-crypto) library. 
## Implemented cryptography algorithms and other functional.
This library contain [AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) algorithm with 128 bit key. Only [ECB](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation) mode is implemented.   
Algorithm implemented in according with [NIST FIPS 197](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf) and optimized with AES-NI and AVX instructions with help of [Intel® Advanced Encryption Standard (AES) New Instructions Set](https://www.intel.com/content/dam/doc/white-paper/advanced-encryption-standard-new-instructions-set-paper.pdf). There is no VAES-based code, because I only have i7-3630QM cpu, and I can't measure performance of AESNI-based code because my cpu doesn't support this instructions.   
## Algorithmic testing.
All implemented functional pass tests with test vectors from [NIST SP 800-38A](https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf).
## Performance testing.
All functions in this library has specific postfix that describe optimization level. The table below explain the means of these postfixes.
|Postfix  |Explanation  |
|---|---|
|noop  |Non-optimized version.|
|pure_c|Optimized by perform polynomial multiplication using precomputed lookup table.|
|aesni_iterative|Optimized by using AES-NI without pipeline.|
|aesni_pipelined|Optimized by using AES-NI with pipeline.|     

Non-optimized version is used as a baseline for performance measurments. Performance measured using [time stamp counter](https://en.wikipedia.org/wiki/Time_Stamp_Counter).   
The table below shows how many times the optimized version is faster than not optimized.      

|   |pure_c|aesni_iterative|aesni_pipelined|
|---|------|---------------|---------------|
|encrypt|16|437|1081|
|decrypt|30|908|2493|
