#include "set_of_polynoms.h"

template<typename T>
Polynomial<T> SetOfPolynomials<T>::Reduction(Polynomial<T> &polynomial) {
    Polynomial<T> res = polynomial;
    while (true) {
        bool was_reduction = false;
        for (Polynomial<T> polynom: GetPolynoms()) {
            Polynomial<T> remainder = res.Reduction(polynom);
            if (remainder != res) {
                was_reduction = true;
            }
        }
        if (!was_reduction) {
            break;
        }
    }
    return res;
}

template<typename T>
void SetOfPolynomials<T>::Buchberger() {
    std::vector<Polynomial<T>> vect;
    std::copy(polynoms_.begin(), polynoms_.end(), std::back_inserter(vect));
    for (auto i = vect.begin(); i < vect.end(); ++i) {
        for (auto j = vect.begin(); j < i; ++j) {
            Polynomial<T> spolynom = (*i).SPolynom(*j);
            Polynomial<T> reduced = Reduction(spolynom);
            if (reduced != 0) {
                vect.push_back(reduced);
                polynoms_.insert(reduced);
            }
        }
    }
}

template<typename T>
bool SetOfPolynomials<T>::InIdeal(Polynomial<T> &polynomial) {
    Buchberger();
    Polynomial<T> remainder = Reduction(polynomial);
    return (remainder == Polynomial<T>({Monomial<T>(0, {})}));
}

template<typename T>
std::unordered_set<Polynomial<T>> SetOfPolynomials<T>::GetPolynoms() {
    return polynoms_;
}