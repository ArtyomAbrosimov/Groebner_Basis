#pragma once

#include <functional>
#include <set>
#include "term.h"
#include "../monom/order.h"

namespace groebner {
    template<typename T, typename Order>
    class Polynomial {
    public:
        using Term = Term<T>;

        Polynomial() = default;

        explicit Polynomial(std::vector<Term> &&terms, Order order) : terms_(std::move(terms)), order_(order) {
            CleanZeros();
            UpdateLeading();
        }

        Polynomial operator+=(const Term &other) {
            for (Term &term: terms_) {
                if (AreEqualMonomials(term, other)) {
                    term += other;
                    return *this;
                }
            }
            terms_.push_back(other);
            UpdateLeading();
            return *this;
        }

        friend Polynomial operator+(const Polynomial &first, const Term &second) {
            Polynomial res = first;
            res += second;
            return res;
        }

        Polynomial operator+=(const Polynomial &other) {
            for (const Term &term: other) {
                *this += term;
            }
            CleanZeros();
            UpdateLeading();
            return *this;
        }

        friend Polynomial operator+(const Polynomial &first, const Polynomial &second) {
            Polynomial res = first;
            res += second;
            return res;
        }

        Polynomial operator-=(const Term &other) {
            for (Term &term: terms_) {
                if (AreEqualMonomials(term, other)) {
                    term -= other;
                    return *this;
                }
            }
            Term subtrahend = other;
            subtrahend.SetCoefficient(subtrahend.GetCoefficient() * (-1));
            terms_.push_back(subtrahend);
            return *this;
        }

        friend Polynomial operator-(const Polynomial &first, const Term &second) {
            Polynomial res = first;
            res -= second;
            return res;
        }

        Polynomial operator-=(const Polynomial &other) {
            for (const Term &term: other) {
                *this -= term;
            }
            CleanZeros();
            UpdateLeading();
            return *this;
        }

        friend Polynomial operator-(const Polynomial &first, const Polynomial &second) {
            Polynomial res = first;
            res -= second;
            return res;
        }

        Polynomial operator*=(const Term &other) {
            for (Term &term: terms_) {
                term *= other;
            }
            return *this;
        }

        friend Polynomial operator*(const Polynomial &first, const Term &second) {
            Polynomial res = first;
            res *= second;
            return res;
        }

        Polynomial &operator*=(const Polynomial &other) {
            *this = *this * other;
            return *this;
        }

        friend Polynomial operator*(const Polynomial &first, const Polynomial &second) {
            Polynomial res;
            for (const Term &term: second) {
                Polynomial part_of_res = first;
                part_of_res *= term;
                res = res + part_of_res;
            }
            res.CleanZeros();
            res.UpdateLeading();
            return res;
        }

        Polynomial operator/=(const Term &other) {
            for (Term &term: terms_) {
                term /= other;
            }
            UpdateLeading();
            return *this;
        }

        friend Polynomial operator/(const Polynomial &first, const Term &second) {
            Polynomial res = first;
            res /= second;
            return res;
        }

        friend bool operator==(const Polynomial &first, const Polynomial &second) {
            Polynomial difference = first - second;
            return difference.IsZero();
        }

        friend bool operator!=(const Polynomial &first, const Polynomial &second) {
            return !(first == second);
        }

        friend std::ostream &operator<<(std::ostream &out, const Polynomial &polynomial) {
            if (polynomial.cbegin() == polynomial.cend()) {
                out << "0";
                return out;
            }
            for (auto it = polynomial.cbegin(); it != polynomial.cend(); ++it) {
                if (it != polynomial.cbegin() && it->GetCoefficient() > 0) {
                    out << " +";
                }
                out << " " << *it;
            }
            return out;
        }

        Term GetLeading() const {
            assert(terms_.size() > 0);
            return leading_;
        }

        bool IsZero() {
            CleanZeros();
            return terms_.size() == 0;
        }

        typename std::vector<Term>::const_iterator cbegin() const {
            return terms_.cbegin();
        }

        typename std::vector<Term>::const_iterator cend() const {
            return terms_.cend();
        }

        typename std::vector<Term>::const_iterator begin() const {
            return terms_.begin();
        }

        typename std::vector<Term>::const_iterator end() const {
            return terms_.end();
        }

    private:
        void CleanZeros() {
            terms_.erase(std::remove_if(terms_.begin(), terms_.end(),
                                        [](const Term &term) { return term.IsZero(); }), terms_.end());
        }

        void UpdateLeading() {
            if (terms_.size() == 0) {
                return;
            }
            Term res = terms_[0];
            for (const Term &term: terms_) {
                if (order_.IsLess(res.GetMonomial(), term.GetMonomial()) && !term.IsZero()) {
                    res = term;
                }
            }
            leading_ = res;
        }

        std::vector<Term> terms_;
        Order order_;
        Term leading_;
    };
}
