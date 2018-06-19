//
// Created by kwh331 on 6/18/2018.
//

#include "dynamic_memory.h"

void test_realloc() {
    char s[] = "FOOBAR";
    char *p = re_alloc(s, 7, 20);
    int z = 0;
    *(p + 6) = '6';
    *(p + 7) = '7';
    *(p + 8) = '8';
    *(p + 9) = '9';
    *(p + 10) = '0';
    *(p + 11) = '1';
    *(p + 12) = '2';
    *(p + 13) = '3';
    *(p + 14) = '\0';
    while (*(p + z) != '\0') {
        std::cout << *(p + z);
        ++z;
    }
}
