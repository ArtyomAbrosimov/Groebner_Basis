#include "cyclic.h"
#include "time_tests.h"
#include "timer_wrapper.h"

namespace groebner {
    void TestBuchberger(const SetOfPolynomials<Rational, GraduatedLexicographical> &set) {
        SetOfPolynomials<Rational, GraduatedLexicographical> basis = Algorithms<Rational, GraduatedLexicographical>::DoBuchberger(
                set);
    }

    void TestSlowBuchberger(const SetOfPolynomials<Rational, GraduatedLexicographical> &set) {
        SetOfPolynomials<Rational, GraduatedLexicographical> basis = Algorithms<Rational, GraduatedLexicographical>::DoSlowBuchberger(
                set);
    }

    void RunTimeTests(size_t max_size) {
        for (size_t size = 1; size <= max_size; ++size) {
            SetOfPolynomials cyclic = Cyclic<Rational, GraduatedLexicographical>(size);
            std::cout << "Cyclic" << size << ": Time of algorithm with optimizations: ";
            TestTime(TestBuchberger)(cyclic);
            std::cout << "; Time of algorithm without optimizations: ";
            TestTime(TestSlowBuchberger)(cyclic);
            std::cout << "\n";
        }
    }
}
