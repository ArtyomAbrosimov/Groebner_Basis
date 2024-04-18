#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <unordered_map>

namespace groebner {
    using Index = int64_t;
    using Degree = int64_t;

    class Monomial {
    public:
        Monomial() = default;
        explicit Monomial(std::unordered_map<Index, Degree> &&vars);
        Monomial operator*=(const Monomial &other);
        Monomial operator/=(const Monomial &other);
        friend Monomial operator*(const Monomial &first, const Monomial &second);
        friend Monomial operator/(const Monomial &first, const Monomial &second);
        friend bool operator==(const Monomial &first, const Monomial &second);
        friend bool operator!=(const Monomial &first, const Monomial &second);
        friend std::ostream &operator<<(std::ostream &out, const Monomial &monomial);
        friend Monomial LCM(const Monomial &first, const Monomial &second);
        friend Monomial GCD(const Monomial &first, const Monomial &second);
        [[nodiscard]] bool Divides(const Monomial &other) const;
        [[nodiscard]] Index GetMaxIndex() const;
        [[nodiscard]] Degree GetSumOfDegrees() const;
        [[nodiscard]] Degree GetDegree(Index var_index) const;
        void SetDegree(Index index, Degree degree);
        [[nodiscard]] typename std::unordered_map<Index, Degree>::const_iterator cbegin() const;
        [[nodiscard]] typename std::unordered_map<Index, Degree>::const_iterator cend() const;

    private:
        void CleanZeros();
        void UpdateMaxIndex();
        void UpdateSumOfDegrees();

        std::unordered_map<Index, Degree> vars_;
        Index max_index_;
        Degree sum_of_degrees_;
    };
}
