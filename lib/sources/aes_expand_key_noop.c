#include "tcl.h"
#include "aes_routine_noop.h"

void aesExpandKey(uint8_t* key, uint32_t keySize, uint8_t* keySchedule)
{
    uint32_t* keySchedule32 = (uint32_t*)keySchedule;
    uint32_t* key32 = (uint32_t*)key;

    uint32_t nk = keySize / 4;
    uint32_t nb = 4;  // block size, fixed in standart
    uint32_t nr = 10; // hardcoded for 128 bit key

    for (uint32_t i = 0; i < 4; i++)
    {
        keySchedule32[i] = key32[i];
    }

    for (uint32_t i = 4; i < nb * (nr + 1); i++)
    {
        uint32_t tmp = keySchedule32[i - 1];

        if (i % nk == 0)
        {
            rotWord(&tmp, &tmp);
            subWord(&tmp, &tmp);
            tmp = tmp ^ rcon(i / nk - 1);
        }
        
        keySchedule32[i] = tmp ^ keySchedule32[i - nk];
    }
};
