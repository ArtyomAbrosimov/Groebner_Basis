#include "correctness_tests.h"

namespace groebner {
    void RunCorectnessTests(size_t max_size) {
        for (size_t size = 1; size <= max_size; ++size) {
            SetOfPolynomials c = Cyclic<Rational, GraduatedLexicographical>(size);
            SetOfPolynomials basis = Algorithms<Rational, GraduatedLexicographical>::DoBuchberger(c);
            std::cout << "Groebner basis of Cyclic" << size << ": " << basis << "\n";
        }
    }
}
