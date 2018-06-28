cmake_minimum_required(VERSION 3.10)
project(rational_number)

set(CMAKE_CXX_STANDARD 14)

add_executable(rational_number main.cpp rational_num.cpp rational_num.h test_rational_number_class.cpp test_rational_number_class.h)