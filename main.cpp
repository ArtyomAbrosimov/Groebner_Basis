#include "tests/tests.h"
#include "tests/except.h"
#include <iostream>

int main() {
    try {
        groebner::RunTests(4);
    } catch (...) {
        except::React();
    }
    return 0;
}
