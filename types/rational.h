#pragma once

#include <cassert>
#include <iostream>

namespace groebner {
    using Numenator = int64_t;
    using Denomenator = int64_t;
    using Number = int64_t;

    class Rational {
    public:
        Rational(Numenator numerator, Denomenator denominator);
        Rational(Numenator numerator);
        Rational() = default;
        Rational operator+=(const Rational &other);
        Rational operator-=(const Rational &other);
        Rational operator*=(const Rational &other);
        Rational operator/=(const Rational &other);
        friend Rational operator+(const Rational &first, const Rational &second);
        friend Rational operator-(const Rational &first, const Rational &second);
        friend Rational operator*(const Rational &first, const Rational &second);
        friend Rational operator/(const Rational &first, const Rational &second);
        Rational operator%=(const Rational &other);
        friend Rational operator%(const Rational &first, const Rational &second);
        friend std::strong_ordering operator<=>(const Rational &first, const Rational &second);
        friend bool operator==(const Rational &first, const Rational &second);
        friend bool operator!=(const Rational &first, const Rational &second);
        friend std::ostream &operator<<(std::ostream &out, const Rational &rational);

    private:
        void Reduce();
        Number GCD(Number first, Number second);

        Numenator numerator_;
        Denomenator denominator_;
    };
}
