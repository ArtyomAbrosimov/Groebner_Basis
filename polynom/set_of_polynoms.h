#pragma once

#include "polynom.h"
#include <iterator>
#include <vector>

template<typename T>
class SetOfPolynomials {
public:
    SetOfPolynomials() = default;

    SetOfPolynomials(std::unordered_set<Polynomial<T>> polynoms) : polynoms_(polynoms) {};

    Polynomial<T> Reduction(Polynomial<T> &polynomial);

    void Buchberger();

    bool InIdeal(Polynomial<T> &polynomial);

    std::unordered_set<Polynomial<T>> GetPolynoms();

private:
    std::unordered_set<Polynomial<T>> polynoms_;
};