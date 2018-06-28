//
// Created by kwh331 on 6/28/2018.
//

#include "test_rational_number_class.h"
#include <iostream>

void test_rational_num() {
    auto one = rational_num(1, 4);
    std::cout << one.to_string() << '\n';
    auto two = rational_num(1, 2);
    std::cout << std::endl;
    std::cout << (one + two).to_string() << '\n';
    std::cout << (two - one).to_string() << '\n';
    std::cout << (one / two).to_string() << '\n';
    std::cout << (one * two).to_string() << '\n';
    std::cout << std::endl;
    one += two;
    std::cout << one.to_string() << '\n';
    one -= two;
    std::cout << one.to_string() << '\n';
    one /= two;
    std::cout << one.to_string() << '\n';
    one *= two;
    std::cout << one.to_string() << '\n';
}
