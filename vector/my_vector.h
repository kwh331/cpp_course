//
// Created by kwh331 on 6/18/2018.
//

#ifndef VECTOR_MY_VECTOR_H
#define VECTOR_MY_VECTOR_H

#include <memory>
#include <initializer_list>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <iostream>

template<class T>
class My_Vector {
public:
    typedef std::allocator<T> allocator_type;
    typedef typename std::allocator<T>::size_type size_type;
    typedef typename std::allocator<T>::value_type value_type;
    typedef typename std::allocator<T>::pointer pointer;
    typedef typename std::allocator<T>::reference reference;
private:
    pointer elements = nullptr;
    size_type num_elem = 0, space = 16;
    allocator_type memory_manager;
public:
    My_Vector() : elements{memory_manager.allocate(16)} {}

    explicit My_Vector(size_type count) : num_elem{0}, space{count}, elements{memory_manager.allocate(count)} {}

    explicit My_Vector(size_type count, const T &value) : num_elem{0}, space{count},
                                                          elements{memory_manager.allocate(count)} {
        for (auto i = 0; i < count; ++i) memory_manager.construct(elements + i, value);
    };

    My_Vector(std::initializer_list<T> lst) : num_elem{lst.size()}, space{lst.size()},
                                              elements{memory_manager.allocate(lst.size())} {
        std::copy(lst.begin(), lst.end(), elements);
    }

    My_Vector(const My_Vector &other) : num_elem{other.num_elem}, space{other.space},
                                        elements{memory_manager.allocate(other.space)} {
        std::copy(other.begin(), other.end(), elements);
    }

    My_Vector &operator=(const My_Vector &other) {
        clear();
        num_elem = other.num_elem;
        space = other.space;
        elements = memory_manager.allocate(space);
        std::copy(other.begin(), other.end(), elements);
    }

    My_Vector(My_Vector<T> &&other) noexcept : num_elem{other.num_elem}, space{other.space} {
        clear();
        elements = other.elements;
        memory_manager = other.memory_manager;
        other.clear();
    }

    ~My_Vector() { clear(); }

    allocator_type &get_allocator() { return memory_manager; }

    reference at(size_type pos) {
        if (pos >= num_elem) throw std::out_of_range("");
        return elements[pos];
    }

    const reference at(size_type pos) const {
        if (pos >= num_elem) throw std::out_of_range("");
        return elements[pos];
    }

    reference operator[](size_type pos) { return elements[pos]; }

    const reference operator[](size_type pos) const { return elements[pos]; }

    reference front() { return elements[0]; }

    const reference front() const { return elements[0]; }

    reference back() { return elements[num_elem - 1]; }

    const reference back() const { return elements[num_elem - 1]; }

    pointer data() noexcept { return elements; }

    const pointer data() const noexcept { return elements; }

    class iterator {
    public:
        typedef typename std::allocator<T>::difference_type difference_type;
        typedef std::random_access_iterator_tag iterator_category;
        typedef typename std::allocator<T>::size_type size_type;
        typedef typename std::allocator<T>::value_type value_type;
        typedef typename std::allocator<T>::pointer pointer;
        typedef typename std::allocator<T>::reference reference;
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
        pointer ptr = &elements[0];
        return iterator(ptr);
    }

    iterator begin() const noexcept {
        pointer ptr = &elements[0];
        return iterator(ptr);
    }

    iterator end() noexcept {
        pointer ptr = &elements[num_elem];
        return iterator(ptr);
    }

    iterator end() const noexcept {
        pointer ptr = &elements[num_elem];
        return iterator(ptr);
    }

    bool empty() const noexcept { return num_elem == 0; }

    size_type size() const noexcept { return num_elem; }

    size_type max_size() const noexcept { return unsigned(-1); }

    void reserve(size_type new_cap) {
        if (new_cap > max_size()) throw std::length_error("");
        if (new_cap > space) {
            pointer new_elements = nullptr;
            auto temp = num_elem;
            try {
                new_elements = memory_manager.allocate(new_cap);
            } catch (const std::bad_alloc &e) {
                std::cerr << e.what() << std::endl;
                return;
            }
            std::copy(begin(), end(), new_elements);
            clear();
            num_elem = temp;
            space = new_cap;
            elements = new_elements;
            new_elements = nullptr;
        }
    }

    size_type capacity() const noexcept { return space; }

    void shrink_to_fit() {
        if (num_elem == space - 1) return;
        auto temp = num_elem;
        auto new_elements = memory_manager.allocate(num_elem);
        std::copy(begin(), end(), new_elements);
        clear();
        num_elem = temp;
        space = temp;
        elements = new_elements;
    }

    void clear() noexcept {
        for (auto i = 0; i < space; ++i) memory_manager.destroy(elements + i);
        memory_manager.deallocate(elements, space);
        num_elem = 0;
        space = 0;
        elements = nullptr;
    }

    iterator insert(iterator pos, const value_type value) {
        reserve(num_elem + 1);
        memory_manager.construct(end().get_ptr(), elements[num_elem - 1]);
        for (auto i = --end(); i != pos; --i) {
            memory_manager.destroy(i.get_ptr());
            memory_manager.construct(i.get_ptr(), *(i - 1));
        }
        memory_manager.destroy(pos.get_ptr());
        memory_manager.construct(pos.get_ptr(), value);
        ++num_elem;
        return pos;
    }

    iterator erase(iterator pos) {
        for (auto i = pos; i != end(); ++i) {
            memory_manager.destroy(i.get_ptr());
            memory_manager.construct(i.get_ptr(), *(i + 1));
        }
        --num_elem;
    }

    void push_back(T &&value) {
        if (num_elem == space) reserve(space * 2);
        memory_manager.construct(elements + num_elem, value);
        ++num_elem;
    }

    void push_back(const reference value) {
        if (num_elem == space) reserve(space * 2);
        memory_manager.construct(elements + num_elem, value);
        ++num_elem;
    }

    void pop_back() {
        pointer ptr = &elements[num_elem - 1];
        memory_manager.destroy(ptr);
        --num_elem;
    }

    void resize(size_type count) {
        reserve(count);  // guarantee that the vector has enough space
        pointer ptr;
        if (num_elem > count) {
            for (auto i = num_elem - 1; i > count; --i) {
                ptr = &elements[i];
                memory_manager.destroy(ptr);
            }
        } else {
            for (auto i = num_elem - 1; i < count; ++i) {
                ptr = &elements[i];
                memory_manager.construct(ptr, T());
            }
        }
        num_elem = count;
    }

    void resize(size_type count, const reference value) {
        reserve(count);
        pointer ptr;
        if (num_elem > count) {
            for (auto i = num_elem - 1; i > count; --i) {
                ptr = &elements[i];
                memory_manager.destroy(ptr);
            }
        } else {
            for (auto i = num_elem - 1; i < count; ++i) {
                ptr = &elements[i];
                memory_manager.construct(ptr, value);
            }
        }
        num_elem = count;
    }

};



#endif //VECTOR_MY_VECTOR_H