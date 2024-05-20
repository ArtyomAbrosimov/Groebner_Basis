#pragma once

#include <iostream>
#include <iterator>
#include <unordered_map>

namespace groebner {
    class Monomial {
    public:
        using Index = int64_t;
        using Degree = int64_t;
        using InitList = std::unordered_map<Index, Degree>;

        Monomial() = default;
        explicit Monomial(InitList &&vars);

        Monomial &operator*=(const Monomial &other);
        Monomial &operator/=(const Monomial &other);
        friend Monomial operator*(const Monomial &first, const Monomial &second);
        friend Monomial operator/(const Monomial &first, const Monomial &second);
        friend bool operator==(const Monomial &first, const Monomial &second);
        friend bool operator!=(const Monomial &first, const Monomial &second);
        friend std::ostream &operator<<(std::ostream &out, const Monomial &monomial);
        friend Monomial LCM(const Monomial &first, const Monomial &second);
        friend Monomial GCD(const Monomial &first, const Monomial &second);
        [[nodiscard]] bool IsDivisorOf(const Monomial &other) const;
        [[nodiscard]] Index GetMaxIndex() const;
        [[nodiscard]] Degree GetSumOfDegrees() const;
        [[nodiscard]] Degree GetDegree(Index var_index) const;
        void SetDegree(Index index, Degree degree);
        [[nodiscard]] typename InitList::const_iterator cbegin() const;
        [[nodiscard]] typename InitList::const_iterator cend() const;
        [[nodiscard]] typename InitList::const_iterator begin() const;
        [[nodiscard]] typename InitList::const_iterator end() const;

    private:
        InitList &CleanZeros(InitList &vars);
        void UpdateMaxIndex();
        void UpdateSumOfDegrees();
        bool ArePositiveIndexes();
        bool ArePositiveDegrees();

        InitList vars_;
        Index max_index_ = 0;
        Degree sum_of_degrees_ = 0;
    };
}
