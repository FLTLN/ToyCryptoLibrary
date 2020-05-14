#ifndef _TKL_H_
#define _TKL_H_

#include <stdint.h>

//
// AES Block Siphers
//

// No optimizations

void aesExpandKey(uint8_t* key, uint32_t keySize, uint8_t* keySchedule);

#endif
