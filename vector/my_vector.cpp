//
// Created by kwh331 on 6/18/2018.
//

#include "my_vector.h"

void test_My_Vector_class() {

    My_Vector<double> list;
    auto list_two(list);
    auto list_three = list_two;
    My_Vector<double> list_four(30);

    std::cout << "\nList size and capacity: " << list.size() << ", " << list.capacity() << std::endl;
    std::cout << "\nList Two size and capacity: " << list_two.size() << ", " << list_two.capacity() << std::endl;
    std::cout << "\nList Three size and capacity: " << list_three.size() << ", " << list_three.capacity() << std::endl;
    std::cout << "\nList Four size and capacity: " << list_four.size() << ", " << list_four.capacity() << std::endl;

    list_two.reserve(100);
    for (auto i = 0; i < 49; ++i) { list_two.push_back((34 - 17 * i) % 344); }
    std::cout << "\nList Two size and capacity after reserve(100): " << list_two.size() << ", " << list_two.capacity()
              << std::endl;

    list_two.shrink_to_fit();
    std::cout << "\nList Two size and capacity after shrink: " << list_two.size() << ", " << list_two.capacity()
              << std::endl;

    list_two.resize(10);
    std::cout << "\nList Two size and capacity after resize(10): " << list_two.size() << ", " << list_two.capacity()
              << std::endl;

    std::cout << "\nList Two element after resize(10).\n";
    std::for_each(list_two.begin(), list_two.end(), [](double &val) { std::cout << val << ' '; });

    list_two.pop_back();
    std::cout << "\n\nList Two element after pop_back().\n";
    std::for_each(list_two.begin(), list_two.end(), [](double &val) { std::cout << val << ' '; });


    list_two.insert(list_two.begin()+3, 777);
    std::cout << "\n\nList Two element after insert(list_two_begin()+3, 777) on fourth position.\n";
    std::for_each(list_two.begin(), list_two.end(), [](double &val) { std::cout << val << ' '; });

    auto data_ptr = list_two.data();
    std::cout << "\n Dereferencing data_ptr " << *data_ptr << std::endl;

    auto front_list_two = list_two.front();
    std::cout << "\nPrinting list_two.front() " << front_list_two << std::endl;

    auto back_list_two = list_two.back();
    std::cout << "\nPrinting list_two.back() " << back_list_two << std::endl;

    std::sort(list_two.begin(), list_two.end());
    std::cout << "\nList Two element after std::sort().\n";
    std::for_each(list_two.begin(), list_two.end(), [](double &val) { std::cout << val << ' '; });


}