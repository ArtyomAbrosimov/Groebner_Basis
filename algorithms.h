#pragma once

#include "polynom/set_of_polynoms.h"

namespace groebner {
    template<typename T, typename TOrder>
    class Algorithms {
        using Polynomial = Polynomial<T, TOrder>;
        using SetOfPolynomials = SetOfPolynomials<T, TOrder>;
        using Term = Term<T>;
        using IndexPair = std::vector<std::pair<size_t, size_t>>;

    public:
        static Polynomial MakeSPolynomial(const Polynomial &first, const Polynomial &second) {
            Term leading1 = first.GetLeadingTerm();
            Term leading2 = second.GetLeadingTerm();
            Term lcm = {LCM(leading1.GetMonomial(), leading2.GetMonomial()),
                        leading1.GetCoefficient() * leading2.GetCoefficient()};
            return first * (lcm / leading1) - second * (lcm / leading2);
        }

        static Polynomial ReducePolynomial(const Polynomial &reducible, const Polynomial &reducing) {
            Polynomial res = reducible;
            ReduceInPlace(&res, reducing);
            return res;
        }

        static Polynomial ReducePolynomial(const Polynomial &reducible, const SetOfPolynomials &reducing) {
            Polynomial res = reducible;
            ReduceInPlace(&res, reducing);
            return res;
        }

        static SetOfPolynomials DoSlowBuchberger(const SetOfPolynomials &set_of_polynomials) {
            SetOfPolynomials res = set_of_polynomials;
            for (size_t i = 0; i < res.GetSize(); ++i) {
                for (size_t j = 0; j < i; ++j) {
                    Polynomial s_polynom = MakeSPolynomial(res[i], res[j]);
                    Polynomial reduced = ReducePolynomial(s_polynom, res);
                    if (!reduced.IsZero()) {
                        res.AddPolynomial(reduced);
                    }
                }
            }
            DoAllReductions(&res);
            return res;
        }

        static SetOfPolynomials DoBuchberger(const SetOfPolynomials &set_of_polynomials) {
            size_t last = set_of_polynomials.GetSize() - 1;
            IndexPair indexes = CreateAllPAirs(last);
            SetOfPolynomials res = set_of_polynomials;
            while (!indexes.empty()) {
                auto &[i, j] = indexes.back();
                indexes.pop_back();
                if (LCM(res[i].GetLeadingTerm().GetMonomial(), res[j].GetLeadingTerm().GetMonomial()) ==
                    res[i].GetLeadingTerm().GetMonomial() * res[j].GetLeadingTerm().GetMonomial() ||
                    IsRedundant(i, j, res, indexes)) {
                    continue;
                }
                Polynomial s_polynom = MakeSPolynomial(res[i], res[j]);
                Polynomial reduced = ReducePolynomial(s_polynom, res);
                if (reduced.IsZero()) {
                    continue;
                }
                last += 1;
                res.AddPolynomial(reduced);
                for (size_t l = 0; l < last; ++l) {
                    indexes.push_back({l, last});
                }
            }
            DoAllReductions(&res);
            return res;
        }

        static bool IsInIdeal(const Polynomial &polynomial, const SetOfPolynomials &set_of_polynomials) {
            SetOfPolynomials basis = DoBuchberger(set_of_polynomials);
            Polynomial remainder = ReducePolynomial(polynomial, set_of_polynomials);
            return remainder.IsZero();
        }

    private:
        static bool IsRedundant(size_t i, size_t j, const SetOfPolynomials &res, const IndexPair &indexes) {
            for (size_t l = 0; l < indexes.size(); ++l) {
                if (l != i && l != j &&
                    std::find(indexes.begin(), indexes.end(), std::make_pair(i, l)) == indexes.end() &&
                    std::find(indexes.begin(), indexes.end(), std::make_pair(j, l)) == indexes.end() &&
                    res[l].GetLeadingTerm().GetMonomial().IsDivisorOf(
                            LCM(res[i].GetLeadingTerm().GetMonomial(), res[j].GetLeadingTerm().GetMonomial()))) {
                    return true;
                }
            }
            return false;
        }

        static void DoAllReductions(SetOfPolynomials *set_of_polynomials) {
            for (size_t i = 0; i < set_of_polynomials->GetSize(); ++i) {
                for (size_t j = 0; j < set_of_polynomials->GetSize(); ++j) {
                    if (i == j) {
                        continue;
                    }
                    Polynomial res = ReducePolynomial((*set_of_polynomials)[i], (*set_of_polynomials)[j]);
                    if (res == (*set_of_polynomials)[i]) {
                        continue;
                    }
                    (*set_of_polynomials)[i] = res;
                    if (res.IsZero()) {
                        set_of_polynomials->ErasePolynomial(i);
                    }
                    return DoAllReductions(set_of_polynomials);
                }
            }
            for (size_t i = 0; i < set_of_polynomials->GetSize(); ++i) {
                Polynomial polynomial = (*set_of_polynomials)[i];
                polynomial /= polynomial.GetLeadingTerm().GetCoefficient();
                (*set_of_polynomials)[i] = polynomial;
            }
        }

        static void ReduceInPlace(Polynomial *res, const Polynomial &reducing) {
            const Term &leading = reducing.GetLeadingTerm();
            for (const Term &term: *res) {
                if (leading.GetMonomial().IsDivisorOf(term.GetMonomial())) {
                    Term quotient = term / leading;
                    Polynomial subtrahend = reducing * quotient;
                    *res -= subtrahend;
                    ReduceInPlace(res, reducing);
                    return;
                }
            }
        }

        static void ReduceInPlace(Polynomial *res, const SetOfPolynomials &reducing) {
            for (const Polynomial &polynomial: reducing) {
                Polynomial remainder = ReducePolynomial(*res, polynomial);
                Polynomial difference = *res - remainder;
                *res = remainder;
                if (!difference.IsZero()) {
                    ReduceInPlace(res, reducing);
                    return;
                }
            }
        }

        static IndexPair CreateAllPAirs(size_t last) {
            IndexPair res;
            for (size_t i = 0; i <= last; ++i) {
                for (size_t j = i + 1; j <= last; ++j) {
                    res.push_back({i, j});
                }
            }
            return res;
        }
    };
}
