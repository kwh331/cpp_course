//
// Created by kwh331 on 6/29/2018.
//

#ifndef FIXED_SIZE_ARRAY_MARRAY_H
#define FIXED_SIZE_ARRAY_MARRAY_H

#include <initializer_list>
#include <algorithm>
#include <stdexcept>

template<class T, size_t N>
class m_array {
    T list[N];
    size_t elem_num = N;
public:
    m_array() {
        for (auto &i: list) i = T();
    }

    m_array(std::initializer_list<T> lst) {
        std::copy(lst.begin(), lst.end(), list);
    }


    m_array &operator=(const m_array &other) {
        for (auto i = 0; i < elem_num; ++i) {
            list[i] = other[i];
        }
    }

    inline T &operator[](size_t pos) { return list[pos]; }

    inline const T &operator[](size_t pos) const { return list[pos]; }

    T &at(size_t pos) {
        if (pos < 0 || pos >= elem_num) throw std::out_of_range("Outside bounds element access.");
        return list[pos];
    }

    const T &at(ssize_t pos) const {
        if (pos < 0 || pos >= elem_num) throw std::out_of_range("Outside bounds element access.");
        return list[pos];
    }

    inline T &front() { return list[0]; }

    inline const T &front() const { return list[0]; }

    inline T &back() { return list[elem_num - 1]; }

    inline const T &back() const { return list[elem_num - 1]; }

    T *data() noexcept { return list; }

    const T *data() const noexcept { return list; }

    class iterator {
    public:
        typedef size_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;
        typedef size_t size_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
    private:
        pointer pos;
    public:
        iterator() : pos{nullptr} {}

        iterator(const iterator &other) {
            this->pos = other.pos;
        }

        explicit iterator(pointer elem_ptr) {
            this->pos = elem_ptr;
        }

        ~iterator() { pos = nullptr; }

        iterator &operator=(const iterator &other) {
            this->pos = other.pos;
            return *this;
        }

        bool operator==(const iterator &other) const { return this->pos == other.pos; }

        bool operator!=(const iterator &other) const { return this->pos != other.pos; }

        bool operator<(const iterator &other) const { return this->pos < other.pos; }

        bool operator>(const iterator &other) const { return this->pos > other.pos; }

        bool operator<=(const iterator &other) const { return this->pos <= other.pos; }

        bool operator>=(const iterator &other) const { return this->pos >= other.pos; }

        iterator &operator++() {
            ++pos;
            return *this;
        }

        const iterator operator++(int) {
            iterator temp(*this);
            operator++();
            return temp;
        }

        iterator &operator--() {
            --pos;
            return *this;
        }

        iterator &operator-=(size_type val) {
            pos -= val;
            return *this;
        }


        iterator operator+(size_type val) const {
            iterator temp(val + pos);
            return temp;
        }

        iterator &operator+=(size_type val) {
            pos += val;
            return *this;
        }

        const iterator operator--(int) {
            iterator temp(*this);
            --pos;
            return temp;
        }

        iterator operator-(size_type val) const {
            iterator temp(pos - val);
            return temp;
        }

        difference_type operator-(iterator other) const { return pos - other.pos; }

        reference operator*() const { return *pos; }

        pointer get_ptr() { return pos; }

        reference operator[](size_type val) const { return pos[val]; }
    };

    iterator begin() noexcept {
        T *ptr = &list[0];
        return iterator(ptr);
    }

    const iterator begin() const noexcept {
        T *ptr = &list[0];
        return iterator(ptr);
    }

    iterator end() noexcept {
        T *ptr = &list[elem_num];
        return iterator(ptr);
    }

    const iterator end() const noexcept {
        T *ptr = &list[elem_num];
        return iterator(ptr);
    }


    bool empty() const noexcept { return elem_num == 0; }

    size_t size() const noexcept { return elem_num; }

    size_t max_size() const noexcept { return unsigned(-1); }

    void fill(const T &value) {
        for (auto &i: list) i = value;
    }

    void swap(m_array &other) noexcept {
        try {
            for (auto i = 0; i < elem_num; ++i) std::swap(list[i], other[i]);
        } catch (...) {
            return;
        }
    }
};

#endif //FIXED_SIZE_ARRAY_MARRAY_H
