#pragma once

#include "../algorithms.h"

namespace groebner {
    template<typename T, typename Order>
    SetOfPolynomials<T, Order> Cyclic(int n) {
        SetOfPolynomials<T, Order> res;
        for (int i = 1; i < n; ++i) { // номер полинома
            Polynomial<T, Order> poly;
            for (int j = 0; j < n; ++j) { // номер монома
                std::unordered_map<groebner::Index, groebner::Degree> monom_vars;
                for (int k = 0; k < i; ++k) monom_vars.insert({(j + k) % n, 1});// степени
                groebner::Monomial monom(std::move(monom_vars));
                groebner::Term<T> term({monom, 1});
                poly += term;
            }
            res.AddPolynomial(poly);
        }
        std::unordered_map<groebner::Index, groebner::Degree> monom_vars;
        for (int k = 0; k < n; ++k) {
            monom_vars.insert({k, 1});
        }
        Polynomial<T, Order> poly;
        groebner::Monomial monom(std::move(monom_vars));
        groebner::Term<T> term({monom, 1});
        groebner::Monomial const_var;
        groebner::Term<T> term_const({const_var, -1});
        poly += term;
        poly += term_const;
        res.AddPolynomial(poly);
        return res;
    }
}
