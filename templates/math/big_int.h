#ifndef PS_UTILS_BIG_INT_H
#define PS_UTILS_BIG_INT_H

#include <bits/stdc++.h>

namespace big {
    using i64 = long long;
    using u64 = unsigned long long;
    
    template<std::size_t N>
    class Uint {
        static_assert(std::has_single_bit(N), "requires 2^n bit size");
        static_assert(N >= 128, "requires >=128 bit size, if not, use built-in ints instead");
        
        using Datatype = std::conditional_t<N == 128, u64, Uint<N / 2>>;
    public:
        Datatype lo, hi;
        
        constexpr auto operator~() const noexcept -> Uint {
            return {~lo, ~hi};
        }
        
        friend constexpr auto operator&(const Uint& l, const Uint& r) noexcept -> Uint {
            return {l.lo & r.lo, l.hi & r.hi};
        }
        
        friend constexpr auto operator|(const Uint& l, const Uint& r) noexcept -> Uint {
            return {l.lo | r.lo, l.hi | r.hi};
        }
        
        friend constexpr auto operator^(const Uint& l, const Uint& r) noexcept -> Uint {
            return {l.lo ^ r.lo, l.hi ^ r.hi};
        }
        
        friend constexpr auto operator<<(const Uint& l, u64 r) noexcept -> Uint {
            r &= 127;
            if (r >= 64) {
                return {0, l.lo << (r - 64)};
            } else {
                return {l.lo << r, (l.hi << r) | (l.lo >> (64 - r))};
            }
        }
        
        friend constexpr auto operator>>(const Uint& l, u64 r) noexcept -> Uint {
            r &= 127;
            if (r >= 64) {
                return {l.hi >> (r - 64), 0};
            } else {
                return {(l.lo >> r) | (l.hi << (64 - r)), l.hi >> r};
            }
        }
        
        constexpr auto operator+() const noexcept -> Uint {
            return *this;
        }
        
        friend constexpr auto operator+(const Uint& l, const Uint& r) noexcept -> Uint {
            bool carry_bit = l.lo + r.lo < l.lo;
            return {l.lo + r.lo, l.hi + r.hi + carry_bit};
        }
        
        friend constexpr auto operator-(const Uint& l, const Uint& r) noexcept -> Uint {
            bool carry_bit = l.lo - r.lo > l.lo;
            return {l.lo - r.lo, l.hi + r.hi - carry_bit};
        }
        
    private:
        static constexpr auto
        assume_high_is_zero_and_multiply(const Uint& l, const Uint& r) noexcept -> Uint {
            auto l_upcast = Uint<N * 2>{l, 0};
            auto r_upcast = Uint<N * 2>{r, 0};
        }
    public:
        friend constexpr auto operator*(const Uint& l, const Uint& r) noexcept -> Uint {
        
        }
        
        
    };
}

#endif
