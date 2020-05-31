#include "tests.h"

#define EXECUTE_TEST(test, payload, iterations)                     \
std::cout << "───────────────────────────────────────────────\n";   \
std::cout << "Test       : " << #test << "\n";                      \
std::cout << "Payload    : " << #payload << "\n";                   \
std::cout << "Iterations : " << #iterations << "\n";                \
std::cout << "Start" <<  "\n";                                      \
all++;                                                              \
{unsigned long long time = test(payload, iterations);               \
std::cout << "Done in " << time << " clocks\n"; }                   \
std::cout << "───────────────────────────────────────────────\n\n";

#define EXECUTE_PRESET_8K1K(test)  EXECUTE_TEST(test, 8192, 1000)
#define EXECUTE_PRESET_8K100K(test)  EXECUTE_TEST(test, 8192, 10000000)

#define WARMUP \
std::cout << "───────────────────────────────────────────────\n";   \
std::cout << "Warmup start" <<  "\n";                               \
{unsigned long long time = p_aes_encrypt_ecb_128_noop(8192, 100);   \
std::cout << "Done in " << time << " clocks\n"; }                   \
std::cout << "───────────────────────────────────────────────\n\n";

int main()
{   
    int all = 0;

    WARMUP
    //EXECUTE_PRESET_8K1K(p_aes_encrypt_ecb_128_noop)
    //EXECUTE_PRESET_8K1K(p_aes_decrypt_ecb_128_noop)
    EXECUTE_PRESET_8K1K(p_aes_encrypt_ecb_128_aesni_iterative)
    EXECUTE_PRESET_8K1K(p_aes_decrypt_ecb_128_aesni_iterative)
    EXECUTE_PRESET_8K1K(p_aes_encrypt_ecb_128_aesni_pipelined)
    EXECUTE_PRESET_8K1K(p_aes_decrypt_ecb_128_aesni_pipelined)

    std::cout << "Testing done\n";
    std::cout << "───────────────────────────────────────────────\n";
    std::cout << "Tests executed : " << all << "\n";
    std::cout << "───────────────────────────────────────────────\n";

    return 0;
}