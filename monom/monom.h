#pragma once

#include <unordered_map>

template<typename T>
class Monomial {
public:
    Monomial() = default;

    Monomial(T coef, const std::unordered_map<int64_t, int64_t> &vars) : coef_(coef), vars_(vars) {};

    [[nodiscard]] int64_t MaxIndex() const;

    [[nodiscard]] int64_t SumOfIndexes() const;

    bool EqualDegree(const Monomial<T> &other) const;

    Monomial<T> LCM(const Monomial<T> &other);

    friend Monomial<T> operator/(const Monomial<T> &first, const Monomial<T> &second);

    friend Monomial<T> operator*(const Monomial<T> &first, const Monomial<T> &second);

    bool Divides(Monomial<T> &other) const;

    T GetCoef() const;

    void SetCoef(T coef);

    [[nodiscard]] std::unordered_map<int64_t, int64_t> GetVars() const;

    void SetVars(std::unordered_map<int64_t, int64_t> vars);

private:
    T coef_;
    std::unordered_map<int64_t, int64_t> vars_;
};