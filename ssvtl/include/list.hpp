//
// Created by Fadet on 30.04.2022.
//

#ifndef SSVTL_LIST_H
#define SSVTL_LIST_H

#include "vector.hpp"
#include <algorithm>
#include <iostream>
#include <initializer_list>
#include <memory>

namespace Ssvtl {

    template<class T>
    class Node {
    public:
        using value_type = T;

        value_type _value = value_type();
        Node<value_type> *_next, *_prev;
    };

    template<typename Node>
    class ListIterator : std::bidirectional_iterator_tag {
    public:
        using value_type = Node;
        using size_type = size_t;
        using pointer = value_type *;
        using reference = value_type &;
        using difference_type = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using iterator_traits = std::iterator_traits<ListIterator>;
    public:
        explicit ListIterator(pointer ptr)
                : _ptr(ptr) {}

        virtual ListIterator &operator++() {
            _ptr = _ptr->_next;
            return *this;
        }

        virtual ListIterator &operator--() {
            _ptr = _ptr->_prev;
            return *this;
        }

        virtual ListIterator operator++(int) {
            ListIterator it = *this;
            ++(*this);
            return it;
        }

        virtual ListIterator operator--(int) {
            ListIterator it = *this;
            --(*this);
            return it;
        }

        typename Node::value_type &operator*() {
            return _ptr->_value;
        }

        pointer operator->() {
            return _ptr;
        }

        ListIterator &operator=(const ListIterator &other) {
            if (this == &other)
                return *this;

            this->_ptr = other._ptr;

            return *this;
        }

        bool operator==(const ListIterator &other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const ListIterator &other) const {
            return _ptr != other._ptr;
        }

        pointer getPointer() {
            return _ptr;
        }

    private:
        pointer _ptr;
    };

    template<typename Node>
    class ReverseListIterator : ListIterator<Node> {
    public:
        using value_type = Node;
        using size_type = size_t;
        using pointer = value_type *;
        using reference = value_type &;
        using difference_type = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using iterator_traits = std::iterator_traits<ReverseListIterator>;
    public:
        explicit ReverseListIterator(pointer ptr)
                : _ptr(ptr) {}

        ReverseListIterator &operator++() override {
            _ptr = _ptr->_prev;
            return *this;
        }

        ReverseListIterator &operator--() override {
            _ptr = _ptr->_next;
            return *this;
        }

        ReverseListIterator operator++(int) override {
            ReverseListIterator it = *this;
            --(*this);
            return it;
        }

        ReverseListIterator operator--(int) override {
            ReverseListIterator it = *this;
            ++(*this);
            return it;
        }

    private:
        pointer _ptr;
    };

    template<typename Node>
    class ConstListIterator : std::bidirectional_iterator_tag {
    public:
        using value_type = Node;
        using size_type = size_t;
        using pointer = value_type *;
        using reference = value_type &;
        using difference_type = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using iterator_traits = std::iterator_traits<ConstListIterator>;
    public:
        explicit ConstListIterator(pointer ptr)
                : _ptr(ptr) {}

        virtual ConstListIterator &operator++() {
            _ptr = _ptr->_next;
            return *this;
        }

        virtual ConstListIterator &operator--() {
            _ptr = _ptr->_prev;
            return *this;
        }

        virtual ConstListIterator operator++(int) {
            ConstListIterator it = *this;
            ++(*this);
            return it;
        }

        virtual ConstListIterator operator--(int) {
            ConstListIterator it = *this;
            --(*this);
            return it;
        }

        const typename Node::value_type &operator*() {
            return _ptr->_value;
        }

        ConstListIterator &operator=(const ConstListIterator &other) {
            if (this == &other)
                return *this;

            this->_ptr = other._ptr;

            return *this;
        }

        bool operator==(const ConstListIterator &other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const ConstListIterator &other) const {
            return _ptr != other._ptr;
        }

    private:
        pointer _ptr;
    };

    template<typename Node>
    class ConstReverseListIterator : ConstListIterator<Node> {
    public:
        using value_type = Node;
        using size_type = size_t;
        using pointer = value_type *;
        using reference = value_type &;
        using difference_type = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using iterator_traits = std::iterator_traits<ConstReverseListIterator>;
    public:
        explicit ConstReverseListIterator(pointer ptr)
                : _ptr(ptr) {}

        ConstReverseListIterator &operator++() override {
            _ptr = _ptr->_prev;
            return *this;
        }

        ConstReverseListIterator &operator--() override {
            _ptr = _ptr->_next;
            return *this;
        }

        ConstReverseListIterator operator++(int) override {
            ConstReverseListIterator it = *this;
            --(*this);
            return it;
        }

        ConstReverseListIterator operator--(int) override {
            ConstReverseListIterator it = *this;
            ++(*this);
            return it;
        }

    private:
        pointer _ptr;
    };

    template<class T, class Allocator = std::allocator<Node<T>>>
    class List {
    public:
        using value_type = T;
        using size_type = size_t;
        using pointer = typename std::allocator_traits<Allocator>::pointer;
        using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
        using reference = value_type &;
        using const_reference = const value_type &;
        using node_type = Node<value_type>;
        using iterator = ListIterator<node_type>;
        using const_iterator = ConstListIterator<node_type>;
        using reverse_iterator = ReverseListIterator<node_type>;
        using const_reverse_iterator = ConstReverseListIterator<node_type>;
    public:
        List() {
            std::allocator<node_type> alloc;

            _size = 0;
            pointer first = alloc.allocate(1);
            pointer last = alloc.allocate(1);

            first->_next = last;
            first->_prev = nullptr;

            last->_next = nullptr;
            last->_prev = first;

            _head = first;
            _tail = last;
        };

        explicit List(size_type size) : List() {
            for (size_type i = 0; i < size; ++i)
                this->push_back(value_type());
        }

        List(const List &other) : List() {
            _constructFromList(other);
        }

        List(size_type size, const value_type &value) : List() {
            for (size_type i = 0; i < size; ++i)
                this->push_back(value);
        }

        List(std::initializer_list<value_type> l) : List() {
            for (auto &elem: l)
                this->push_back(elem);
        }

        iterator begin() noexcept { return ++iterator(_head); }

        const_iterator begin() const noexcept { return ++const_iterator(_head); }

        iterator end() { return iterator(_tail); }

        const_iterator end() const noexcept { return const_iterator(_tail); }

        const_iterator cbegin() const noexcept { return ++const_iterator(_head); }

        const_iterator cend() const noexcept { return const_iterator(_tail); }

        reverse_iterator rbegin() noexcept { return ++reverse_iterator(_tail); }

        const_reverse_iterator rbegin() const noexcept { return ++const_reverse_iterator(_tail); }

        reverse_iterator rend() noexcept { return reverse_iterator(_head); }

        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(_head); }

        const_reverse_iterator crbegin() const noexcept { return ++const_reverse_iterator(_tail); }

        const_reverse_iterator crend() const noexcept { return reverse_iterator(_head); }

        iterator insert(iterator pos, const value_type &value) {
            std::allocator<node_type> alloc;

            _size++;

            pointer newNode = alloc.allocate(1);
            newNode->_value = value;

            return _insertPointer(pos, newNode);
        }

        iterator erase(iterator pos) {
            std::allocator<node_type> alloc;

            if (pos == this->end() ||
                pos == --(this->begin())
                    )
                return this->end();

            _size--;

            auto nextIter = _relinkPointer(pos);

            alloc.deallocate(pos.getPointer(), 1);

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

        void resize(size_type count,
                    const value_type &value = value_type()) {
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
            if (this->empty())
                return;

            for (auto it = ++this->begin(); it != this->end(); ++it) {
                auto prevIter = --it;
                ++it;

                erase(prevIter);
            }
            erase(--(this->end()));
        }

        void swap(List &other) {
            auto t = *this;
            *this = other;
            other = t;
        }

        void splice(iterator pos, List &other) {
            if (other.empty())
                return;

            auto prevIter = --pos;
            ++pos;

            prevIter->_next = other.begin().getPointer();
            other.begin()->_prev = prevIter.getPointer();

            (--other.end())->_next = pos.getPointer();
            pos->_prev = (--other.end()).getPointer();

            other._head->_next = other._tail;
            other._tail->_prev = other._head;

            _size += other._size;
            other._size = 0;
        }

        void reverse() {
            auto i = begin(), j = --end();

            auto n = _size / 2;
            for (size_type k = 0; k < n; ++k) {
                std::swap(i->_value, j->_value);
                ++i, --j;
            }
        }

        size_type remove(const value_type &value) {
            if (this->empty())
                return 0;

            size_type deleted = 0;

            for (auto it = ++this->begin(); it != this->end(); ++it) {
                auto prevIter = --it;
                ++it;

                if (*prevIter == value && ++deleted)
                    erase(prevIter);
            }
            if (*--this->end() == value)
                erase(--this->end());

            return deleted;
        }

        template<class UnaryPredicate>
        size_type remove_if(UnaryPredicate p) {
            if (this->empty())
                return 0;

            size_type deleted = 0;

            for (auto it = ++this->begin(); it != this->end(); ++it) {
                auto prevIter = --it;
                ++it;

                if (p(*prevIter) && ++deleted)
                    erase(prevIter);
            }
            if (p(*--this->end()))
                erase(--this->end());

            return deleted;
        }

        size_type unique() {
            if (this->empty())
                return 0;

            size_type deleted = 0;

            for (auto it = ++this->begin(); it != this->end(); ++it) {
                auto prevIter = --it;
                ++it;

                if (*prevIter == *it && ++deleted) {
                    erase(it);
                    it = prevIter;
                }
            }

            return deleted;
        }

        template<class BinaryPredicate>
        size_type unique(BinaryPredicate p) {
            if (this->empty())
                return 0;

            size_type deleted = 0;

            for (auto it = ++this->begin(); it != this->end(); ++it) {
                auto prevIter = --it;
                ++it;

                if (p(*prevIter, *it) && ++deleted) {
                    erase(it);
                    it = prevIter;
                }
            }

            return deleted;
        }

        void merge(List &other) {
            auto itThis = this->begin();
            auto itOther = other.begin();
            auto thisEnd = this->end();
            auto otherEnd = other.end();

            while (itThis != thisEnd && itOther != otherEnd) {
                if (*itThis == *itOther) {
                    auto copyIt = _relinkPointer(itOther);
                    _insertPointer(++itThis, itOther.getPointer());
                    itOther = copyIt;
                } else if (*itThis > *itOther) {
                    auto copyIt = _relinkPointer(itOther);
                    _insertPointer(itThis, itOther.getPointer());
                    itOther = copyIt;
                } else
                    ++itThis;
            }
            while (itOther != otherEnd) {
                auto copyIt = _relinkPointer(itOther);
                _insertPointer(thisEnd, itOther.getPointer());
                itOther = copyIt;
            }

            other._size = 0;
        }

        void sort() {
            Vector<value_type> v;
            for (const auto &x: *this)
                v.push_back(x);

            std::sort(v.begin(), v.end());

            auto it = this->begin();
            for (const auto &x: v) {
                it->_value = x;
                ++it;
            }
        }

        template<class Compare>
        void sort(Compare comp) {
            Vector<value_type> v;
            for (const auto &x: *this)
                v.push_back(x);

            std::sort(v.begin(), v.end(), comp);

            auto it = this->begin();
            for (const auto &x: v) {
                it->_value = x;
                ++it;
            }
        }

        size_type size() const noexcept { return _size; }

        [[nodiscard]] bool empty() const noexcept { return _size == 0; }

        reference front() noexcept { return *begin(); }

        const_reference front() const noexcept { return *begin(); }

        reference back() noexcept { return *--end(); }

        const_reference back() const noexcept { return *--end(); }

        List &operator=(const List &other) {
            if (this == &other)
                return *this;

            this->clear();
            this->_constructFromList(other);
            return *this;
        }

        ~List() {
            std::allocator<node_type> alloc;

            this->clear();
            alloc.deallocate(_head, 1);
            alloc.deallocate(_tail, 1);
        }

    private:
        node_type *_head;
        node_type *_tail;
        size_type _size;

        iterator _insertPointer(iterator &pos, node_type *ptr) {
            auto prevIter = --pos;
            ++pos;

            prevIter->_next = ptr;
            pos->_prev = ptr;

            ptr->_prev = prevIter.getPointer();
            ptr->_next = pos.getPointer();

            return iterator(ptr);
        }

        iterator _relinkPointer(iterator &pos) {
            auto prevIter = --pos;
            ++pos;

            auto nextIter = ++pos;
            --pos;

            prevIter->_next = nextIter.getPointer();
            nextIter->_prev = prevIter.getPointer();

            return nextIter;
        }

        void _constructFromList(const List &other) {
            for (auto it = other.begin(); it != other.end(); ++it)
                this->push_back(*it);
        }
    };
}

#endif //SSVTL_LIST_H
