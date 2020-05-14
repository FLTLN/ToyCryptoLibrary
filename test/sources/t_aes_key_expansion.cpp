extern "C"
{
#include "tcl.h"
}

#include "test_common.h"
#include "tests.h"
#include <stdint.h>

bool aes_key_expansion_noop()
{
    uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    uint8_t keySchedule[16];

    bufWipe(keySchedule, 16);
    aesExpandKey(key, 16, keySchedule);

    std::cout << hexDump(key, 16) << "\n";
    std::cout << hexDump(keySchedule, 16) << "\n";

    return true;
};