cmake_minimum_required(VERSION 3.10)
project(my_realloc)

set(CMAKE_CXX_STANDARD 11)

add_executable(my_realloc main.cpp dynamic_memory.cpp dynamic_memory.h)