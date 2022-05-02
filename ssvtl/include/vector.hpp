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
 *
 * */

/*  vector methods
 *
 *  empty
 *  max_size
 *  reserve
 *  shrink_to_fit
 *
 *  clear
 *  insert
 *  emplace
 *  erase
 *  push_back
 *  pop_back - pop_front(additional)
 *
 *  swap
 * */

template<typename Vec>
class VectorIterator : std::random_access_iterator_tag {
public:
    using value_type = typename Vec::value_type;
    using pointer = typename Vec::pointer;
    using reference = typename Vec::reference;
    using size_type = typename Vec::size_type;
    using it = VectorIterator<Vec>;

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

    VectorIterator operator+=(const size_type n) noexcept {
        m_value += n;
        return *this;
    }

    VectorIterator operator-=(const size_type n) noexcept {
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

    VectorIterator operator[](size_type n) noexcept {
        return *this + n;
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
        // для совместимости со стандартной библиотекой
        using _alloc = Alloc;

        using value_type = T;
        using reference = T&;
        using const_reference = const T&;

        using pointer = typename _alloc_traits::pointer;
        using const_pointer = typename _alloc_traits::const_pointer;

        using size_type = typename _alloc_traits::size_type;
        using difference_type = typename _alloc_traits::difference_type;

        using iterator = VectorIterator<Vector<value_type>>;

        explicit Vector() = default;

        explicit Vector(size_type size) {
            resize(size);
        }

        Vector(std::initializer_list<value_type> list) : Vector(
                std::distance(list.begin(), list.end())) {

            _assignRange(list.begin(), list.end());
        }

        Vector(Vector& other) noexcept
                : m_data(std::copy(other.m_data)),
                  m_size(std::copy(other.m_size)),
                  m_capacity(std::copy(other.m_capacity)) {
        }

        Vector(Vector&& other) noexcept
                : m_data(std::copy(other.m_data)),
                  m_size(std::copy(other.m_size)),
                  m_capacity(std::copy(other.m_capacity)) {
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
            if (size() == 0)
                throw std::length_error("vector is empty");
            return *begin();
        }

        reference back() {
            if (size() == 0)
                throw std::length_error("vector is empty");
            return *(--end());
        }

        size_type size() noexcept {
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
//                std::destroy(startDestroy, endDestroy);
            }
            if (newSize > size()) {
                if (capacity() < newSize) {
                    m_data = static_cast<pointer>(
                            std::realloc(static_cast<void*>(data()),
                                         sizeof(value_type) * newSize));
                    if (newSize != 0 && data() == nullptr) {
                        throw std::bad_alloc();
                    }
                    m_capacity = newSize;
                }
            }

            m_size = newSize;
        }

        template<typename... ValT>
        decltype(auto) emplace_back(ValT&& ... values) {
            // TODO: push_back
            resize(size() + 1);
            reference _val = at(size() - 1);
            // _val = std::forward<>()

            _val = value_type(std::forward<ValT>(values)...);
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
                msgs << "vector" << "vector::_outOfRangeCheck"
                     << "\n" << index << ">= " << "vector.size()" << " is "
                     << size();

                throw std::out_of_range(msgs.str());
            }
        }
    };


}

#endif //SSVTL_VECTOR_HPP
