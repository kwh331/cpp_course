cmake_minimum_required(VERSION 3.10)
project(big_int)

set(CMAKE_CXX_STANDARD 14)

add_executable(big_int main.cpp big_int_class.cpp big_int_class.h test_big_int_class.cpp test_big_int_class.h)