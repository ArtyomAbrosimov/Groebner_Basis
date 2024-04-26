#include "tests.h"

namespace groebner {
    void RunTests(int n) {
        RunCorectnessTests(n);
        RunTimeTests(n);
    }
}
