#include "remainders.h"

namespace groebner {
    Remainder::Remainder(Number value, Number modulus) : value_(value), modulus_(modulus) {
        assert(modulus > 0);
        value_ = (value_ % modulus_ + modulus_) % modulus_;
    }

    Remainder Remainder::operator+=(const Remainder &other) {
        assert(modulus_ == other.modulus_);
        value_ = (value_ + other.value_) % modulus_;
        return *this;
    }

    Remainder Remainder::operator-=(const Remainder &other) {
        assert(modulus_ == other.modulus_);
        value_ = (value_ - other.value_) % modulus_;
        return *this;
    }

    Remainder Remainder::operator*=(const Remainder &other) {
        assert(modulus_ == other.modulus_);
        value_ = (value_ * other.value_) % modulus_;
        return *this;
    }

    Remainder Remainder::operator/=(const Remainder &other) {
        assert(modulus_ == other.modulus_);
        Number inverse = FindInverseElement(other.value_);
        assert(inverse != -1);
        value_ = (value_ * inverse) % modulus_;
        return *this;
    }

    Remainder operator+(const Remainder &first, const Remainder &second) {
        Remainder res = first;
        res += second;
        return res;
    }

    Remainder operator-(const Remainder &first, const Remainder &second) {
        Remainder res = first;
        res -= second;
        return res;
    }

    Remainder operator*(const Remainder &first, const Remainder &second) {
        Remainder res = first;
        res *= second;
        return res;
    }

    Remainder operator/(const Remainder &first, const Remainder &second) {
        Remainder res = first;
        res /= second;
        return res;
    }

    Remainder Remainder::operator%=(const Remainder &other) {
        assert(modulus_ == other.modulus_);
        value_ = (value_ % other.value_) % modulus_;
        return *this;
    }

    Remainder operator%(const Remainder &first, const Remainder &second) {
        Remainder res = first;
        res %= second;
        return first;
    }

    std::strong_ordering operator<=>(const Remainder &first, const Remainder &second) {
        assert(first.modulus_ == second.modulus_);
        return first.value_ <=> second.value_;
    }

    bool operator==(const Remainder &first, const Remainder &second) {
        assert(first.modulus_ == second.modulus_);
        return first.value_ == second.value_;
    }

    bool operator!=(const Remainder &first, const Remainder &second) {
        return !(first == second);
    }

    Remainder Remainder::operator+=(const Number &other) {
        value_ = (value_ + other) % modulus_;
        return *this;
    }

    Remainder Remainder::operator-=(const Number &other) {
        value_ = (value_ - other) % modulus_;
        return *this;
    }

    Remainder Remainder::operator*=(const Number &other) {
        value_ = (value_ * other) % modulus_;
        return *this;
    }

    Remainder Remainder::operator/=(const Number &other) {
        Number inverse = FindInverseElement(other);
        assert(inverse != -1);
        value_ = (value_ * inverse) % modulus_;
        return *this;
    }

    Remainder operator+(const Remainder &first, const Number &second) {
        Remainder res = first;
        res += second;
        return res;
    }

    Remainder operator-(const Remainder &first, const Number &second) {
        Remainder res = first;
        res -= second;
        return res;
    }

    Remainder operator*(const Remainder &first, const Number &second) {
        Remainder res = first;
        res *= second;
        return res;
    }

    Remainder operator/(const Remainder &first, const Number &second) {
        Remainder res = first;
        res /= second;
        return res;
    }

    Remainder Remainder::operator%=(const Number &other) {
        value_ = (value_ % other) % modulus_;
        return *this;
    }

    Remainder operator%(const Remainder &first, const Number &second) {
        Remainder res = first;
        res %= second;
        return first;
    }

    std::strong_ordering operator<=>(const Remainder &first, const Number &second) {
        return first.value_ <=> (second % first.modulus_);
    }

    bool operator==(const Remainder &first, const Number &second) {
        return first.value_ == (second % first.modulus_);
    }

    bool operator!=(const Remainder &first, const Number &second) {
        return !(first == second);
    }

    std::ostream &operator<<(std::ostream &out, const Remainder &remainder) {
        out << remainder.value_;
        return out;
    }

    Number Remainder::FindInverseElement(Number other) const {
        for (Number i = 1; i < modulus_; ++i) {
            if ((other * i) % modulus_ == 1) {
                return i;
            }
        }
        return -1;
    }
}
