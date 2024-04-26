#include "time_tests.h"

namespace groebner {
    void RunTimeTests(int n) {
        for (int i = 1; i <= n; ++i) {
            groebner::SetOfPolynomials c =
                    groebner::Cyclic<groebner::Rational, groebner::GraduatedLexicographicalOrder>(i);
            const clock_t start_fast = ::clock();
            groebner::SetOfPolynomials basis =
                    groebner::Algorithms<groebner::Rational, groebner::GraduatedLexicographicalOrder>::DoBuchberger(c);
            const clock_t finish_fast = ::clock();
            const clock_t start_slow = ::clock();
            basis = groebner::Algorithms<groebner::Rational, groebner::GraduatedLexicographicalOrder>::DoSlowBuchberger(
                    c);
            const clock_t finish_slow = ::clock();
            std::cout << "Cyclic" << i << ": Time of algorithm with optimizations: "
                      << finish_fast - start_fast << "; Time of algorithm without optimizations: "
                      << finish_slow - start_slow << "\n";
        }
    }
}
