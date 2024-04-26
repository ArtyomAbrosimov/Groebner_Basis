cmake_minimum_required(VERSION 3.24)
project(Groebner_Basis)

set(CMAKE_CXX_STANDARD 23)

add_executable(Groebner_Basis monom/monom.h monom/order.h polynom/polynom.h polynom/set_of_polynoms.h main.cpp monom/monom.cpp monom/order.cpp types/rational.h types/rational.cpp algorithms.h polynom/term.h types/remainders.h types/remainders.cpp tests/tests.cpp tests/tests.h tests/cyclic.h tests/time_tests.h tests/time_tests.cpp tests/correctness_tests.h tests/correctness_tests.cpp)
