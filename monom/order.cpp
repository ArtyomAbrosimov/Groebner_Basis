#include "order.h"

template<typename T>
bool LexicographicalOrder::operator()(const Monomial<T> &first, const Monomial<T> &second) const {
    int64_t max_index = std::max(first.MaxIndex(), second.MaxIndex());
    for (int64_t i = 0; i <= max_index; ++i) {
        if (first.GetVars()[i] < second.GetVars()[i]) {
            return true;
        }
        if (first.GetVars()[i] > second.GetVars()[i]) {
            return false;
        }
    }
    return false;
}

template<typename T>
bool GradedLexicographicOrder::operator()(const Monomial<T> &first, const Monomial<T> &second) const {
    int64_t first_sum = first.SumOfIndexes();
    int64_t second_sum = second.SumOfIndexes();
    if (first_sum < second_sum) {
        return true;
    }
    if (first_sum > second_sum) {
        return false;
    }
    LexicographicalOrder lex;
    return lex(first, second);
}