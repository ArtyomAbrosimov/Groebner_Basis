cmake_minimum_required(VERSION 3.24)
project(Groebner_Basis)

set(CMAKE_CXX_STANDARD 23)

add_executable(Groebner_Basis monom/monom.h monom/order.h polynom/polynom.h polynom/set_of_polynoms.h main.cpp monom/monom.cpp monom/order.cpp types/rational.h types/rational.cpp algorythms.h polynom/polynom.h polynom/term.h types/remainders.cpp)
