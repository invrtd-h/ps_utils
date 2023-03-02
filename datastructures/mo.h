#ifndef PS_UTILS_MO_H
#define PS_UTILS_MO_H

#include <bits/stdc++.h>

template <typename T>
struct MoSpace {
    std::vector<T> data;
    int l{}, r{};
    
    virtual void insert(int val) = 0;
    virtual void erase(int val) = 0;
    
    [[nodiscard]]
    virtual T get_ans() const = 0;
    
    void apply_query(int ql, int qr) {
        while (r < qr) insert(data[r++]);
        while (l > ql) insert(data[--l]);
        while (r > qr) erase(data[--r]);
        while (l < ql) erase(data[l++]);
    }
};

#endif //PS_UTILS_MO_H
