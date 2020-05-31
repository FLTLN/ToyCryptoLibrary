#include "tcl.h"

#include "aes_defines.h"
#include "aes_routine_noop.h"
#include "aes_lookup_tables.h"

// This function perform Key Expansion Routine used to generate a series of Round Keys from the 128 bit Cipher Key.

void aes_expandKey_128_noop(uint8_t* key, uint8_t* keySchedule)
{
    uint32_t* keySchedule32 = (uint32_t*)keySchedule;
    uint32_t* key32 = (uint32_t*)key;

    for (uint32_t i = 0; i < 4; i++)
    {
        keySchedule32[i] = key32[i];
    }

    for (uint32_t i = 4; i < NB * (NR128 + 1); i++)
    {
        uint32_t tmp = keySchedule32[i - 1];

        if (i % NK128 == 0)
        {
            rotWord(&tmp, &tmp);
            subWord(&tmp, &tmp);
            tmp = tmp ^ rcon(i / NK128 - 1);
        }
        
        keySchedule32[i] = tmp ^ keySchedule32[i - NK128];
    }
};
