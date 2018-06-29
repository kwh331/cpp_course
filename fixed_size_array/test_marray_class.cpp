//
// Created by kwh331 on 6/29/2018.
//

#include "test_marray_class.h"
#include <iostream>

void test_array() {
    m_array<int, 10> list = {9, 7, 4, 3, 6, 7, 2, 8, 1, 10};
    std::cout << " operator[1] " << list[1] << std::endl;
    try {
        std::cout << list.at(3454) << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "The size of the array : " << list.size() << '\n';
    std::cout << "list elements \n [ ";
    std::for_each(list.begin(), list.end(), [](const int &a) { std::cout << a << ' '; });
    std::cout << "] \n";
    auto list_two = list;
    std::sort(list.begin(), list.end());
    std::cout << "After std::sort\n [ ";
    std::for_each(list.begin(), list.end(), [](const int &a) { std::cout << a << ' '; });
    std::cout << "] \n";
    std::cout << "list two elements \n [ ";
    std::for_each(list_two.begin(), list_two.end(), [](const int &a) { std::cout << a << ' '; });
    std::cout << "] \n";
    list_two.swap(list);
    std::cout << "list_two elements after swap with list\n [ ";
    std::for_each(list_two.begin(), list_two.end(), [](const int &a) { std::cout << a << ' '; });
    std::cout << "] \n";
    list_two.fill(331);
    std::cout << "list_two elements after fill(331)\n [ ";
    std::for_each(list_two.begin(), list_two.end(), [](const int &a) { std::cout << a << ' '; });
    std::cout << "] \n";
}
