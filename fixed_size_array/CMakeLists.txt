cmake_minimum_required(VERSION 3.10)
project(fixed_size_array)

set(CMAKE_CXX_STANDARD 11)

add_executable(fixed_size_array main.cpp marray.cpp marray.h test_marray_class.cpp test_marray_class.h)