# cmake_minimum_required(VERSION <specify CMake version here>)
project(calculator_modified)

set(CMAKE_CXX_STANDARD 11)

add_executable(calculator_modified main.cpp compute_postfix_expression.cpp compute_postfix_expression.h infix_notation_to_postfix.cpp infix_notation_to_postfix.h)