#ifndef PS_UTILS_NTT_H
#define PS_UTILS_NTT_H

#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128;

constexpr i64 get_ntt_mod(i64 a, i64 b) {
    return (1LL << b) * a + 1;
}

constexpr i64 pow_mod(i64 a, i64 b, i64 p) {
    i64 ret = 1;
    a %= p;
    
    while (b) {
        if (b % 2) {
            ret = ret * a % p;
        }
        a = a * a % p;
        b /= 2;
    }
    return ret;
}

constexpr i64 inv(i64 a, i64 p) {
    return pow_mod(a, p - 2, p);
}

template<i64 A, i64 B, i64 W>
std::vector<i64> ntt(int n, std::vector<i64> &&a, int pol = 1) {
    constexpr i64 P = get_ntt_mod(A, B);
    
    std::vector<i64> r(n, 0);
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
        i64 we = pow_mod(W, (P - 1) / mte, P);
        if (pol == -1) {we = inv(we, P);}
        for (int i = 0; i < n; i += mte) {
            i64 w = 1;
            for (int j = i; j < i + mte / 2; ++j, w = w * we % P) {
                int j2 = j + mte / 2;
                i64 temp1 = r[j], temp2 = r[j2];
                i64 delta = w * temp2 % P;
                r[j] = (temp1 + delta) % P;
                r[j2] = (temp1 + P - delta) % P;
            }
        }
    }
    
    if (pol == -1) {
        for (auto &c : r) {
            c = c * inv(n, P) % P;
        }
    }
    
    return r;
}

template<i64 A, i64 B, i64 W>
auto single_mul(std::vector<i64> a, std::vector<i64> b) {
    const int n =
            1 << std::bit_width((unsigned int)(a.size() + b.size() - 1));
    
    auto ta = ntt<A, B, W>(n, std::move(a));
    auto tb = ntt<A, B, W>(n, std::move(b));
    
    for (int i = 0; i < n; ++i) {
        ta[i] *= tb[i];
    }
    
    return ntt<A, B, W>(n, std::move(ta), -1);
}

constexpr i64 crt(i64 a1, i64 P1, i64 a2, i64 P2) {
    i128 P = P1 * P2;
    i128 n1 = P2, n2 = P1;
    i128 s1 = inv(n1, P1), s2 = inv(n2, P2);
    return (a1 * n1 % P * s1 + a2 * n2 % P * s2) % P;
}

auto mul(const std::vector<i64> &a, const std::vector<i64> &b) {
    constexpr i64 A1 = 119, B1 = 23, W1 = 3;
    constexpr i64 A2 = 63,  B2 = 25, W2 = 5;
    
    constexpr i64 P1 = get_ntt_mod(A1, B1), P2 = get_ntt_mod(A2, B2);
    
    auto mul_mod1 = single_mul<A1, B1, W1>(a, b);
    auto mul_mod2 = single_mul<A2, B2, W2>(a, b);
    
    for (int i = 0; i < mul_mod1.size(); ++i) {
        mul_mod1[i] = crt(mul_mod1[i], P1, mul_mod2[i], P2);
    }
    
    return mul_mod1;
}

#endif
