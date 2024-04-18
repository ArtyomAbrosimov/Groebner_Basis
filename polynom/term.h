#pragma once

#include "../monom/order.h"
#include "../types//rational.h"
#include "../types/remainders.h"

namespace groebner {
    template<typename T>
    class Term {
    public:
        Term() = default;

        Term(Monomial &monomial, T coefficient) : monomial_(monomial), coefficient_(coefficient) {}

        Term operator+=(const Term &other) {
            assert(AreEqualMonomials(*this, other));
            coefficient_ += other.coefficient_;
            return *this;
        }

        Term operator-=(const Term &other) {
            assert(AreEqualMonomials(*this, other));
            coefficient_ -= other.coefficient_;
            return *this;
        }

        Term operator*=(const Term &other) {
            coefficient_ *= other.coefficient_;
            monomial_ *= other.monomial_;
            return *this;
        }

        Term operator/=(const Term &other) {
            coefficient_ /= other.coefficient_;
            monomial_ /= other.monomial_;
            return *this;
        }

        friend Term operator+(const Term &first, const Term &second) {
            Term res = first;
            res += second;
            return res;
        }

        friend Term operator-(const Term &first, const Term &second) {
            Term res = first;
            res -= second;
            return res;
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

        friend Term operator==(const Term &first, const Term &second) {
            return first.coefficient_ == second.coefficient_ && first.monomial_ == second.monomial_;
        }

        friend Term operator!=(const Term &first, const Term &second) {
            return !(first == second);
        }

        friend std::ostream &operator<<(std::ostream &out, const Term &term) {
            out << term.coefficient_;
            if (!term.IsZero()) {
                out << ' ' << term.monomial_;
            }
            return out;
        }

        friend Term LCM(const Term &first, const Term &second) {
            Monomial res_monomial = LCM(first.monomial_, second.monomial_);
            T res_coefficient = CoefLCM(first.coefficient_, second.coefficient_);
            return Term(res_monomial, res_coefficient);
        }

        friend Term GCD(const Term &first, const Term &second) {
            Monomial res_monomial = GCD(first.monomial_, second.monomial_);
            T res_coefficient = CoefGCD(first.coefficient_, second.coefficient_);
            return Term(res_monomial, res_coefficient);
        }

        friend bool AreEqualMonomials(const Term &first, const Term &other) {
            return first.monomial_ == other.monomial_;
        }

        bool Divides(const Term &other) const {
            return monomial_.Divides(other.monomial_);
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
            coefficient_ = coefficient;
        }

    private:
        static T CoefGCD(T first, T second) {
            while (second != 0) {
                T temp = second;
                second = first % second;
                first = temp;
            }
            return first;
        }

        static T CoefLCM(T first, T second) {
            return (first * second) / CoefGCD(first, second);
        }

        Monomial monomial_;
        T coefficient_;
    };
}
