#pragma once

#include "monom.h"

namespace groebner {
    class LexicographicalOrder {
    public:
        [[nodiscard]] static bool IsLess(const Monomial &first, const Monomial &second);
    };

    class GraduatedLexicographicalOrder {
    public:
        [[nodiscard]] static bool IsLess(const Monomial &first, const Monomial &second);
    };

    class GraduatedReverseLexicographicalOrder {
    public:
        [[nodiscard]] static bool IsLess(const Monomial &first, const Monomial &second);
    };
}
