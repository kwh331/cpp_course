//
// Created by kwh331 on 6/28/2018.
//

#include "test_higher_order_functions.h"
#include "custom_ver_higher_order_functions.h"
#include <iostream>
#include <algorithm>
#include <string>

void test_reduce();

void test_sort();

void test_transform();

void test_filter();

void test_custom_version_of_higher_order_functions() {
    test_reduce();
    test_sort();
    test_transform();
    test_filter();
}

template<class T>
inline T add_val(const T &a, const T &b) { return a + b; }

void test_reduce() {
    std::vector<int> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto y = reduce(x.begin(), x.end());
    std::cout << y << std::endl;
    y = reduce(x.begin(), x.end(), 0);
    std::cout << y << std::endl;
    y = reduce(x.begin(), x.end(), 0, [](const int &a, const int &b) { return a + b; });
    std::cout << y << std::endl;
    y = reduce(x.begin(), x.end(), 0, add_val<int>);
    std::cout << y << std::endl;
}

void test_sort() {
    std::vector<int> x = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    sort(x.begin(), x.end());
    std::cout << "\n[ ";
    std::for_each(x.begin(), x.end(), [](const int &a) { std::cout << a << ' '; });
    std::cout << "]\n";
    sort(x.begin(), x.end(), [](const int &a, const int &b) { return a > b; });
    std::cout << "\n[ ";
    std::for_each(x.begin(), x.end(), [](const int &a) { std::cout << a << ' '; });
    std::cout << "]\n";
}

void test_transform() {
    std::vector<std::string> s = {"A", "B", "C", "D"};
    transform(s.begin(), s.end(), s.begin(),
              [](const std::string &c) { return c + "x"; });
    std::cout << "\n[ ";
    std::for_each(s.begin(), s.end(), [](const std::string &c) { std::cout << c << ' '; });
    std::cout << "]\n";
    std::vector<std::string> t = {"tAs", "tBs", "tCs", "tDs"};
    transform(s.begin(), s.end(), t.begin(), t.begin(),
              [](const std::string &c, const std::string &r) { return c + r; });
    std::cout << "\n[ ";
    std::for_each(t.begin(), t.end(), [](const std::string &c) { std::cout << c << ' '; });
    std::cout << "]\n";
}

void test_filter() {
    std::string str1 = "Text with some   spaces";
    str1.erase(std::remove(str1.begin(), str1.end(), ' '),
               str1.end());
    std::cout << str1 << '\n';
    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
    str2.erase(std::remove_if(str2.begin(), str2.end(),
                              [](unsigned char x) { return std::isspace(x); }), str2.end());
    std::cout << str2 << std::endl;
}
