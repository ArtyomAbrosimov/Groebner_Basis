#include "polynom.h"

template<typename T>
Monomial<T> Polynomial<T>::Leading() const {
    LexicographicalOrder lex;
    Monomial<T> res = monomials_.begin();
    for (Monomial<T> &monom: monomials_) {
        if (lex(res, monom)) {
            res = monom;
        }
    }
    return res;
}

template<typename T>
Polynomial<T> Polynomial<T>::Reduction(Polynomial<T> &other) {
    Monomial<T> leading = other.Leading();
    Polynomial<T> res = this;
    while (true) {
        bool was_reduction = false;
        for (Monomial<T> &monom: res.GerMonomials()) {
            if (monom.Divides(leading)) {
                was_reduction = true;
                Monomial<T> quotient = monom / leading;
                Polynomial<T> subtrahend = other * quotient;
                res = res - subtrahend;
            }
        }
        if (!was_reduction) {
            break;
        }
    }
    return res;
}

template<typename T>
Polynomial<T> Polynomial<T>::SPolynom(Polynomial<T> &other) {
    Monomial<T> leading1 = Leading();
    Monomial<T> leading2 = other.Leading();
    Monomial<T> lcm = leading1.LCM(leading2);
    return (lcm / leading1) * this - (lcm / leading2) * other;
}

template<typename T>
Polynomial<T> operator*(const Polynomial<T> &first, const Monomial<T> &second) {
    std::unordered_set<Monomial<T>> monomials = first.GerMonomials();
    for (Monomial<T> &monom: monomials) {
        monom = monom * second;
    }
    return Polynomial(monomials);
}

template<typename T>
Polynomial<T> operator-(const Polynomial<T> &first, const Polynomial<T> &second) {
    Polynomial<T> res = first;
    for (Monomial<T> monom2: second.GerMonomials()) {
        bool was_equal = false;
        for (Monomial<T> &monom1: first.GerMonomials()) {
            if (monom2.EqualDegree(monom1)) {
                was_equal = true;
                T coef = monom1.GetCoef() - monom2.GetCoef();
                if (coef != 0) {
                    monom1.SetCoef();
                } else {
                    res.EraseMonomial(monom1);
                }
            }
            break;
        }
        if (!was_equal) {
            monom2.SetCoef(-1 * monom2.GetCoef());
            res.AddMonomial(monom2);
        }
    }
    return res;
}

template<typename T>
bool Polynomial<T>::operator!=(Polynomial<T> &other) {
    return monomials_ != other.GetMonomials();
}

template<typename T>
std::unordered_set<Monomial<T>> Polynomial<T>::GetMonomials() const {
    return monomials_;
}

template<typename T>
void Polynomial<T>::AddMonomial(const Monomial<T> &monomial) {
    monomials_.insert(monomial);
}

template<typename T>
void Polynomial<T>::EraseMonomial(Monomial<T> &monomial) {
    monomials_.erase(monomial);
}
