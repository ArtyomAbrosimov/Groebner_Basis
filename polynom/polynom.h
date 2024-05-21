#pragma once

#include <functional>
#include <set>
#include "term.h"
#include "../monom/order.h"

namespace groebner {
    template<typename T, typename TOrder>
    class Polynomial {
        using Term = Term<T>;
        using TermList = std::vector<Term>;

    public:
        Polynomial() = default;

        explicit Polynomial(TermList &&terms) : terms_(std::move(CleanZeros(terms))) {
            UpdateLeadingTerm();
        }

        Polynomial &operator+=(const Term &other) {
            if (other.IsZero()) {
                return *this;
            }
            for (Term &term: terms_) {
                if (AreEqualMonomials(term, other)) {
                    term.AddCoefficient(other.GetCoefficient());
                    if (term.IsZero()) {
                        CleanZeros(terms_);
                        UpdateLeadingTerm();
                    }
                    return *this;
                }
            }
            terms_.push_back(other);
            if (TOrder::IsLess(terms_[leading_index_].GetMonomial(), other.GetMonomial())) {
                leading_index_ = terms_.size() - 1;
            }
            return *this;
        }

        friend Polynomial operator+(const Polynomial &first, const Term &second) {
            Polynomial res = first;
            res += second;
            return res;
        }

        Polynomial &operator+=(const Polynomial &other) {
            for (const Term &term: other) {
                *this += term;
            }
            return *this;
        }

        friend Polynomial operator+(const Polynomial &first, const Polynomial &second) {
            Polynomial res = first;
            res += second;
            return res;
        }

        Polynomial &operator-=(const Term &other) {
            if (other.IsZero()) {
                return *this;
            }
            for (Term &term: terms_) {
                if (AreEqualMonomials(term, other)) {
                    term.AddCoefficient(-1 * other.GetCoefficient());
                    if (term.IsZero()) {
                        CleanZeros(terms_);
                        UpdateLeadingTerm();
                    }
                    return *this;
                }
            }
            Term subtrahend = other;
            subtrahend.SetCoefficient(subtrahend.GetCoefficient() * (-1));
            terms_.push_back(subtrahend);
            if (TOrder::IsLess(terms_[leading_index_].GetMonomial(), subtrahend.GetMonomial())) {
                leading_index_ = terms_.size() - 1;
            }
            return *this;
        }

        friend Polynomial operator-(const Polynomial &first, const Term &second) {
            Polynomial res = first;
            res -= second;
            return res;
        }

        Polynomial &operator-=(const Polynomial &other) {
            for (const Term &term: other) {
                *this -= term;
            }
            return *this;
        }

        friend Polynomial operator-(const Polynomial &first, const Polynomial &second) {
            Polynomial res = first;
            res -= second;
            return res;
        }

        Polynomial &operator*=(const Term &other) {
            for (Term &term: terms_) {
                term *= other;
            }
            if (other.IsZero()) {
                CleanZeros(terms_);
                UpdateLeadingTerm();
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
                res += part_of_res;
            }
            return res;
        }

        Polynomial &operator/=(const Term &other) {
            for (Term &term: terms_) {
                term /= other;
            }
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
                if (it != polynomial.cbegin() && it->GetCoefficient() >= 0) {
                    out << " +";
                }
                out << " " << *it;
            }
            return out;
        }

        Term GetLeadingTerm() const {
            static Term zero{{}, 0};
            if (terms_.empty())
                return zero;
            return terms_[leading_index_];
        }

        [[nodiscard]] bool IsZero() const {
            Polynomial test = *this;
            return test.terms_.size() == 0;
        }

        typename TermList::const_iterator cbegin() const {
            return terms_.cbegin();
        }

        typename TermList::const_iterator cend() const {
            return terms_.cend();
        }

        typename TermList::const_iterator begin() const {
            return terms_.begin();
        }

        typename TermList::const_iterator end() const {
            return terms_.end();
        }

    private:
        TermList CleanZeros(TermList &terms) {
            terms.erase(std::remove_if(terms.begin(), terms.end(),
                                       [](const Term &term) { return term.IsZero(); }), terms.end());
            return terms;
        }

        void UpdateLeadingTerm() {
            if (terms_.empty()) {
                return;
            }
            Term res = terms_[0];
            size_t index = 0;
            for (size_t i = 1; i < terms_.size(); ++i) {
                if (TOrder::IsLess(res.GetMonomial(), terms_[i].GetMonomial())) {
                    res = terms_[i];
                    index = i;
                }
            }
            leading_index_ = index;
        }

        TermList terms_;
        size_t leading_index_ = 0;
    };
}
