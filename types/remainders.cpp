#include <cassert>
#include <numeric>
#include "remainders.h"

namespace groebner {
    Remainder::Remainder(Integer value, Integer modulus) : value_((value % modulus + modulus) % modulus),
                                                           modulus_(modulus) {
        assert(modulus_ > 0);
        FindAllInverses();
    }

    Remainder &Remainder::operator+=(const Remainder &other) {
        assert(modulus_ == other.modulus_);
        value_ = static_cast<Integer>((static_cast<int64_t>(value_) + other.value_) % modulus_);
        return *this;
    }

    Remainder &Remainder::operator-=(const Remainder &other) {
        assert(modulus_ == other.modulus_);
        value_ = static_cast<Integer>((static_cast<int64_t>(value_) - other.value_) % modulus_);
        return *this;
    }

    Remainder &Remainder::operator*=(const Remainder &other) {
        assert(modulus_ == other.modulus_);
        value_ = static_cast<Integer>((static_cast<int64_t>(value_) * other.value_) % modulus_);
        return *this;
    }

    Remainder &Remainder::operator/=(const Remainder &other) {
        assert(modulus_ == other.modulus_);
        Integer inverse = FindInverseElement(other.value_);
        assert(inverse != -1);
        value_ = static_cast<Integer>((static_cast<int64_t>(value_) + inverse) % modulus_);
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

    Remainder &Remainder::operator+=(const Integer &other) {
        value_ = static_cast<Integer>((static_cast<int64_t>(value_) + other) % modulus_);
        return *this;
    }

    Remainder &Remainder::operator-=(const Integer &other) {
        value_ = static_cast<Integer>((static_cast<int64_t>(value_) - other) % modulus_);

        return *this;
    }

    Remainder &Remainder::operator*=(const Integer &other) {
        value_ = static_cast<Integer>((static_cast<int64_t>(value_) * other) % modulus_);
        return *this;
    }

    Remainder &Remainder::operator/=(const Integer &other) {
        Integer inverse = inverses_[other];
        assert(inverse != -1);
        value_ = static_cast<Integer>((static_cast<int64_t>(value_) + inverse) % modulus_);
        return *this;
    }

    Remainder operator+(const Remainder &first, const Remainder::Integer &second) {
        Remainder res = first;
        res += second;
        return res;
    }

    Remainder operator-(const Remainder &first, const Remainder::Integer &second) {
        Remainder res = first;
        res -= second;
        return res;
    }

    Remainder operator*(const Remainder &first, const Remainder::Integer &second) {
        Remainder res = first;
        res *= second;
        return res;
    }

    Remainder operator/(const Remainder &first, const Remainder::Integer &second) {
        Remainder res = first;
        res /= second;
        return res;
    }

    std::strong_ordering operator<=>(const Remainder &first, const Remainder::Integer &second) {
        return first.value_ <=> (second % first.modulus_);
    }

    bool operator==(const Remainder &first, const Remainder::Integer &second) {
        return first.value_ == (second % first.modulus_);
    }

    bool operator!=(const Remainder &first, const Remainder::Integer &second) {
        return !(first == second);
    }

    std::ostream &operator<<(std::ostream &out, const Remainder &remainder) {
        out << remainder.value_;
        return out;
    }

    Remainder::Integer Remainder::FindInverseElement(Integer divider) const {
        for (Integer candidate = 1; candidate < modulus_; ++candidate) {
            if ((divider * candidate) % modulus_ == 1) {
                return candidate;
            }
        }
        return -1;
    }

    void Remainder::FindAllInverses() {
        for (Integer element = 0; element < modulus_; ++element) {
            inverses_[element] = FindInverseElement(element);
        }
    }
}
