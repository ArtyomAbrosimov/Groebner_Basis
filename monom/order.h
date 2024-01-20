#pragma once

#include "monom.h"

struct LexicographicalOrder {
    template<typename T>
    bool operator()(const Monomial<T> &, const Monomial<T> &) const; // less
};

struct GradedLexicographicOrder {
    template<typename T>
    bool operator()(const Monomial<T> &, const Monomial<T> &) const; // less
};