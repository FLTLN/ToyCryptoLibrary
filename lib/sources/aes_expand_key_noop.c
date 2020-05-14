#include "tcl.h"
#include "aes_routine_noop.h"

void aesExpandKey(uint8_t* key, uint32_t keySize, uint8_t* keySchedule)
{
    for (uint32_t i = 0; i < keySize; i++)
    {
        subByte(key + i, keySchedule + i);
    }
};
