#include "fermat.h"

#include <vector>
#include <cassert>
#include <random>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>

// Calculates (base ^ exponent) % mod
std::uint32_t mod_exp(std::uint32_t base, std::uint32_t exponent, std::uint32_t mod) {
    std::uint64_t x = 1, r = base % mod;
    for(int i = 0; i < 32; i++) {
        if(exponent & (1 << i)) {
            x = (x * r) % mod;
        }
        r = (r * r) % mod;
    }
    return x;
}

// Perform Fermat test on n.
// You should return true only if A^(n-1) % n == 1 for every A inside the tests vector
bool fermat_test(std::uint32_t n, const std::vector<std::uint32_t>& tests) {
    for(auto a : tests) {
        if(mod_exp(a, n - 1, n) != 1) {
            return false;
        }
    }
}
