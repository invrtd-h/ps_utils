#ifndef PS_UTILS_SEGTREE_NO_COMMUTE_H
#define PS_UTILS_SEGTREE_NO_COMMUTE_H

#include <bits/stdc++.h>

template<typename F, typename T>
concept BinaryOp = requires (F f, T t1, T t2) {
    {f(t1, t2)} -> std::convertible_to<T>;
};

template<typename T, BinaryOp<T> F = std::plus<T>, T identity = T()>
struct SegTree {
    std::vector<T> data;
    constexpr static int mem_num = 1;
    
    SegTree() = default;
    
    explicit SegTree(std::size_t size) noexcept {
        std::size_t n = 1 << std::bit_width(size);
        data = std::vector(n * 2, identity);
    }
    
    [[maybe_unused]]
    static auto from(const std::vector<T>& v) -> SegTree {
        auto ret = SegTree();
        std::size_t n = 1 << std::bit_width(v.size());
        ret.data.resize(n * 2);
        
        for (std::size_t i = 0; i < v.size(); ++i) {
            ret.data[n + i] = v[i];
        }
        for (std::size_t i = v.size() + n; i < ret.data.size(); ++i) {
            ret.data[i] = identity;
        }
        for (std::size_t i = n - 1; i > 0; --i) {
            ret.data[i] = F()(ret.data[2 * i], ret.data[2 * i + 1]);
        }
        
        return ret;
    }
    
    [[maybe_unused]]
    void push(const T& t, std::size_t idx) {
        idx += data.size() / 2;
        data[idx] = t;
        idx /= 2;
        
        for (; idx; idx /= 2) {
            data[idx] = F()(data[2 * idx], data[2 * idx + 1]);
        }
    }
    
    [[nodiscard]]
    [[maybe_unused]]
    auto reduce(std::size_t l, std::size_t r) const {
        auto n = data.size() / 2;
        l += n;
        r += n;
        
        std::vector<std::size_t> l_idxes, r_idxes;
        for (; l <= r; l /= 2, r /= 2) {
            if (l % 2 == 1) {l_idxes.push_back(l++);}
            if (r % 2 == 0) {r_idxes.push_back(r--);}
        }
        std::reverse(r_idxes.begin(), r_idxes.end());
        
        auto ret = identity;
        for (std::size_t i : l_idxes) {
            ret = F()(ret, data[i]);
        }
        for (std::size_t i : r_idxes) {
            ret = F()(ret, data[i]);
        }
        
        return ret;
    }
};

#endif
