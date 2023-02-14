#ifndef PS_UTILS_FRACTION_H
#define PS_UTILS_FRACTION_H

#include <concepts>

template<std::integral T>
class Fraction {
    T num, denom;

public:
    constexpr Fraction(const T &num_, const T &denom_ = 1) noexcept
            : num(num_), denom(denom_)
    {
        if (denom < 0) {
            num *= -1;
            denom *= -1;
        }
        reduce();
    }
    
    constexpr explicit operator double() const {
        return static_cast<double>(num) / denom;
    }
    
    friend constexpr auto
    operator+(const Fraction &l, const Fraction &r) -> Fraction {
        return Fraction(l.num * r.denom + l.denom * r.num, l.denom * r.denom);
    }
    
    friend constexpr auto
    operator-(const Fraction &l, const Fraction &r) -> Fraction {
        return Fraction(l.num * r.denom - l.denom * r.num, l.denom * r.denom);
    }
    
    friend constexpr auto
    operator*(const Fraction &l, const Fraction &r) -> Fraction {
        return Fraction(l.num * r.num, l.denom * r.denom);
    }
    
    friend constexpr auto
    operator/(const Fraction &l, const Fraction &r) -> Fraction {
        return Fraction(l.num * r.denom, l.denom * r.num);
    }
    
    friend constexpr auto
    operator<=>(const Fraction &l, const Fraction &r) -> Fraction {
        return l.num * r.denom <=> l.denom * r.num;
    }

private:
    constexpr void reduce() {
        if (num == 0) return;
        
        T temp = std::gcd(num, denom);
        num /= temp;
        denom /= temp;
    }
};

#endif //PS_UTILS_FRACTION_H
