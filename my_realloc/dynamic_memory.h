//
// Created by kwh331 on 6/18/2018.
//

#ifndef MY_REALLOC_DYNAMIC_MEMORY_H
#define MY_REALLOC_DYNAMIC_MEMORY_H
#include <iostream>

template<class T>
T *re_alloc(T *old_array, int array_size, int desired_size) {
    T *p;
    p = new T[desired_size + 1];
    int z = 0;
    while (z < array_size) {
        *(p + z) = *(old_array + z);
        ++z;
    }
    *(p + z) = '\0';
    delete[] old_array;
    return p;
}

void test_realloc();

#endif //MY_REALLOC_DYNAMIC_MEMORY_H