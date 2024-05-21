#pragma once

#include "monom.h"

namespace groebner {
    class Lexicographical {
    public:
        [[nodiscard]] static bool IsLess(const Monomial &first, const Monomial &second);
    };

    class GraduatedLexicographical {
    public:
        [[nodiscard]] static bool IsLess(const Monomial &first, const Monomial &second);
    };

    class GraduatedReverseLexicographical {
    public:
        [[nodiscard]] static bool IsLess(const Monomial &first, const Monomial &second);
    };
}
