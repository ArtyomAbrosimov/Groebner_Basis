#pragma once

#include <cassert>
#include <numeric>
#include "../monom/monom.h"
#include "../types//rational.h"
#include "../types/remainders.h"

namespace groebner {
    template<typename T>
    class Term {
    public:
        Term() = default;

        Term(Monomial &monomial, T coefficient) : monomial_(monomial), coefficient_(coefficient) {
            CheckZero();
        }

        Term(Monomial &&monomial, T coefficient) : monomial_(std::move(monomial)), coefficient_(coefficient) {
            CheckZero();
        }

        Term(T coefficient) : coefficient_(std::move(coefficient)) {}

        Term &operator*=(const Term &other) {
            coefficient_ *= other.coefficient_;
            monomial_ *= other.monomial_;
            CheckZero();
            return *this;
        }

        Term &operator/=(const Term &other) {
            assert(other.monomial_.IsDivisorOf(monomial_));
            assert(!other.IsZero());
            coefficient_ /= other.coefficient_;
            monomial_ /= other.monomial_;
            return *this;
        }

        friend Term operator*(const Term &first, const Term &second) {
            Term res = first;
            res *= second;
            return res;
        }

        friend Term operator/(const Term &first, const Term &second) {
            Term res = first;
            res /= second;
            return res;
        }

        Term &operator/=(T other) {
            assert(other != 0);
            coefficient_ /= other;
            return *this;
        }

        Term &operator*=(T other) {
            coefficient_ *= other;
            CheckZero();
            return *this;
        }

        friend Term operator/(Term &first, T second) {
            Term res = first;
            res /= second;
            return res;
        }

        friend Term operator*(Term &first, T second) {
            Term res = first;
            res *= second;
            return res;
        }

        friend bool operator==(const Term &first, const Term &second) {
            return first.coefficient_ == second.coefficient_ && first.monomial_ == second.monomial_;
        }

        friend bool operator!=(const Term &first, const Term &second) {
            return !(first == second);
        }

        friend std::ostream &operator<<(std::ostream &out, const Term &term) {
            if (!term.IsZero()) {
                out << term.coefficient_ << ' ' << term.monomial_;
            }
            return out;
        }

        void AddCoefficient(T other) {
            coefficient_ += other;
            CheckZero();
        }

        friend bool AreEqualMonomials(const Term &first, const Term &other) {
            return first.monomial_ == other.monomial_;
        }

        [[nodiscard]] bool IsZero() const {
            return coefficient_ == 0;
        }

        [[nodiscard]] Monomial GetMonomial() const {
            return monomial_;
        }

        [[nodiscard]] T GetCoefficient() const {
            return coefficient_;
        }

        void SetCoefficient(T coefficient) {
            coefficient_ = std::move(coefficient);
        }

    private:
        void CheckZero() {
            if (coefficient_ == 0) {
                monomial_ = Monomial();
            }
        }

        Monomial monomial_;
        T coefficient_ = 1;
    };
}
