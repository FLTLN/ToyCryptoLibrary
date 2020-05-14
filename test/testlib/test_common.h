#ifndef __TEST_COMMON_H_
#define __TEST_COMMON_H_

#include <iostream>
#include <string>
#include <bitset>

#include <stdint.h>

std::string hexDump(void* mem, size_t len);

bool bufCmp(void* a, void* b, size_t len);

void bufWipe(void* mem, size_t len);

#endif // __TEST_COMMON_H_
