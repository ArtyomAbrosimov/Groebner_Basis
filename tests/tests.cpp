#include "correctness_tests.h"
#include "time_tests.h"
#include "tests.h"

namespace groebner {
    void RunTests(size_t max_size) {
        RunCorectnessTests(max_size);
        RunTimeTests(max_size);
    }
}
