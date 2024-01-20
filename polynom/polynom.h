#pragma once

#include "../monom/order.cpp"
#include <unordered_set>

template<typename T>
class Polynomial {
public:
    Polynomial() = default;

    explicit Polynomial(std::unordered_set<Monomial<T>> monomials) : monomials_(monomials) {};

    Monomial<T> Leading() const;

    Polynomial<T> Reduction(Polynomial<T> &other);

    Polynomial<T> SPolynom(Polynomial<T> &other);

    friend Polynomial<T> operator*(const Polynomial<T> &first, const Monomial<T> &second);

    friend Polynomial<T> operator-(const Polynomial<T> &first, const Polynomial<T> &second);

    bool operator!=(Polynomial<T> &other);

    std::unordered_set<Monomial<T>> GetMonomials() const;

    void AddMonomial(const Monomial<T> &monomial);

    void EraseMonomial(Monomial<T> &monomial);

private:
    std::unordered_set<Monomial<T>> monomials_;
};