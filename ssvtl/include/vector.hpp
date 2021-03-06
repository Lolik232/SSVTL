//
// Created by vladv on 01.05.2022.
//

#ifndef SSVTL_VECTOR_HPP
#define SSVTL_VECTOR_HPP


#include <memory>
#include <exception>
#include <sstream>
#include <iostream>

/*  done
 *
 *  at
 *  operator[]
 *  front
 *  back
 *  data
 *  size
 *  capacity
 *  resize
 *  emplace_back
 *  empty
 *  reserve
 *  push_back
 *  clear
 *  pop_back - pop_front(additional)
 *
 * */

/*  vector methods
 *
 *  max_size
 *
 *  shrink_to_fit
 *
 *  insert
 *  emplace
 *  erase
 *
 *
 *  swap
 * */

template<typename T>
class VectorIterator : std::iterator<std::random_access_iterator_tag, T> {
private:
    using _alloc = std::allocator<T>;
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = typename std::allocator_traits<_alloc>::difference_type;
    using iterator_category = std::random_access_iterator_tag;
    using size_type = typename std::allocator_traits<_alloc>::size_type;

    using it = VectorIterator;
    using iterator_traits = std::iterator_traits<it>;

public:
    explicit VectorIterator(pointer value) {
        m_value = value;
    }

    VectorIterator(it& other) noexcept:
            m_value(other.m_value) {
    }

    VectorIterator(it&& other) noexcept:
            m_value(std::move(other.m_value)) {
    }

    reference operator*() noexcept {
        return *m_value;
    }

    pointer operator->() noexcept {
        return m_value;
    }

    const VectorIterator& operator++() noexcept {
        m_value++;
        return *this;
    }

    VectorIterator operator++(int) noexcept {
        VectorIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    VectorIterator& operator--() noexcept {
        m_value--;
        return *this;
    }

    VectorIterator operator--(int) noexcept {
        VectorIterator tmp = *this;
        --(*this);
        return tmp;
    }

    VectorIterator& operator=(const VectorIterator& other) noexcept {
        m_value = other.m_value;
        return *this;
    }

    VectorIterator& operator+=(const size_type n) noexcept {
        m_value += n;
        return *this;
    }

    VectorIterator& operator-=(const size_type n) noexcept {
        m_value -= n;
        return *this;
    }

    VectorIterator operator+(const size_type n) noexcept {
        VectorIterator tmp = *this;
        tmp += n;
        return tmp;
    }

    VectorIterator operator-(const size_type n) noexcept {
        VectorIterator tmp = *this;
        tmp -= n;
        return tmp;
    }

    size_type operator-(const VectorIterator<T> other) noexcept {
        return m_value - other.m_value;
    }

    VectorIterator operator[](size_type n) noexcept {
        return *this + n;
    }

    bool operator<(VectorIterator& other) {
        return m_value < other.m_value;
    }

    bool operator>(VectorIterator& other) {
        return m_value > other.m_value;
    }

    bool operator==(VectorIterator& other) {
        return m_value == other.m_value;
    }

    bool operator!=(VectorIterator& other) {
        return m_value != other.m_value;
    }

    bool operator>=(VectorIterator& other) {
        return m_value >= other.m_value;
    }

    bool operator<=(VectorIterator& other) {
        return m_value <= other.m_value;
    }

private:
    pointer m_value;
};


namespace Ssvtl {
    template<typename T, typename Alloc = std::allocator<T>>
    class Vector {
    private:
        using _alloc_traits = std::allocator_traits<Alloc>;

    public:
        // ?????? ?????????????????????????? ???? ?????????????????????? ??????????????????????
        using _alloc = Alloc;

        using value_type = T;
        using reference = T&;
        using const_reference = const T&;

        using pointer = typename _alloc_traits::pointer;
        using const_pointer = typename _alloc_traits::const_pointer;

        using size_type = typename _alloc_traits::size_type;
        using difference_type = typename _alloc_traits::difference_type;

        using iterator = VectorIterator<value_type>;

        explicit Vector() = default;

        explicit Vector(size_type size) {
            resize(size);
        }

        Vector(std::initializer_list<value_type> list) : Vector(
                std::distance(list.begin(), list.end())) {

            _assignRange(list.begin(), list.end());
        }

        Vector(Vector& other) noexcept {
            reserve(other.capacity());
            resize(other.size());
            std::copy(other.begin(), other.end(), begin());
        }

        Vector(Vector&& other) noexcept
                : m_data(std::move(other.m_data)),
                  m_size(std::move(other.m_size)),
                  m_capacity(std::move(other.m_capacity)) {
        }

        pointer data() noexcept {
            return m_data;
        }

        reference operator[](size_type n) noexcept {
            return m_data[n];
        }

        reference at(size_type n) {
            _outOfRangeCheck(n);

            return (*this)[n];
        };

        reference front() {
            return *begin();
        }

        reference back() {
            if (size() == 0)
                return front();
            return *(end() - 1);
        }

        size_type size() const noexcept {
            return m_size;
        }

        iterator begin() noexcept {
            return iterator(m_data);
        }

        iterator end() noexcept {
            return begin() + size();
        }

        size_type capacity() noexcept {
            return m_capacity;
        }

        void resize(const size_type newSize) {
            if (newSize < size()) {
                iterator startDestroy = begin() + newSize;
                iterator endDestroy = end();

                if (std::is_destructible_v<value_type>)
                    std::destroy(startDestroy, endDestroy);
            }

            if (newSize > size()) {
                if (capacity() < newSize) {
                    _reallocMem(newSize);
                }
            }

            m_size = newSize;
        }

        template<typename... ValT>
        decltype(auto) emplace_back(ValT&& ... values) {
            if (size() == capacity()) {
                _addMem();
            }

            m_size++;
            *back() = value_type(std::forward<ValT>(values)...);
        }

        [[nodiscard]] bool empty() const noexcept {
            return size() == 0;
        }

        void reserve(size_type n) {
            if (n > capacity()) {
                _reallocMem(n);
            }
        }

        void push_back(value_type val) {
            if (size() >= capacity()) {
                _addMem();
            }

            m_size++;
            back() = val;
        }

        void clear() noexcept {
            if (size() == 0) {
                return;
            }

            _destroyRange(begin(), end());
            m_size = 0;
        }

        void pop_back() {
            _destroy(end() - 1);
            m_size--;
        }

        void pop_front() {
            _destroy(begin());
            if (std::is_move_assignable_v<value_type>) {
                std::move(begin() + 1, end(), iterator(begin()));
            } else {
                std::copy(begin() + 1, end(), iterator(begin()));
            }
            m_size--;
        }

        ~Vector() {
            resize(0);
        }

    private:
        pointer m_data = nullptr;
        size_type m_size = 0;
        size_type m_capacity = 0;

        template<typename It>
        void _assignRange(It first, It last) {
            iterator next = begin();
            iterator _end = end();
            // TODO: next != end
            for (; first != last; ++first, ++next) {
                *next = *first;
            }
        }

        void _outOfRangeCheck(size_type index) {
            if (index >= size()) {
                std::stringstream msgs;
                msgs << "vector::_outOfRangeCheck"
                     << '\n' << '\t' << "index is " << index << " >= "
                     << "vector.size()"
                     << " is "
                     << size();

                throw std::out_of_range(msgs.str());
            }
        }

        void _reallocMem(const size_type newCapacity) {
            std::allocator<value_type> alloc;

            pointer newMem;

            if (newCapacity != 0) {
                newMem = alloc.allocate(newCapacity);
                if (newMem == nullptr)
                    throw std::bad_alloc();

                if (std::is_move_assignable_v<value_type>) {
                    std::move(begin(), end(), iterator(newMem));
                } else {
                    std::copy(begin(), end(), iterator(newMem));
                }
            } else {
                newMem = nullptr;
            }

            if (m_data != nullptr) {
                _destroyRange(begin(), end());
                alloc.deallocate(m_data, capacity());
            }
//            auto newMem = static_cast<pointer>(
//                    std::realloc(static_cast<void*>(m_data),
//                                 sizeof(value_type) * newCapacity));
//            if (newCapacity != 0 && newMem == nullptr) {
//                throw std::bad_alloc();
//            }

            m_data = newMem;
            m_capacity = newCapacity;
        }

        void _addMem() {
            size_type newCapacity = size() == 0 ? 1 : size() * 2;
            _reallocMem(newCapacity);
        }

        void _destroy(iterator pos) {
            _destroyRange(pos, pos + 1);
        }

        void _destroyRange(iterator first, iterator end) {
            if (std::is_destructible_v<value_type> == false)
                return;
//            _alloc_traits::destroy()

            std::destroy(first, end);
        }
    };
}

#endif //SSVTL_VECTOR_HPP