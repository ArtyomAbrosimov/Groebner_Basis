#pragma once

#include "polynom/set_of_polynoms.h"

namespace groebner {
    template<typename T, typename Order>
    class Algorithms {
    public:
        using Polynomial = Polynomial<T, Order>;
        using SetOfPolynomials = SetOfPolynomials<T, Order>;
        using Term = Term<T>;

        static Polynomial MakeSPolynomial(const Polynomial &first, const Polynomial &second) {
            Term leading1 = first.GetLeading();
            Term leading2 = second.GetLeading();
            Term lcm = LCM(leading1, leading2);
            return first * (lcm / leading1) - second * (lcm / leading2);
        }

        static Polynomial ReducePolynomial(const Polynomial &reducible, const Polynomial &reducing) {
            Polynomial res = reducible;
            DoReduction(res, reducing);
            return res;
        }

        static Polynomial ReducePolynomial(const Polynomial &reducible, const SetOfPolynomials &reducing) {
            Polynomial res = reducible;
            DoReduction(res, reducing);
            return res;
        }

        static SetOfPolynomials DoSlowBuchberger(const SetOfPolynomials &set_of_polynomials) {
            SetOfPolynomials res = set_of_polynomials;
            for (VectorIndex i = 0; i < res.GetSize(); ++i) {
                for (VectorIndex j = 0; j < i; ++j) {
                    Polynomial s_polynom = MakeSPolynomial(res[i], res[j]);
                    Polynomial reduced = ReducePolynomial(s_polynom, res);
                    if (!reduced.IsZero()) res.AddPolynomial(reduced);
                }
            }
            DoAllReductions(res);
            return res;
        }

        static SetOfPolynomials DoBuchberger(const SetOfPolynomials &set_of_polynomials) {
            std::vector<std::pair<VectorIndex, VectorIndex>> indexes;
            VectorIndex last = set_of_polynomials.GetSize() - 1;
            for (VectorIndex i = 0; i <= last; ++i) {
                for (VectorIndex j = i + 1; j <= last; ++j) {
                    indexes.push_back({i, j});
                }
            }
            SetOfPolynomials res = set_of_polynomials;
            while (!indexes.empty()) {
                auto &[i, j] = indexes.back();
                indexes.pop_back();
                if (LCM(res[i].GetLeading(), res[j].GetLeading()) == res[i].GetLeading() * res[j].GetLeading() ||
                    CheckOptimization(i, j, res, indexes)) {
                    continue;
                }
                Polynomial s_polynom = MakeSPolynomial(res[i], res[j]);
                Polynomial reduced = ReducePolynomial(s_polynom, res);
                if (reduced.IsZero()) continue;
                last += 1;
                res.AddPolynomial(reduced);
                for (VectorIndex l = 0; l < last; ++l) {
                    indexes.push_back({l, last});
                }
            }
            DoAllReductions(res);
            return res;
        }

        static bool IsInIdeal(const Polynomial &polynomial, const SetOfPolynomials &set_of_polynomials) {
            SetOfPolynomials basis = DoBuchberger(set_of_polynomials);
            Polynomial remainder = ReducePolynomial(polynomial, set_of_polynomials);
            return remainder.IsZero();
        }

    private:
        static bool CheckOptimization(VectorIndex i, VectorIndex j, const SetOfPolynomials &res, const
        std::vector<std::pair<VectorIndex, VectorIndex>> &indexes) {
            for (VectorIndex l = 0; l < indexes.size(); ++l) {
                if (l != i && l != j &&
                    std::find(indexes.begin(), indexes.end(), std::make_pair(i, l)) == indexes.end() &&
                    std::find(indexes.begin(), indexes.end(), std::make_pair(j, l)) == indexes.end() &&
                    res[l].GetLeading().Divides(LCM(res[i].GetLeading(), res[j].GetLeading()))) {
                    return true;
                }
            }
            return false;
        }

        static void DoAllReductions(SetOfPolynomials &set_of_polynomials) {
            for (VectorIndex i = 0; i < set_of_polynomials.GetSize(); ++i) {
                for (VectorIndex j = 0; j < set_of_polynomials.GetSize(); ++j) {
                    if (i == j) continue;
                    Polynomial res = ReducePolynomial(set_of_polynomials[i], set_of_polynomials[j]);
                    if (res == set_of_polynomials[i]) continue;
                    set_of_polynomials.ChangePolynomial(i, res);
                    if (res.IsZero()) set_of_polynomials.ErasePolynomial(i);
                    return DoAllReductions(set_of_polynomials);
                }
            }
            for (VectorIndex i = 0; i < set_of_polynomials.GetSize(); ++i) {
                Polynomial polynomial = set_of_polynomials[i];
                polynomial /= polynomial.GetLeading().GetCoefficient();
                set_of_polynomials.ChangePolynomial(i, polynomial);
            }
        }

        static void DoReduction(Polynomial &res, const Polynomial &reducing) {
            const Term &leading = reducing.GetLeading();
            for (const Term &term: res) {
                if (leading.GetMonomial().Divides(term.GetMonomial())) {
                    Term quotient = term / leading;
                    Polynomial subtrahend = reducing * quotient;
                    res -= subtrahend;
                    return DoReduction(res, reducing);
                }
            }
        }

        static void DoReduction(Polynomial &res, const SetOfPolynomials &reducing) {
            for (const Polynomial &polynomial: reducing) {
                Polynomial remainder = ReducePolynomial(res, polynomial);
                Polynomial difference = res - remainder;
                res = remainder;
                if (!difference.IsZero()) {
                    return DoReduction(res, reducing);
                }
            }
        }
    };
}
