#ifndef PS_UTILS_SEGTREE_H
#define PS_UTILS_SEGTREE_H

#include <bits/stdc++.h>

int bit_width(int x) {
    int ret = 0;
    for (; x; x /= 2) {
        ++ret;
    }
    return ret;
}

template<typename T, typename F, T DEFAULT>
struct ST {
    std::vector<T> data;
    
    explicit ST(const std::vector<T> &init) noexcept
            : data(1 << (bit_width(init.size()) + 1))
    {
        const int sz = (int) data.size();
        for (int i = sz / 2; i < sz / 2 + init.size(); ++i) {
            data[i] = init[i - sz / 2];
        }
        for (int i = sz / 2 + init.size(); i < sz; ++i) {
            data[i] = DEFAULT;
        }
        for (int i = sz / 2 - 1; i > 0; --i) {
            data[i] = F()(data[2 * i], data[2 * i + 1]);
        }
    }
    
    void update(int idx, const T &val) noexcept {
        idx += data.size() / 2;
        data[idx] = val;
        
        idx /= 2;
        while (idx >= 1) {
            data[idx] = F()(data[2 * idx], data[2 * idx + 1]);
            idx /= 2;
        }
    }
    
    T reduce(int l, int r) const {
        const int n = data.size() / 2;
        l += n;
        r += n;
        
        T ret = DEFAULT;
        while (l <= r) {
            if (l % 2 == 1) {
                ret = F()(ret, data[l++]);
            }
            if (r % 2 == 0) {
                ret = F()(ret, data[r--]);
            }
            l /= 2;
            r /= 2;
        }
        
        return ret;
    }
};

#endif
