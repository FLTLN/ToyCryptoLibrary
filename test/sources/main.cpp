#define EXECUTE_TEST(test) \
std::cout << "Test: " << #test << "\n"; \
std::cout << "\nTest output:\n\n"; \
if(test()) std::cout << "\nTest passed\n\n"; \
else std::cout << "\nTest failed\n\n";

#include <iostream>
#include "tests.h"

int main()
{
    EXECUTE_TEST(aes_key_expansion_noop)
    std::cout << "ok";
    return 0;
}