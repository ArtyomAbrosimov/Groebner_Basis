#include "order.h"

namespace groebner {
    bool Lexicographical::IsLess(const Monomial &first, const Monomial &second) {
        Monomial::Index max_index = std::max(first.GetMaxIndex(), second.GetMaxIndex());
        for (Monomial::Index i = 0; i <= max_index; ++i) {
            if (first.GetDegree(i) == second.GetDegree(i))
                continue;
            return first.GetDegree(i) < second.GetDegree(i);
        }
        return false;
    }

    bool GraduatedLexicographical::IsLess(const Monomial &first, const Monomial &second) {
        Monomial::Degree first_sum = first.GetSumOfDegrees();
        Monomial::Degree second_sum = second.GetSumOfDegrees();
        if (first_sum == second_sum)
            return Lexicographical::IsLess(first, second);
        return first_sum < second_sum;
    }

    bool GraduatedReverseLexicographical::IsLess(const Monomial &first, const Monomial &second) {
        Monomial::Degree first_sum = first.GetSumOfDegrees();
        Monomial::Degree second_sum = second.GetSumOfDegrees();
        if (first_sum != second_sum)
            return first_sum < second_sum;
        Monomial::Degree max_index = std::max(first.GetMaxIndex(), second.GetMaxIndex());
        for (Monomial::Index i = max_index; i >= 0; --i) {
            if (first.GetDegree(i) - second.GetDegree(i) != 0) {
                return first.GetDegree(i) > second.GetDegree(i);
            }
        }
        return false;
    }
}
