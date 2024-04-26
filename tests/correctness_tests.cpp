#include "correctness_tests.h"

namespace groebner {
    void RunCorectnessTests(int n) {
        for (int i = 1; i <= n; ++i) {
            groebner::SetOfPolynomials c =
                    groebner::Cyclic<groebner::Rational, groebner::GraduatedLexicographicalOrder>(i);
            groebner::SetOfPolynomials basis =
                    groebner::Algorithms<groebner::Rational, groebner::GraduatedLexicographicalOrder>::DoBuchberger(
                            c);
            std::cout << "Groebner basis of Cyclic" << i << ": " << basis << "\n";
        }
    }
}
