#include "order.h"

namespace groebner {
    bool LexicographicalOrder::IsLess(const Monomial &first, const Monomial &second) {
        Index max_index = std::max(first.GetMaxIndex(), second.GetMaxIndex());
        for (Index i = 0; i <= max_index; ++i) {
            if (first.GetDegree(i) < second.GetDegree(i)) {
                return true;
            }
            if (first.GetDegree(i) > second.GetDegree(i)) {
                return false;
            }
        }
        return false;
    }

    bool GraduatedLexicographicalOrder::IsLess(const Monomial &first, const Monomial &second) {
        Degree first_sum = first.GetSumOfDegrees();
        Degree second_sum = second.GetSumOfDegrees();
        if (first_sum < second_sum) {
            return true;
        }
        if (first_sum > second_sum) {
            return false;
        }
        return LexicographicalOrder::IsLess(first, second);
    }

    bool GraduatedReverseLexicographicalOrder::IsLess(const Monomial &first, const Monomial &second) {
        Degree first_sum = first.GetSumOfDegrees();
        Degree second_sum = second.GetSumOfDegrees();
        if (first_sum < second_sum) {
            return true;
        }
        if (first_sum > second_sum) {
            return false;
        }
        Degree max_index = std::max(first.GetMaxIndex(), second.GetMaxIndex());
        for (Index i = max_index; i >= 0; --i) {
            if (first.GetDegree(i) - second.GetDegree(i) != 0) {
                return first.GetDegree(i) > second.GetDegree(i);
            }
        }
        return false;
    }
}
