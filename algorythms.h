#pragma once

#include "polynom/set_of_polynoms.h"

namespace groebner {
    template<typename T, typename Order>
    class Algorithms {
    public:
        using Polynomial = Polynomial<T, Order>;
        using SetOfPolynomials = SetOfPolynomials<T, Order>;
        using Term = Term<T>;

        static Polynomial MakeSPolynom(const Polynomial &first, const Polynomial &second) {
            Term leading1 = first.GetLeading();
            Term leading2 = second.GetLeading();
            Term lcm = LCM(leading1, leading2);
            return first * (lcm / leading1) - second * (lcm / leading2);
        }

        static Polynomial ReducePolynomial(const Polynomial &reducible, const Polynomial &reducing) {
            Polynomial res = reducible;
            PerformReduction(res, reducing);
            return res;
        }

        static Polynomial ReducePolynomial(const Polynomial &reducible, const SetOfPolynomials &reducing) {
            Polynomial res = reducible;
            DoReduction(res, reducing);
            return res;
        }

        static SetOfPolynomials DoBuchberger(const SetOfPolynomials &set_of_polynomials) {
            if (set_of_polynomials.GetSize() == 0) {
                return {};
            }
            SetOfPolynomials res;
            res.AddPolynomial(*set_of_polynomials.begin());
            for (const Polynomial &polynomial: set_of_polynomials) {
                if (!ReducePolynomial(polynomial, res).IsZero()) {
                    res.AddPolynomial(polynomial);
                }
            }
            for (int i = 0; i < res.GetSize(); ++i) {
                for (int j = 0; j < i; ++j) {
                    Polynomial s_polynom = MakeSPolynom(res[i], res[j]);
                    Polynomial reduced = ReducePolynomial(s_polynom, res);
                    if (!reduced.IsZero()) res.AddPolynomial(reduced);
                }
            }
            return res;
        }

        static bool IsInIdeal(const Polynomial &polynomial, const SetOfPolynomials &set_of_polynomials) {
            SetOfPolynomials basis = DoBuchberger(set_of_polynomials);
            Polynomial remainder = ReducePolynomial(polynomial, set_of_polynomials);
            return remainder.IsZero();
        }

    private:
        static void DoReduction(Polynomial &res, const SetOfPolynomials &reducing) {
            for (const auto &polynomial: reducing) {
                Polynomial remainder = ReducePolynomial(res, polynomial);
                Polynomial difference = res - remainder;
                res = remainder;
                if (!difference.IsZero()) {
                    return DoReduction(res, reducing);
                }
            }
        }

        static void PerformReduction(Polynomial &res, const Polynomial &reducing) {
            const Term &leading = reducing.GetLeading();
            for (const auto &monom: res) {
                if (leading.GetMonomial().Divides(monom.GetMonomial())) {
                    Term quotient = monom / leading;
                    Polynomial subtrahend = reducing * quotient;
                    res -= subtrahend;
                    return PerformReduction(res, reducing);
                }
            }
        }
    };
}
