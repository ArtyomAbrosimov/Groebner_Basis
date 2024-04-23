#include "algorithms.h"

namespace groebner {
    template<typename T, typename Order>
    SetOfPolynomials<T, Order> Cyclic(int n) {
        SetOfPolynomials<T, Order> res;
        for (int i = 1; i < n; ++i) { // номер полинома
            Polynomial<T, Order> poly;
            for (int j = 0; j < n; ++j) { // номер монома
                std::unordered_map<groebner::Index, groebner::Degree> a;
                for (int k = 0; k < i; ++k) { // степени
                    a.insert({(j + k) % n, 1});
                }
                groebner::Monomial A(std::move(a));
                groebner::Term<int> ta({A, 1});
                poly += ta;
            }
            res.AddPolynomial(poly);
        }
        std::unordered_map<groebner::Index, groebner::Degree> a;
        for (int k = 0; k < n; ++k) {
            a.insert({k, 1});
        }
        Polynomial<T, Order> poly;
        groebner::Monomial A(std::move(a));
        groebner::Term<int> ta({A, 1});
        groebner::Monomial B;
        groebner::Term<int> tb({B, -1});
        poly += ta;
        poly += tb;
        res.AddPolynomial(poly);
        return res;
    }
}

int main() {
    groebner::SetOfPolynomials c =
            groebner::Cyclic<int, groebner::GraduatedLexicographicalOrder>(5);
    std::cout << c << "\n";
    groebner::SetOfPolynomials basis =
            groebner::Algorithms<int, groebner::GraduatedLexicographicalOrder>::DoBuchberger(c);
    std::cout << basis << "\n";
}
