//
// Created by kwh331 on 6/25/2018.
//

#include "mlist.h"
#include <iostream>


void test_mlist_class() {
    mlist<double> one(1000, 345.2345324532);
    mlist<double> two;
    mlist<double> three = {134.345, 345.12345, 4.234543, 23435.34, 8765.34, 23.4, 2145.324, 99.66};
    mlist<double> five(three);
    mlist<double> six(mlist<double>(30, 435.345));
    mlist<double> seven = three;
    five.clear();
    one.clear();
    two.clear();
    three.clear();
    five.clear();
    six.clear();
    seven.clear();

    mlist<double> list = {243.34, 3.345, 4.90, 5.234, 4.11, 2.34, 3.3451, 31, 342.989, 3.234, 4324, 32.676};

    std::cout << "[ ";
    std::for_each(list.begin(), list.end(), [](const double &val) { std::cout << val << " "; });
    std::cout << "]\n";

    std::cout << "The size of the list is: " << list.size() << '.' << std::endl;
    std::cout << "The first element is: " << list.front() << '.' << std::endl;
    std::cout << "The last element is: " << list.back() << ".\n\n";

    list.pop_front();
    std::cout << "[ ";
    std::for_each(list.begin(), list.end(), [](const double &val) { std::cout << val << " "; });
    std::cout << "]\n";
    std::cout << "The size of the list after pop_front is: " << list.size() << '.' << std::endl;
    std::cout << "The first element after pop_front is: " << list.front() << ".\n\n";

    list.pop_back();
    std::cout << "[ ";
    std::for_each(list.begin(), list.end(), [](const double &val) { std::cout << val << " "; });
    std::cout << "]\n";
    std::cout << "The last element after pop_back is: " << list.back() << '.' << std::endl;
    std::cout << "The size of the list after pop_back is: " << list.size() << ".\n\n";

    list.push_front(777.111);
    std::cout << "[ ";
    std::for_each(list.begin(), list.end(), [](const double &val) { std::cout << val << " "; });
    std::cout << "]\n";
    std::cout << "The size of the list after push_front is: " << list.size() << '.' << std::endl;
    std::cout << "The first element after push_front is: " << list.front() << '.' << std::endl;
    std::cout << "The last element after push_front is: " << list.back() << ".\n\n";


    list.push_back(666.555);
    std::cout << "[ ";
    std::for_each(list.begin(), list.end(), [](const double &val) { std::cout << val << " "; });
    std::cout << "]\n";
    std::cout << "The size of the list after push_back is: " << list.size() << '.' << std::endl;
    std::cout << "The first element after push_back is: " << list.front() << '.' << std::endl;
    std::cout << "The last element after push_back is: " << list.back() << ".\n\n";

    list.resize(16, 3.14);
    std::cout << "[ ";
    std::for_each(list.begin(), list.end(), [](const double &val) { std::cout << val << " "; });
    std::cout << "]\n";
    std::cout << "The size of the list after resize(16, 3.14) is: " << list.size() << ".\n\n";

    list.sort();
    std::cout << "[ ";
    std::for_each(list.begin(), list.end(), [](const double &val) { std::cout << val << " "; });
    std::cout << "]\n";
    std::cout << "The list after calling sort with it.\n\n";

    list.resize(5);
    std::cout << "[ ";
    std::for_each(list.begin(), list.end(), [](const double &val) { std::cout << val << " "; });
    std::cout << "]\n";
    std::cout << "The size of the list after resize(5) is: " << list.size() << ".\n\n";

}