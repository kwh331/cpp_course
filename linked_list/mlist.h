//
// Created by kwh331 on 6/25/2018.
//

#ifndef LINKED_LIST_MLIST_H
#define LINKED_LIST_MLIST_H

#include <iterator>
#include <memory>
#include <initializer_list>
#include <algorithm>
#include <vector>

template<class T>
class mlist {
public:
    typedef typename std::allocator<T>::value_type value_type;
    typedef typename std::allocator<T>::pointer pointer;
    typedef typename std::allocator<T> allocator_type;
    typedef typename std::allocator<T>::reference reference;
    typedef typename std::allocator<T>::const_reference const_reference;
    typedef typename std::allocator<T>::size_type size_type;
private:
    class node {
    public:
        T *data = nullptr;
        node *next = nullptr;
        node *prev = nullptr;

        node() = default;

        explicit node(node *prev_node, node *next_next) : prev{prev_node}, next{next_next} {}
    };

    allocator_type memory_manager;
    std::allocator<node> node_allocator;
    node *start_node = nullptr;
    node *end_node = nullptr;
    size_type elem_num = 0;

public:
    mlist() = default;

    explicit mlist(size_type count, const T &value = T()) {
        for (auto i = 0; i < count; ++i) {
            push_back(value);
        }
    }

    mlist(std::initializer_list<T> lst) {
        for (auto i = lst.begin(); i != lst.end(); ++i) {
            push_back(*i);
        }
    }

    mlist(const mlist<T> &other) {
        for (auto i = other.begin(); i != other.end(); ++i) {
            push_back(*i);
        }

    }

    mlist<T> &operator=(const mlist<T> &other) {
        clear();
        for (auto i = other.begin(); i != other.end(); ++i) {
            push_back(*i);
        }
        return *this;
    }

    mlist(mlist<T> &&other) noexcept {
        elem_num = other.elem_num;
        start_node = other.start_node;
        end_node = other.end_node;
        other.start_node = nullptr;
        other.end_node = nullptr;
        other.elem_num = 0;
    }

    ~mlist() { clear(); }

    allocator_type get_allocator() const { return memory_manager; }

    T &front() { return *(start_node->data); }

    const T &front() const { return *(start_node->data); }

    T &back() { return *(end_node->data); }

    const T &back() const { return *(end_node->data); }

private:
    class iterator {
        node *pos;
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef typename std::allocator<T>::size_type size_type;
        typedef typename std::allocator<T>::value_type value_type;
        typedef typename std::allocator<node>::pointer pointer;
        typedef typename std::allocator<node>::reference reference;

        iterator() : pos{nullptr} {};

        iterator(const iterator &other) {
            pos = other.pos;
        }

        explicit iterator(node *elem_ptr) {
            pos = elem_ptr;
        }

        ~iterator() {
            pos = nullptr;
        }

        iterator &operator=(const iterator &other) {
            pos = other.pos;
            return *this;
        }

        bool operator==(const iterator &other) const { return pos == other.pos; }

        bool operator!=(const iterator &other) const { return pos != other.pos; }

        bool operator<(const iterator &other) const { return pos < other.pos; }

        bool operator>(const iterator &other) const { return pos > other.pos; }

        bool operator<=(const iterator &other) const { return pos <= other.pos; }

        bool operator>=(const iterator &other) const { return pos >= other.pos; }

        iterator &operator++() {
            pos = pos->next;
            return *this;
        }

        const iterator operator++(int) {
            iterator temp(*this);
            operator++();
            return temp;
        }

        iterator &operator--() {
            pos = pos->prev;
            return *this;
        }

        const iterator operator--(int) {
            iterator temp(*this);
            operator--();
            return temp;
        }

        const T &operator*() const { return *(pos->data); }

        T &operator*() { return *(pos->data); }

    private:
        node *get_ptr() { return pos; }

        node *get_ptr() const { return pos; }
    };

public:
    typedef const iterator const_iterator;

    iterator begin() noexcept { return iterator(start_node); }

    const_iterator begin() const noexcept { return iterator(start_node); }

    iterator end() noexcept { return iterator(); }

    const_iterator end() const noexcept { return iterator(); }

    bool empty() const noexcept { return elem_num == 0; }

    size_type size() const noexcept { return elem_num; }

    size_type max_size() const noexcept { return unsigned(-1); }

    void clear() noexcept {
        if (elem_num > 0) {
            auto link = start_node;
            while (link != nullptr) {
                memory_manager.destroy(link->data);  // destroying T class object
                memory_manager.deallocate(link->data, 1); // freeing memory allocated for T class object
                auto prev_link = link;
                link = link->next;
                node_allocator.destroy(prev_link);  // destroying node class object
                node_allocator.deallocate(prev_link, 1);  // freeing memory allocated for node class object
            }
            elem_num = 0;
            start_node = nullptr;
            end_node = nullptr;
        }
    }

    // insert value before position
    iterator insert(const_iterator position, const T &value) {
        node *node_to_insert = node_allocator.allocate(1);
        node_allocator.construct(node_to_insert, node());
        node_to_insert->data = memory_manager.allocate(1);
        memory_manager.construct(node_to_insert->data, value);
        auto current_object = position.get_ptr();
        node_to_insert->next = current_object;
        node_to_insert->prev = current_object->prev;
        current_object->prev = node_to_insert;
        ++elem_num;
        return iterator(node_to_insert);
    }

    iterator erase(iterator position) {
        auto node_to_delete = position.get_ptr();
        node_to_delete->prev->next = node_to_delete->next;
        memory_manager.destroy(node_to_delete->data);
        memory_manager.deallocate(node_to_delete->data, 1);
        node_allocator.destroy(node_to_delete);
        node_allocator.deallocate(node_to_delete, 1);
        --elem_num;
        return ++position;
    }

    void push_back(const T &value) {
        if (elem_num >= 2) {
            node *new_node = node_allocator.allocate(1);
            node_allocator.construct(new_node, node());
            new_node->data = memory_manager.allocate(1);
            memory_manager.construct(new_node->data, value);
            new_node->prev = end_node;
            end_node->next = new_node;
            end_node = new_node;
        } else if (elem_num) {
            end_node = node_allocator.allocate(1);
            node_allocator.construct(end_node, node());
            end_node->data = memory_manager.allocate(1);
            memory_manager.construct(end_node->data, value);
            start_node->next = end_node;
            end_node->prev = start_node;
        } else {
            start_node = node_allocator.allocate(1);
            node_allocator.construct(start_node, node());
            start_node->data = memory_manager.allocate(1);
            memory_manager.construct(start_node->data, value);
        }
        ++elem_num;
    }

    // O(1) for doubly-linked list
    void pop_back() {
        auto node_to_delete = end_node;
        end_node = end_node->prev;
        end_node->next = nullptr;
        memory_manager.destroy(node_to_delete->data);
        memory_manager.deallocate(node_to_delete->data, 1);
        node_allocator.destroy(node_to_delete);
        node_allocator.deallocate(node_to_delete, 1);
        --elem_num;
    }

    // O(1)
    void push_front(const T &value) {
        node *new_node = node_allocator.allocate(1);
        node_allocator.construct(new_node, node());
        new_node->data = memory_manager.allocate(1);
        memory_manager.construct(new_node->data, value);
        new_node->next = start_node;
        start_node->prev = new_node;
        start_node = new_node;
        ++elem_num;
    }

    // O(1)
    void pop_front() {
        auto node_to_delete = start_node;
        start_node = start_node->next;
        start_node->prev = nullptr;
        memory_manager.destroy(node_to_delete->data);
        memory_manager.deallocate(node_to_delete->data, 1);
        node_allocator.destroy(node_to_delete);
        node_allocator.deallocate(node_to_delete, 1);
        --elem_num;
    }

    void resize(size_type count, const T &value = T()) {
        if (count > elem_num) {
            while (count != elem_num) push_back(value);
        } else {
            while (count != elem_num) pop_back();
        }
    }

    void sort() {
        std::vector<T> container_with_random_access_iterator;
        std::for_each(begin(), end(), [&](const T &val) { container_with_random_access_iterator.push_back(val); });
        clear();
        std::sort(container_with_random_access_iterator.begin(),
                  container_with_random_access_iterator.end());
        std::for_each(container_with_random_access_iterator.begin(),
                      container_with_random_access_iterator.end(), [&](const T &val) { push_back(val); });
    }


};

void test_mlist_class();

#endif //LINKED_LIST_MLIST_H
