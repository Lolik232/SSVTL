//
// Created by Fadet on 30.04.2022.
//

#ifndef SSVTL_LIST_H
#define SSVTL_LIST_H

#ifndef size_t
#define size_t unsigned long long
#endif

namespace Ssvtl {

    template<class T>
    class Node {
    public:
        using value_type = T;

        value_type _value;
        Node<value_type> *_next, *_prev;
    };

    template<typename Node>
    class ListIterator {
    public:
        using value_type = Node;
        using pointer = value_type *;
    public:
        explicit ListIterator(pointer ptr)
                : _ptr(ptr) {}

        ListIterator &operator++() {
            _ptr = _ptr->_next;
            return *this;
        }

        ListIterator &operator--() {
            _ptr = _ptr->_prev;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator it = *this;
            ++(*this);
            return it;
        }

        ListIterator operator--(int) {
            ListIterator it = *this;
            --(*this);
            return it;
        }

        typename Node::value_type &operator*() {
            return _ptr->_value;
        }

        bool operator==(const ListIterator &other) {
            return _ptr == other._ptr;
        }

        bool operator!=(const ListIterator &other) {
            return _ptr != other._ptr;
        }

    private:
        pointer _ptr;
    };

    template<class T>
    class List {
    public:
        using value_type = T;
        using reference = value_type &;
        using node_type = Node<value_type>;
        using iterator = ListIterator<node_type>;
    public:
        List() {
            _size = 0;
            auto *first = new node_type;
            auto *last = new node_type;

            first->_next = last;
            first->_prev = nullptr;

            last->_next = nullptr;
            last->_prev = first;

            _head = first;
            _tail = last;
        };

        List(size_t size, const value_type &value) {
            _size = size;
        }

        reference back() { return _tail->_value; }

        reference front() { return _head->_value; }

        iterator begin() { return ListIterator<node_type>(_head); }


    private:
        node_type *_head;
        node_type *_tail;
        size_t _size;
    };


}

#endif //SSVTL_LIST_H
