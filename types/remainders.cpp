#include "remainders.h"

namespace groebner {
    Remainder::Remainder(Number value, Number modulus) : value_(value), modulus_(modulus) {
        assert(modulus > 0);
        value_ = (value_ % modulus_ + modulus_) % modulus_;
    }

    Remainder operator+(const Remainder &first, const Remainder &second) {
        assert(first.modulus_ == second.modulus_);
        return {(first.value_ + second.value_) % first.modulus_, first.modulus_};
    }

    Remainder operator-(const Remainder &first, const Remainder &second) {
        assert(first.modulus_ == second.modulus_);
        return {(first.value_ - second.value_ + first.modulus_) % first.modulus_, first.modulus_};
    }

    Remainder operator*(const Remainder &first, const Remainder &second) {
        assert(first.modulus_ == second.modulus_);
        return {(first.value_ * second.value_) % first.modulus_, first.modulus_};
    }

    Remainder operator/(const Remainder &first, const Remainder &second) {
        assert(first.modulus_ == second.modulus_);
        Number inverse = first.FindInverseElement(second.value_);
        assert(inverse != -1);
        return {(first.value_ * inverse) % first.modulus_, first.modulus_};
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

    Remainder operator+(const Remainder &first, const Number &second) {
        return {(first.value_ + second) % first.modulus_, first.modulus_};
    }

    Remainder operator-(const Remainder &first, const Number &second) {
        return {(first.value_ - second + first.modulus_) % first.modulus_, first.modulus_};
    }

    Remainder operator*(const Remainder &first, const Number &second) {
        return {(first.value_ * second) % first.modulus_, first.modulus_};
    }

    Remainder operator/(const Remainder &first, const Number &second) {
        Number inverse = first.FindInverseElement(second % first.modulus_);
        assert(inverse != -1);
        return {(first.value_ * inverse) % first.modulus_, first.modulus_};
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
