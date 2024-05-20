#pragma once

#include <iostream>

namespace groebner {
    class Rational {
        using Integer = int64_t;

    public:
        Rational(Integer numerator, Integer denominator);
        Rational(Integer numerator);
        Rational() = default;

        Rational &operator+=(const Rational &other);
        Rational &operator-=(const Rational &other);
        Rational &operator*=(const Rational &other);
        Rational &operator/=(const Rational &other);
        friend Rational operator+(const Rational &first, const Rational &second);
        friend Rational operator-(const Rational &first, const Rational &second);
        friend Rational operator*(const Rational &first, const Rational &second);
        friend Rational operator/(const Rational &first, const Rational &second);
        friend std::strong_ordering operator<=>(const Rational &first, const Rational &second);
        friend bool operator==(const Rational &first, const Rational &second);
        friend bool operator!=(const Rational &first, const Rational &second);
        friend std::ostream &operator<<(std::ostream &out, const Rational &rational);

    private:
        void Reduce();

        Integer numerator_ = 0;
        Integer denominator_ = 1;
    };
}
