//
// Created by kwh331 on 6/18/2018.
//

#include "string_functions.h"
#include <iostream>


int str_cmp(std::string *pt1, std::string *pt2) {
    int t = 0;
    while (t != (*pt1).length()) {
        if ((*pt1)[t] != (*pt2)[t]) {
            return ((*pt1)[t] < (*pt2)[t]) ? -t : +t;
        } else {
            ++t;
        }
    }
    return 1;
}

char *str_cat(char *pt1, char const *pt2) {
    int s = 0;
    while (*(pt1 + s) != '\0') ++s;
    int src_len = 0;
    while (*(pt2 + src_len) != '\0') ++src_len;
    int t = 0;
    while (t != src_len) {
        *(pt1 + s) = *(pt2 + t);
        ++s;
        ++t;
    }
    *(pt1 + s + 1) = '\0';
    return pt1;
}

char *str_cpy(char *dest, const char *src) {
    while (*dest++ = *src++) {}
    return dest;
}

size_t str_len(const char *str) {
    size_t size = 0;
    while (*str++) {
        ++size;
    }
    return size;
}

void test_string_methods() {


    std::string name_0 = "class";
    std::string name_1 = "cstring";
    std::string *p1 = &name_0, *p2 = &name_1;
    std::cout << "String compare function: " << ' ' << str_cmp(p1, p2) << std::endl;


    char name[50] = "XXXXX ";
    char last_name[] = "YYYYYYY";
    char *temp = str_cat(name, last_name);
    std::cout << "String concatenation: ";
    std::puts(temp);


    char dest[50];
    const char *src = "strcpy function call example";
    str_cpy(dest, src);
    std::cout << dest << std::endl;


    const char *str = "How many characters in this string?";
    std::cout << "The length is " << str_len(str) << " chars." << std::endl;
}