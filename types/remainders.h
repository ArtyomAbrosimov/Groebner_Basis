#pragma once

#include <cassert>
#include <iostream>

namespace groebner {
    using Number = int64_t;

    class Remainder {
    public:
        Remainder(Number value, Number modulus);
        friend Remainder operator+(const Remainder &first, const Remainder &second);
        friend Remainder operator-(const Remainder &first, const Remainder &second);
        friend Remainder operator*(const Remainder &first, const Remainder &second);
        friend Remainder operator/(const Remainder &first, const Remainder &second);
        friend std::strong_ordering operator<=>(const Remainder &first, const Remainder &second);
        friend bool operator==(const Remainder &first, const Remainder &second);
        friend Remainder operator+(const Remainder &first, const Number &second);
        friend Remainder operator-(const Remainder &first, const Number &second);
        friend Remainder operator*(const Remainder &first, const Number &second);
        friend Remainder operator/(const Remainder &first, const Number &second);
        friend std::strong_ordering operator<=>(const Remainder &first, const Number &second);
        friend bool operator==(const Remainder &first, const Number &second);
        friend bool operator!=(const Remainder &first, const Number &second);
        friend std::ostream &operator<<(std::ostream &out, const Remainder &remainders);

    private:
        [[nodiscard]] Number FindInverseElement(Number other) const;

        Number value_;
        Number modulus_;
    };
}
