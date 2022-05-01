//
// Created by vladv on 30.04.2022.
//

#ifndef SSVTL_QUEUE_HPP
#define SSVTL_QUEUE_HPP

#include "list.hpp"

namespace Ssvtl {

    // TODO: replace std::list for our list implementation
    template<typename T, typename Container = Ssvtl::List<T>>
    class Queue {
    public:
        // для совместимости со стандартной библиотекой
        using value_type = typename Container::value_type;
        using container_type = Container;
        using size_type = typename Container::size_type;
        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;

        // для стандартизации имён в библиотеке
        using ValueT = value_type;
        using ContainerT = container_type;
        using SizeT = size_type;
        using RefenceT = reference;
        using ConstReferenceT = const_reference;

        static_assert(std::is_same_v<T, ValueT>, "T and ValueT must be equal!");

        Queue() = default;

        RefenceT front() {
            return m_data.front();
        }

        RefenceT back() {
            return m_data.back();
        }

        void push(ConstReferenceT value) {
            m_data.push_back(value);
        }

        void pop() {
            m_data.pop_front();
        }

        SizeT size() const {
            return m_data.size();
        }

        [[nodiscard]] bool empty() const {
            return m_data.empty();
        }


    protected:
        Container m_data{};
    };
};

#endif //SSVTL_QUEUE_HPP
