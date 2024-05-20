#include <cassert>
#include <numeric>
#include "rational.h"

namespace groebner {
    Rational::Rational(Integer numerator, Integer denominator) : numerator_(numerator), denominator_(denominator) {
        assert(denominator_ != 0);
        Reduce();
    }

    Rational::Rational(Integer numerator) : numerator_(numerator) {
        Reduce();
    }

    Rational &Rational::operator+=(const Rational &other) {
        Integer lcm = std::lcm(denominator_, other.denominator_);
        numerator_ = numerator_ * (lcm / denominator_) + other.numerator_ * (lcm / other.denominator_);
        denominator_ = lcm;
        Reduce();
        return *this;
    }

    Rational &Rational::operator-=(const Rational &other) {
        Integer lcm = std::lcm(denominator_, other.denominator_);
        numerator_ = numerator_ * (lcm / denominator_) - other.numerator_ * (lcm / other.denominator_);
        denominator_ = lcm;
        Reduce();
        return *this;
    }

    Rational &Rational::operator*=(const Rational &other) {
        numerator_ = numerator_ * other.numerator_;
        denominator_ = denominator_ * other.denominator_;
        Reduce();
        return *this;
    }

    Rational &Rational::operator/=(const Rational &other) {
        assert(other != 0);
        numerator_ = numerator_ * other.denominator_;
        denominator_ = denominator_ * other.numerator_;
        Reduce();
        return *this;
    }

    Rational operator+(const Rational &first, const Rational &second) {
        Rational res = first;
        res += second;
        return res;
    }

    Rational operator-(const Rational &first, const Rational &second) {
        Rational res = first;
        res -= second;
        return res;
    }

    Rational operator*(const Rational &first, const Rational &second) {
        Rational res = first;
        res *= second;
        return res;
    }

    Rational operator/(const Rational &first, const Rational &second) {
        Rational res = first;
        res /= second;
        return res;
    }

    std::strong_ordering operator<=>(const Rational &first, const Rational &second) {
        return first.numerator_ * second.denominator_ <=> second.numerator_ * first.denominator_;
    }

    bool operator==(const Rational &first, const Rational &second) {
        return first.numerator_ == second.numerator_ && first.denominator_ == second.denominator_;
    }

    bool operator!=(const Rational &first, const Rational &second) {
        return !(first == second);
    }

    std::ostream &operator<<(std::ostream &out, const Rational &rational) {
        out << rational.numerator_;
        if (rational.denominator_ != 1) {
            out << '/' << rational.denominator_;
        }
        return out;
    }

    void Rational::Reduce() {
        Integer divider = std::gcd(numerator_, denominator_);
        numerator_ /= divider;
        denominator_ /= divider;
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
    }
}
