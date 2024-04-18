#include "algorythms.h"

int main() {
    std::unordered_map<groebner::Index, groebner::Degree> a{{2, 4},
                                                            {3, 6}};
    groebner::Monomial A(std::move(a));
    std::unordered_map<groebner::Index, groebner::Degree> b{{1, 1},
                                                            {2, 4},
                                                            {3, 1}};
    groebner::Monomial B(std::move(b));
    std::unordered_map<groebner::Index, groebner::Degree> c{{1, 2},
                                                            {2, 2}};
    groebner::Monomial C(std::move(c));
    std::unordered_map<groebner::Index, groebner::Degree> d{{2, 4},
                                                            {3, 1}};
    groebner::Monomial D(std::move(d));
    std::unordered_map<groebner::Index, groebner::Degree> e{{1, 1},
                                                            {2, 1},
                                                            {3, 2}};
    groebner::Monomial E(std::move(e));
    std::unordered_map<groebner::Index, groebner::Degree> f{{1, 1},
                                                            {2, 2}};
    groebner::Monomial F(std::move(f));
    groebner::Term<int> ta({A, 1});
    groebner::Term<int> tb({B, 2});
    groebner::Term<int> tc({C, 1});
    groebner::Term<int> td({D, 1});
    groebner::Term<int> te({E, -1});
    groebner::Term<int> tf({F, 1});
    std::vector<groebner::Term<int>> p({ta, tb, tc});
    std::vector<groebner::Term<int>> q({td, te, tf});
    groebner::LexicographicalOrder lex;
    groebner::Polynomial<int, groebner::LexicographicalOrder> P(std::move(p), lex);
    groebner::Polynomial<int, groebner::LexicographicalOrder> Q(std::move(q), lex);
    std::vector<groebner::Polynomial<int, groebner::LexicographicalOrder>> s({P, Q});
    groebner::SetOfPolynomials S(std::move(s));
//    groebner::Polynomial<int, groebner::LexicographicalOrder> res =
//            groebner::Algorithms<int, groebner::LexicographicalOrder>::MakeSPolynom(P, P);
    groebner::Polynomial<int, groebner::LexicographicalOrder> res = groebner::Algorithms<int, groebner::LexicographicalOrder>::ReducePolynomial(
            P, Q);
    std::cout << res << "\n";
//    groebner::Algorithms<int, groebner::LexicographicalOrder>::DoBuchberger(S);
//    std::cout << S << "\n";
//    std::cout << groebner::Algorithms<int, groebner::LexicographicalOrder>::IsInIdeal(P, S);
}
