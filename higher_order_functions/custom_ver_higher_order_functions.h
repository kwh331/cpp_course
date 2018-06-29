//
// Created by kwh331 on 6/28/2018.
//

#ifndef HIGHER_ORDER_FUNCTIONS_CUSTOM_VER_HIGHER_ORDER_FUNCTIONS_H
#define HIGHER_ORDER_FUNCTIONS_CUSTOM_VER_HIGHER_ORDER_FUNCTIONS_H

#include <iterator>
#include <vector>
#include <iostream>
#include <algorithm>

template<class InputIt>
typename std::iterator_traits<InputIt>::value_type reduce(InputIt first, InputIt last) {
    typename std::iterator_traits<InputIt>::value_type result;
    for (auto &i = first; i != last; ++i) result += *i;
    return result;
}

template<class InputIt, class T>
T reduce(InputIt first, InputIt last, T init) {
    for (auto &i = first; i != last; ++i) init += *i;
    return init;
}

template<class InputIt, class T, class BinaryOp>
T reduce(InputIt first, InputIt last, T init, BinaryOp op) {
    for (auto &i = first; i != last; ++i) init = op(init, *i);
    return init;
};
namespace {
    template<class RandomIt>
    void merge(RandomIt &first, RandomIt &last) {
        std::vector<typename std::iterator_traits<RandomIt>::value_type> temp_lst;
        auto middle = first + std::distance(first, last) / 2;
        auto i = first, j = middle;
        for (; i < middle && j < last;) {
            if (*i <= *j) {
                temp_lst.push_back(*i);
                ++i;
            } else {
                temp_lst.push_back(*j);
                ++j;
            }
        }
        for (; i < middle; ++i) temp_lst.push_back(*i);
        for (; j < last; ++j) temp_lst.push_back(*j);
        for (auto k = 0; k < temp_lst.size(); ++k) *(first + k) = temp_lst[k];
    }

    template<class RandomIt>
    void MergeSort(RandomIt &first, RandomIt &last) {
        if (std::distance(first, last) == 1) return;
        auto middle = std::distance(first, last) / 2;
        MergeSort(first, first + middle);
        MergeSort(first + middle, last);
        merge(first, last);
    }

    template<class RandomIt, class Compare>
    void merge(RandomIt &first, RandomIt &last, Compare &comp) {
        std::vector<typename std::iterator_traits<RandomIt>::value_type> temp_lst;
        auto middle = first + std::distance(first, last) / 2;
        auto i = first, j = middle;
        for (; i < middle && j < last;) {
            if (comp(*i, *j)) {
                temp_lst.push_back(*i);
                ++i;
            } else {
                temp_lst.push_back(*j);
                ++j;
            }
        }
        for (; i < middle; ++i) temp_lst.push_back(*i);
        for (; j < last; ++j) temp_lst.push_back(*j);
        for (auto k = 0; k < temp_lst.size(); ++k) *(first + k) = temp_lst[k];
    }

    template<class RandomIt, class Compare>
    void MergeSort(RandomIt &first, RandomIt &last, Compare &comp) {
        if (std::distance(first, last) == 1) return;
        auto middle = std::distance(first, last) / 2;
        MergeSort(first, first + middle);
        MergeSort(first + middle, last);
        merge(first, last, comp);
    }
}

template<class RandomIt>
void sort(RandomIt &first, RandomIt &last) {
    MergeSort(first, last);
}

template<class RandomIt, class Compare>
void sort(RandomIt &first, RandomIt &last, Compare comp) {
    MergeSort(first, last, comp);
}

template<class InputIt, class OutputIt, class UnaryOperation>
OutputIt transform(InputIt &first1, InputIt &last1, OutputIt &d_first, UnaryOperation unary_op) {
    while (first1 != last1) {

        *d_first = unary_op(*first1);
        ++first1;
        ++d_first;
    }
    return d_first;
}

template<class InputIt1, class InputIt2, class OutputIt, class BinaryOperation>
OutputIt transform(InputIt1 &first1, InputIt1 &last1, InputIt2 &first2, OutputIt &d_first, BinaryOperation binary_op) {
    while (first1 != last1) {
        *d_first = binary_op(*first1, *first2);
        ++first1;
        ++first2;
        ++d_first;
    }
    return d_first;
}

template<class ForwardIt, class T>
ForwardIt filter(ForwardIt first, ForwardIt last, const T &value) {
    first = std::find(first, last, value);
    if (first != last)
        for (ForwardIt i = first; ++i != last;)
            if (!(*i == value))
                *first++ = std::move(*i);
    return first;
}

template<class ForwardIt, class UnaryPredicate>
ForwardIt filter(ForwardIt first, ForwardIt last, UnaryPredicate p) {
    first = std::find_if(first, last, p); // first value that satisfies the remove criteria
    if (first != last) // if there is a value that satisfies the remove criteria
        for (ForwardIt i = first; ++i != last;)
            if (!p(*i))                        // *i does not satisfies the remove criteria
                *first++ = std::move(*i);
    return first;
}

#endif //HIGHER_ORDER_FUNCTIONS_CUSTOM_VER_HIGHER_ORDER_FUNCTIONS_H
