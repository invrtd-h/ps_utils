#ifndef PS_UTILS_MODULO_H
#define PS_UTILS_MODULO_H

#include <bits/stdc++.h>

template<unsigned int P, unsigned int PHI = P - 1>
class Modulo {
private:
    long long n;
    
public:
    Modulo() = default;
    constexpr Modulo(long long _n) : n(_n >= 0 ? _n % P : (P - (-_n % P)) % P) {}
    constexpr Modulo operator+(const Modulo& rhs) const {return Modulo((n + rhs.n) % P);}
    constexpr Modulo& operator+=(const Modulo& rhs) {*this = *this + rhs; return *this;}
    constexpr Modulo operator-() const {return n == 0 ? 0 : P - n;}
    constexpr Modulo operator-(const Modulo& rhs) const {return *this + (-rhs);}
    constexpr Modulo& operator-=(const Modulo& rhs) {*this = *this - rhs; return *this;}
    constexpr Modulo operator*(const Modulo& rhs) const {return Modulo((n * rhs.n) % P);}
    constexpr Modulo& operator*=(const Modulo& rhs) {*this = *this * rhs; return *this;}
    
    [[nodiscard]] constexpr Modulo pow(unsigned long long powered) const {
        if (powered <= 1) {
            return powered == 0 ? 1 : *this;
        }
        Modulo hold = pow(powered / 2);
        return powered % 2 == 0 ? hold * hold : hold * hold * (*this);
    }
    [[nodiscard]] constexpr Modulo inverse() const {return this->pow(PHI - 1);}
    constexpr Modulo operator/(const Modulo& rhs) const {
        if (rhs == 0) {throw std::logic_error("Division by zero");}
        return *this * rhs.inverse();
    }
    constexpr Modulo& operator/=(const Modulo& rhs) {*this = *this / rhs; return *this;}
    constexpr bool operator==(const Modulo& rhs) const {return n == rhs.n;}
    constexpr explicit operator int() const {return static_cast<int>(n);}
    
    friend auto operator<<(std::ostream &os, const Modulo &m) -> std::ostream & {
        os << m.n; return os;
    }
};

#endif //PS_UTILS_MODULO_H
