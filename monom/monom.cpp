#include "monom.h"

template<typename T>
int64_t Monomial<T>::MaxIndex() const {
    int64_t res = -1;
    for (auto &[index, degree]: vars_) {
        res = std::max(res, index);
    }
    return res;
}

template<typename T>
int64_t Monomial<T>::SumOfIndexes() const {
    int64_t res = 0;
    for (auto &[index, degree]: vars_) {
        res += degree;
    }
    return res;
}

template <typename T>
bool Monomial<T>::EqualDegree(const Monomial<T> &other) const {
    return vars_ == other.GetVars();
}

template <typename T>
Monomial<T> Monomial<T>::LCM(const Monomial<T> &other) {
    Monomial<T> res;
    res.SetCoef(coef_ * other.GetCoef());
    std::unordered_map<int64_t, int64_t> vars = vars_;
    for (auto &[index, degree]: other.GetVars()) {
        vars[index] += degree;
    }
    return res;
}

template<typename T>
Monomial<T> operator/(const Monomial<T> &first, const Monomial<T> &second) {
    Monomial<T> res;
    res.SetCoef(first.GetCoef() / second.GetCoef());
    std::unordered_map<int64_t, int64_t> vars;
    for (auto &[index, degree]: first.GetVars()) {
        vars[index] = degree - second.GetVars()[index];
    }
    res.SetVars(vars);
    return res;
}

template<typename T>
Monomial<T> operator*(const Monomial<T> &first, const Monomial<T> &second) {
    Monomial<T> res;
    res.SetCoef(first.GetCoef() * second.GetCoef());
    std::unordered_map<int64_t, int64_t> vars = first.GetVars();
    for (auto &[index, degree]: second.GetVars()) {
        vars[index] += degree;
    }
    res.SetVars(vars);
    return res;
}

template <typename T>
bool Monomial<T>::Divides(Monomial<T> &other) const {
    for (auto &[index, degree]: other.GetVars()) {
        if (vars_[index] < degree) {
            return false;
        }
    }
    return true;
}

template<typename T>
T Monomial<T>::GetCoef() const {
    return coef_;
}

template<typename T>
void Monomial<T>::SetCoef(T coef) {
    coef_ = coef;
}

template<typename T>
std::unordered_map<int64_t, int64_t> Monomial<T>::GetVars() const {
    return vars_;
}

template<typename T>
void Monomial<T>::SetVars(std::unordered_map<int64_t, int64_t> vars) {
    vars_ = vars;
}