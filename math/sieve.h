#ifndef PS_UTILS_SIEVE_H
#define PS_UTILS_SIEVE_H

#include <vector>

std::vector<int> prime_sieve(int ubd) {
    std::vector<char> sieve(ubd, 1);
    sieve[0] = sieve[1] = sieve[4] = 0;
    
    for (int i = 2; i * i < ubd; ++i) {
        if (not sieve[i]) {
            continue;
        }
        for (int j = i * i; j < ubd; j += i) {
            sieve[j] = 0;
        }
    }
    
    std::vector<int> ret;
    for (int i = 0; i < ubd; ++i) {
        if (sieve[i]) {
            ret.push_back(i);
        }
    }
    
    return ret;
}

#endif //PS_UTILS_SIEVE_H
