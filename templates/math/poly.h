#ifndef PS_UTILS_POLY_H
#define PS_UTILS_POLY_H

#include <bits/stdc++.h>

template<typename T>
concept Field = requires (T t1, T t2) {
    {t1 + t2} -> std::same_as<T>;
    {t1 - t2} -> std::same_as<T>;
    {t1 * t2} -> std::same_as<T>;
    {t1 / t2} -> std::same_as<T>;
    {-t1} -> std::same_as<T>;
};

template<typename S, typename F>
concept MultPolicy = Field<F> &&
                     requires (std::vector<F> l, std::vector<F> r)
{
{S::mult(l, r)} -> std::same_as<std::vector<F>>;
};

class NaiveMult {
public:
    template<Field T>
    static auto mult(const std::vector<T>& l, const std::vector<T>& r) noexcept
    -> std::vector<T>
    {
        const std::size_t ret_size = l.size() + r.size() - 1;
        auto ret = std::vector<T>(ret_size, T{0});
        
        for (std::size_t i = 0; i < l.size(); ++i) {
            for (std::size_t j = 0; j < r.size(); ++j) {
                ret[i + j] = ret[i + j] + l[i] * r[j];
            }
        }
        
        return ret;
    }
};

template<Field T, MultPolicy<T> M = NaiveMult>
class Poly {
public:
    std::vector<T> data;
    
    [[nodiscard]]
    [[maybe_unused]]
    static auto unit(std::size_t deg) noexcept -> Poly {
        auto ret = std::vector<T>(deg, T{0});
        ret.push_back(T{1});
        return Poly{ret};
    }
    
    [[nodiscard]]
    [[maybe_unused]]
    std::size_t deg() const noexcept {
        return data.size() - 1;
    }
    
    [[nodiscard]]
    std::size_t size() const noexcept {
        return data.size();
    }
    
    [[maybe_unused]]
    const T& get(std::size_t idx) const noexcept {
        if (idx < data.size()) {
            return data[idx];
        } else {
            return T{0};
        }
    }
    
    auto operator+(const Poly& rhs) const noexcept -> Poly {
        std::vector<T> ret(std::max(size(), rhs.size()));
        auto min_size = std::min(size(), rhs.size());
        for (std::size_t i = 0; i < min_size; ++i) {
            ret[i] = data[i] + rhs.data[i];
        }
        if (size() < rhs.size()) {
            for (std::size_t i = min_size; i < rhs.size(); ++i) {
                ret[i] = rhs.data[i];
            }
        } else {
            for (std::size_t i = min_size; i < size(); ++i) {
                ret[i] = data[i];
            }
        }
        return Poly{ret};
    }
    
    auto operator-() const noexcept -> Poly {
        auto ret = data;
        for (auto& x : ret) {x *= T(-1);}
        return Poly{ret};
    }
    
    auto operator-(const Poly& rhs) const noexcept -> Poly {
        std::vector<T> ret(std::max(size(), rhs.size()));
        auto min_size = std::min(size(), rhs.size());
        for (std::size_t i = 0; i < min_size; ++i) {
            ret[i] = data[i] - rhs.data[i];
        }
        if (size() < rhs.size()) {
            for (std::size_t i = min_size; i < rhs.size(); ++i) {
                ret[i] = -rhs.data[i];
            }
        } else {
            for (std::size_t i = min_size; i < size(); ++i) {
                ret[i] = data[i];
            }
        }
        return Poly{ret};
    }
    
    auto operator*(const Poly& rhs) const noexcept -> Poly {
        return Poly{M::mult(data, rhs.data)};
    }
    
    auto operator+=(const Poly& rhs) const noexcept -> Poly& {
        *this = *this + rhs;
        return *this;
    }
    
    auto operator-=(const Poly& rhs) const noexcept -> Poly& {
        *this = *this - rhs;
        return *this;
    }
    
    auto operator*=(const Poly& rhs) const noexcept -> Poly& {
        *this = *this * rhs;
        return *this;
    }
    
    auto operator()(const T& t) const noexcept -> T {
        T ret = T{0};
        T x = T{1};
        for (std::size_t i = 0; i < size(); ++i) {
            ret += x * data[i];
            x *= t;
        }
        return ret;
    }
};

#endif
