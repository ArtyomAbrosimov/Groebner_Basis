#pragma once

#include <iostream>
#include <unordered_map>

namespace groebner {
    class Remainder {
        using Integer = int32_t;

    public:
        Remainder(Integer value, Integer modulus);

        Remainder &operator+=(const Remainder &other);
        Remainder &operator-=(const Remainder &other);
        Remainder &operator*=(const Remainder &other);
        Remainder &operator/=(const Remainder &other);
        friend Remainder operator+(const Remainder &first, const Remainder &second);
        friend Remainder operator-(const Remainder &first, const Remainder &second);
        friend Remainder operator*(const Remainder &first, const Remainder &second);
        friend Remainder operator/(const Remainder &first, const Remainder &second);
        friend std::strong_ordering operator<=>(const Remainder &first, const Remainder &second);
        friend bool operator==(const Remainder &first, const Remainder &second);
        friend bool operator!=(const Remainder &first, const Remainder &second);

        Remainder &operator+=(const Integer &other);
        Remainder &operator-=(const Integer &other);
        Remainder &operator*=(const Integer &other);
        Remainder &operator/=(const Integer &other);
        friend Remainder operator+(const Remainder &first, const Integer &second);
        friend Remainder operator-(const Remainder &first, const Integer &second);
        friend Remainder operator*(const Remainder &first, const Integer &second);
        friend Remainder operator/(const Remainder &first, const Integer &second);
        friend std::strong_ordering operator<=>(const Remainder &first, const Integer &second);
        friend bool operator==(const Remainder &first, const Integer &second);
        friend bool operator!=(const Remainder &first, const Integer &second);
        friend std::ostream &operator<<(std::ostream &out, const Remainder &remainders);

    private:
        [[nodiscard]] Integer FindInverseElement(Integer other) const;
        void FindAllInverses();

        Integer value_ = 0;
        Integer modulus_ = 1;
        std::unordered_map<Integer, Integer> inverses_;
    };
}
