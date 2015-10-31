#pragma once
#include <list>
#include <algorithm>
#include "stack_allocator.hpp"

// use libstdc++'s internal type here may not be a good choice
// TODO: copy libstc++'s stl_list.h to current folder
template <typename T>
using __std_list_node_t = std::_List_node<T>;

template <typename T, size_t Capacity>
class FixedList
    : public std::list<T, StackAllocator<__std_list_node_t<T>, Capacity>> {
 public:
  using Allocator = StackAllocator<__std_list_node_t<T>, Capacity>;
  using BaseType = std::list<T, Allocator>;
  using ReservsedMemoryType = typename Allocator::ReservedMemory;

  using reference = typename BaseType::reference;
  using const_reference = typename BaseType::const_reference;
  using iterator = typename BaseType::iterator;
  using const_iterator = typename BaseType::const_iterator;
  using size_type = typename BaseType::size_type;
  using allocator_type = typename BaseType::allocator_type;
  using pointer = typename BaseType::pointer;
  using const_pointer = typename BaseType::const_pointer;
  using reverse_iterator = typename BaseType::reverse_iterator;
  using const_reverse_iterator = typename BaseType::const_reverse_iterator;

  using BaseType::assign;
  using BaseType::size;
  using BaseType::begin;
  using BaseType::end;
  using BaseType::push_back;

  FixedList() : BaseType(Allocator(&stack_data_)) {}
  explicit FixedList(size_type count, const T& value = T()) : FixedList() {
    assign(count, value);
  }

  template <typename InputIterator>
  FixedList(InputIterator first, InputIterator last)
      : FixedList() {
    assign(first, last);
  }

  FixedList(const FixedList& other) : FixedList() {
    assign(other.begin(), other.end());
  }

  FixedList(FixedList&& other) : FixedList() {
    assign(other.begin(), other.end());
    other.clear();
  }

  FixedList(std::initializer_list<T> init) : FixedList() { assign(init); }

  FixedList(const std::list<T>& other) : FixedList() {
    assign(other.begin(), other.end());
  }

  FixedList(std::list<T>&& other) : FixedList() {
    assign(other.begin(), other.end());
    other.clear();
  }

  FixedList& operator=(const FixedList& other) {
    assign(other.begin(), other.end());
  }

  FixedList& operator=(FixedList&& other) {
    assign(other.begin(), other.end());
    other.clear();
  }

  FixedList& operator=(std::initializer_list<T> init) { assign(init); }

  FixedList& operator=(const std::list<T>& other) {
    assign(other.begin(), other.end());
  }

  FixedList& operator=(std::list<T>&& other) {
    assign(other.begin(), other.end());
    other.clear();
  }

  ~FixedList() = default;

 private:
  ReservsedMemoryType stack_data_;
};

template <typename T, size_t Capacity>
void swap(FixedList<T, Capacity>& lhs, FixedList<T, Capacity>& rhs) {
  FixedSwap(lhs, rhs);
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator==(const FixedList<T, Capacity1>& lhs,
                       const FixedList<T, Capacity2>& rhs) {
  return lhs.size() == rhs.size() &&
         std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator!=(const FixedList<T, Capacity1>& lhs,
                       const FixedList<T, Capacity2>& rhs) {
  return !(lhs == rhs);
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator<(const FixedList<T, Capacity1>& lhs,
                      const FixedList<T, Capacity2>& rhs) {
  return std::lexicographical_compare(std::begin(lhs), std::end(lhs),
                                      std::begin(rhs), std::end(rhs));
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator<=(const FixedList<T, Capacity1>& lhs,
                       const FixedList<T, Capacity2>& rhs) {
  return !(rhs < lhs);
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator>(const FixedList<T, Capacity1>& lhs,
                      const FixedList<T, Capacity2>& rhs) {
  return rhs < lhs;
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator>=(const FixedList<T, Capacity1>& lhs,
                       const FixedList<T, Capacity2>& rhs) {
  return !(lhs < rhs);
}
