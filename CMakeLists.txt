cmake_minimum_required(VERSION 3.24)
project(Groebner_Basis)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Groebner_Basis main.cpp monom/monom.cpp monom/order.cpp types/rational.cpp types/remainders.cpp tests/tests.cpp tests/time_tests.cpp tests/correctness_tests.cpp tests/except.cpp)
