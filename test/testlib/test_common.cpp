#include "test_common.h"

static char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                 '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

std::string hexDump(void* mem, size_t len)
{
    uint8_t* byteMem = (uint8_t*)mem;
    std::string dump = "0x";

    for (size_t i = 0; i < len; i++)
    {
        dump += hexmap[(byteMem[i] & 0xF0) >> 4];
        dump += hexmap[byteMem[i] & 0x0F];
    }
    
    return dump;
};

bool bufCmp(void* a, void* b, size_t len)
{
    uint8_t* A = (uint8_t*)a;
    uint8_t* B = (uint8_t*)b;
    for (size_t i = 0; i < len; i++)
    {
        if (A[i] != B[i]) return false;
    }
    
    return true;
};

void bufWipe(void* mem, size_t len)
{
    uint8_t* byteMem = (uint8_t*)mem;

    for (size_t i = 0; i < len; i++)
    {
        byteMem[i] = 0x00;
    }
};
