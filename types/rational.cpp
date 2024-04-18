#include "rational.h"

namespace groebner {
    Rational::Rational(Numenator numerator, Denomenator denominator = 1) {
        assert(denominator != 0);
        numerator_ = numerator;
        denominator_ = denominator;
        Reduce();
    }

    Rational operator+(const Rational &first, const Rational &second) {
        Rational res(first.numerator_ * second.denominator_ + second.numerator_ * first.denominator_,
                     first.denominator_ * second.denominator_);
        res.Reduce();
        return res;
    }

    Rational operator-(const Rational &first, const Rational &second) {
        Rational res(first.numerator_ * second.denominator_ - second.numerator_ * first.denominator_,
                     first.denominator_ * second.denominator_);
        res.Reduce();
        return res;
    }

    Rational operator*(const Rational &first, const Rational &second) {
        Rational res(first.numerator_ * second.numerator_, first.denominator_ * second.denominator_);
        res.Reduce();
        return res;
    }

    Rational operator/(const Rational &first, const Rational &second) {
        Rational res(first.numerator_ * second.denominator_, first.denominator_ * second.numerator_);
        res.Reduce();
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

    Rational operator+(const Rational &first, const Number &second) {
        Rational res(first.numerator_ + second * first.denominator_,
                     first.denominator_);
        res.Reduce();
        return res;
    }

    Rational operator-(const Rational &first, const Number &second) {
        Rational res(first.numerator_ + second * first.denominator_,
                     first.denominator_);
        res.Reduce();
        return res;
    }

    Rational operator*(const Rational &first, const Number &second) {
        Rational res(first.numerator_ * second, first.denominator_);
        res.Reduce();
        return res;
    }

    Rational operator/(const Rational &first, const Number &second) {
        Rational res(first.numerator_, first.denominator_ * second);
        res.Reduce();
        return res;
    }

    std::strong_ordering operator<=>(const Rational &first, const Number &second) {
        return first.numerator_ <=> second * first.denominator_;
    }

    bool operator==(const Rational &first, const Number &second) {
        return first.numerator_ == second && first.denominator_ == 1;
    }

    bool operator!=(const Rational &first, const Number &second) {
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
        Number divider = GCD(numerator_, denominator_);
        numerator_ /= divider;
        denominator_ /= divider;
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
    }

    Number Rational::GCD(Number first, Number second) {
        while (second != 0) {
            Number temp = second;
            second = first % second;
            first = temp;
        }
        return first;
    }
}
