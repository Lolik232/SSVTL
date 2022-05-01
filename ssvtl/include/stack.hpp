#ifndef SSVTL_STACK_H
#define SSVTL_STACK_H

#include <deque>

namespace Ssvtl {

  template<typename T,
      typename Container = std::deque<T>>
  class Stack;

  template<typename T,
      typename Container>
  class Stack {
  protected:
    Container container_;

  public:
    using container_type = Container;
    using ContainerT = container_type;
    using reference = typename Container::reference;
    using ReferenceT = reference;
    using const_reference = typename Container::const_reference;
    using ConstReferenceT = const_reference;
    using size_type = typename Container::size_type;
    using SizeT = size_type;
    using value_type = typename Container::value_type;
    using ValueT = value_type;

    static_assert(std::is_same_v<T, ValueT>, "container adaptors require consistent types");

    Stack() = default;

    explicit Stack(const Container& container) :
        container_(container) {}

    explicit Stack(Container&& container) noexcept:
        container_(std::move(container)) {}

    Stack(const Stack& other_stack) :
        Stack(other_stack.container_) {}

    Stack(Stack&& other_stack) noexcept:
        Stack(std::move(other_stack.container_)) {}

    template<typename Alloc,
        typename std::enable_if_t<std::uses_allocator<Container, Alloc>::value>* = nullptr>
    explicit Stack(const Alloc& alloc) noexcept:
        container_(alloc) {}

    template<typename Alloc,
        typename std::enable_if_t<std::uses_allocator<Container, Alloc>::value>* = nullptr>
    explicit Stack(const Container& container,
                   const Alloc& alloc) noexcept:
        container_(container, alloc) {}

    template<typename Alloc,
        typename std::enable_if_t<std::uses_allocator<Container, Alloc>::value>* = nullptr>
    explicit Stack(Container&& container,
                   const Alloc& alloc) noexcept:
        container_(std::move(container), alloc) {}

    template<typename Alloc,
        typename std::enable_if_t<std::uses_allocator<Container, Alloc>::value>* = nullptr>
    explicit Stack(const Stack& other_stack,
                   const Alloc& alloc) noexcept:
        container_(other_stack.container_, alloc) {}

    template<typename Alloc,
        typename std::enable_if_t<std::uses_allocator<Container, Alloc>::value>* = nullptr>
    explicit Stack(Stack&& other_stack,
                   const Alloc& alloc) noexcept:
        container_(std::move(other_stack.container_), alloc) {}

    ~Stack() = default;

    Stack& operator=(const Stack& other_stack) {
      container_ = other_stack.container_;
      return *this;
    }

    Stack& operator=(Stack&& other_stack) noexcept {
      container_ = std::move(other_stack.container_);
      return *this;
    }

    ReferenceT top() {
      return container_.back();
    }

    ReferenceT getTop() {
      return container_.back();
    }

    ConstReferenceT top() const {
      return container_.cback();
    }

    ConstReferenceT getTop() const {
      return container_.cback();
    }

    [[nodiscard]] bool empty() const {
      return container_.empty();
    }

    [[nodiscard]] bool isEmpty() const {
      return container_.empty();
    }

    SizeT size() const {
      return container_.size();
    }

    SizeT getSize() const {
      return container_.size();
    }

    /**
     * @brief Pushes the given element value to the top of the stack.
     * @param value the value of the element to push
     */
    void push(const ValueT& value) {
      container_.push_back(value);
    }

    /**
    * @brief Pushes the given element value to the top of the stack.
    * @param value the value of the element to push
    */
    void push(ValueT&& value) {
      container_.push_back(std::move(value));
    }

    template<typename... Args>
    decltype(auto) emplace(Args&& ... args) {
      container_.emplace_back(std::forward<Args>(args)...);
    }

    /**
     * @brief Removes the top element from the stack.
     */
    void pop() {
      container_.pop_back();
    }

    /**
     * @brief Exchanges the contents of the container adaptor with those of other.
     * @param other_stack container adaptor to exchange the contents with
     */
    void swap(Stack&& other_stack) {
      std::swap(container_, other_stack.container_);
    }

    friend std::compare_three_way_result_t<Container> operator<=>(const Ssvtl::Stack<T, Container>& lhs,
                                                                  const Ssvtl::Stack<T, Container>& rhs) = default;
  };
}

#endif //SSVTL_STACK_H