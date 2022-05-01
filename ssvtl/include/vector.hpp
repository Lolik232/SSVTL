//
// Created by vladv on 01.05.2022.
//

#ifndef SSVTL_VECTOR_HPP
#define SSVTL_VECTOR_HPP


#include <memory>

/*  vector methods
 *  at
 *  operator[]
 *  front
 *  back
 *  data
 *
 *  empty
 *  size
 *  max_size
 *  reserve
 *  capacity
 *  shrink_to_fit
 *
 *  clear
 *  insert
 *  emplace
 *  erase
 *  push_back
 *  emplace_back
 *  pop_back - pop_front(additional)
 *  resize
 *
 *  swap
 *
 * */

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

    };

}

#endif //SSVTL_VECTOR_HPP
