#pragma once

#include "../algorithms.h"

namespace groebner {
    template<typename T, typename TOrder>
    SetOfPolynomials<T, TOrder> Cyclic(size_t size) {
        SetOfPolynomials<T, TOrder> res;
        for (size_t polynom_number = 1; polynom_number < size; ++polynom_number) {
            Polynomial<T, TOrder> polynom;
            for (size_t monom_number = 0; monom_number < size; ++monom_number) {
                std::unordered_map<Monomial::Index, Monomial::Degree> monom_vars;
                for (size_t degree = 0; degree < polynom_number; ++degree) {
                    monom_vars.insert({(monom_number + degree) % size, 1});
                }
                Term<T> term(Monomial(std::move(monom_vars)), 1);
                polynom += term;
            }
            res.AddPolynomial(polynom);
        }
        std::unordered_map<Monomial::Index, Monomial::Degree> last_monom_vars;
        for (size_t var_index = 0; var_index < size; ++var_index) {
            last_monom_vars.insert({var_index, 1});
        }
        Term<T> term_prod(Monomial(std::move(last_monom_vars)), 1);
        Term<T> term_const({}, -1);
        Polynomial<T, TOrder> last_polynom({term_prod, term_const});
        res.AddPolynomial(last_polynom);
        return res;
    }
}
