//
// Created by Fadet on 30.04.2022.
//

#ifndef SSVTL_LIST_H
#define SSVTL_LIST_H

#include <algorithm>

#ifndef size_t
#define size_t unsigned long long
#endif

namespace Ssvtl {

    template<class T>
    class Node {
    public:
        using value_type = T;

        value_type &_value;
        Node<value_type> *_next, *_prev;
    };

    template<typename Node>
    class ListIterator {
    public:
        using value_type = Node;
        using size_type = size_t;
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

        ListIterator &operator[](const size_type &offset) {
            for (size_type i = 0; i < offset; ++i)
                ++(*this);
            return *this;
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

        pointer getPointer() {
            return _ptr;
        }

    private:
        pointer _ptr;
    };

    template<class T>
    class List {
    public:
        using value_type = T;
        using size_type = size_t;
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

        List(size_type size, const value_type &value) {
            _size = size;
            for (size_type i = 0; i < size; ++i)
                this->push_back(value);
        }

        iterator begin() { return ++iterator(_head); }

        iterator end() { return iterator(_tail); }

        iterator insert(iterator pos, const value_type &value) {
            _size++;

            auto *newNode = new node_type;
            newNode->_value = value;

            return _insertPointer(pos, newNode);
        }

        iterator erase(iterator pos) {
            if (pos == this->end() ||
                pos == --(this->begin())
                    )
                return this->end();

            _size--;

            auto nextIter = _relinkPointer(pos);

            delete pos.getPointer();

            return nextIter;
        }

        void push_front(const value_type &value) {
            insert(this->begin(), value);
        }

        void push_back(const value_type &value) {
            insert(this->end(), value);
        }

        void pop_front() { erase(this->begin()); }

        void pop_back() { erase(--(this->end())); }

        void resize(size_type count, const value_type &value) {
            if (_size > count) {
                auto diff = _size - count;
                for (size_type i = 0; i < diff; ++i)
                    this->pop_back();
            } else if (_size < count) {
                auto diff = count - _size;
                for (size_type i = 0; i < diff; ++i)
                    this->push_back(value);
            }

            _size = count;
        }

        void clear() {
            for (auto it = this->begin(); it != this->end(); ++it)
                erase(it);
            _size = 0;
        }

        void swap(List &other) {
            std::swap(*this, other);
        }

        void splice(iterator pos, List &other) {
            static_assert(std::is_same_v<T, typename decltype(other)::value_type>,
                          "this and other template types must be equal!");

            for (auto it = other.begin(); it != other.end(); ++it) {
                auto ptr = it.getPointer();
                _insertPointer(pos++, ptr);
                _relinkPointer(it);
            }

            _size += other._size;
            other._size = 0;
        }

        reference front() { return *begin(); }

        reference back() { return *--end(); }


    private:
        node_type *_head;
        node_type *_tail;
        size_type _size;

        iterator _insertPointer(iterator &pos, node_type *ptr) {
            auto prevIter = --pos;
            ++pos;

            prevIter.getPoiner()->_next = ptr;
            pos.getPointer()->_prev = ptr;

            ptr->_prev = prevIter.getPointer();
            ptr->_next = pos.getPointer();

            return iterator(ptr);
        }

        iterator _relinkPointer(iterator &pos) {
            auto prevIter = --pos;
            ++pos;

            auto nextIter = ++pos;
            --pos;

            prevIter.getPointer()->_next = nextIter.getPointer();
            nextIter.getPointer()->_prev = prevIter.getPointer();

            return nextIter;
        }
    };


}

#endif //SSVTL_LIST_H
