#ifndef PS_UTILS_FFT_H
#define PS_UTILS_FFT_H

#include <bits/stdc++.h>

using cd = std::complex<double>;
double pi = std::numbers::pi;

std::vector<cd> fft(int n, std::vector<cd> &&a, int pol = 1) {
    std::vector<cd> r(n, 0);
    for (int i = 0; i < a.size(); ++i) {
        int s = 0;
        for (int b = 1, d = n / 2; b < n; b <<= 1, d >>= 1) {
            if (b & i) {
                s += d;
            }
        }
        r[s] = a[i];
    }
    
    for (int mte = 2; mte <= n; mte <<= 1) {
        const cd we = std::exp(cd(0, pol * 2 * pi / mte));
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

auto mul(std::vector<cd> a, std::vector<cd> b) {
    const int n =
        1 << std::bit_width(static_cast<unsigned int>(a.size() + b.size() - 1));
    
    auto ta = fft(n, std::move(a)), tb = fft(n, std::move(b));
    
    for (int i = 0; i < n; ++i) {
        ta[i] *= tb[i];
    }
    
    return fft(n, std::move(ta), -1);
}

#endif
