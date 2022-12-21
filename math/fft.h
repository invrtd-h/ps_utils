#ifndef PS_UTILS_FFT_H
#define PS_UTILS_FFT_H

#include <bits/stdc++.h>

using cd = std::complex<double>;
double pi = std::numbers::pi;

std::vector<cd> fft(const std::vector<cd> &a, int pol = 1) {
    int n = 1;
    const int a_sz = static_cast<int>(a.size());
    while (n < a_sz) {
        n <<= 1;
    }
    std::vector<cd> r(n);
    for (int i = 0; i < n; ++i) {
        int s = 0;
        for (int b = 1, d = n / 2; b < n; b <<= 1, d >>= 1) {
            if (b & i) {
                s += d;
            }
        }
        r[s] = i < a_sz ? a[i] : 0;
    }
    
    for (int mte = 2; mte <= n; mte <<= 1) {
        cd we = std::exp(cd(0, pol * 2 * pi / mte));
        for (int i = 0; i < n; i += mte) {
            cd w = 1;
            for (int j = i; j < i + mte / 2; ++j, w *= we) {
                int j2 = j + mte / 2;
                cd temp1 = r[j], temp2 = r[j2];
                r[j] = temp1 + w * temp2;
                r[j2] = temp1 - w * temp2;
            }
        }
    }
    
    if (pol == -1) {
        for (auto &c : r) {
            c /= n;
        }
    }
    
    return r;
}

std::vector<cd> mul(std::vector<cd> a, std::vector<cd> b) {
    const int target_size = static_cast<int>(a.size() + b.size() - 1);
    a.reserve(target_size);
    b.reserve(target_size);
    
    while (a.size() < target_size) {
        a.emplace_back(0);
    }
    while (b.size() < target_size) {
        b.emplace_back(0);
    }
    
    auto ta = fft(a), tb = fft(b);
    
    std::vector<cd> ret(ta.size());
    for (int i = 0; i < ret.size(); ++i) {
        ret[i] = ta[i] * tb[i];
    }
    
    return fft(ret, -1);
}

#endif //PS_UTILS_FFT_H
