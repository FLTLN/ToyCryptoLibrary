#define EXECUTE_TEST(test) \
std::cout << "Test: " << #test << "\n" \
std::cout << "Test output:\n"; \
if(test()) std::cout << "Test passed\n\n"; \
else std::cout << "Test failed\n\n";

#include <iostream>
#include "tests.h"

int main()
{
    EXECUTE_TEST(aes_key_expansion_noop)
    return 0;
}