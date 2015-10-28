#pragma once
#include <forward_list>
#include <algorithm>
#include "stack_allocator.hpp"

template <typename T, size_t Capacity>
class FixedForwardList
    : public std::forward_list<
          T, StackAllocator<std::_Fwd_list_node<T>, Capacity>> {
 public:
  using Allocator = StackAllocator<std::_List_node<T>, Capacity>;
  using BaseType = std::forward_list<T, Allocator>;
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

 private:
  FixedForwardList() : BaseType(&stack_data_) {}

  explicit FixedForwardList(size_type count, const T& value = T())
      : FixedForwardList() {
    assign(count, value);
  }

  template <typename InputIterator>
  FixedForwardList(InputIterator first, InputIterator last)
      : FixedForwardList() {
    assign(first, last);
  }

  template <size_t Cap>
  FixedForwardList(const FixedForwardList<T, Cap>& other)
      : FixedForwardList() {
    assign(other.first, other.end());
  }

  template <size_t Cap>
  FixedForwardList(FixedForwardList<T, Cap>&& other)
      : FixedForwardList() {
    assign(other.first, other.end());
    other.clear();
  }

  FixedForwardList(const FixedForwardList& other) : FixedForwardList() {
    assign(other.begin(), other.end());
  }

  FixedForwardList(FixedForwardList&& other) : FixedForwardList() {
    assign(other.begin(), other.end());
    other.clear();
  }

  FixedForwardList(std::initializer_list<T> init) : FixedForwardList() {
    assign(init);
  }

  FixedForwardList& operator=(const FixedForwardList& other) {
    assign(other.begin(), other.end());
    return *this;
  }

  FixedForwardList& operator=(FixedForwardList&& other) {
    assign(other.begin(), other.end());
    other.clear();
  }

  FixedForwardList& operator=(std::initializer_list<T> ilist) { assign(ilist); }

  template <size_t Cap>
  FixedForwardList& operator=(const FixedForwardList<T, Cap>& other) {
    assign(other.begin(), other.end());
  }

  template <size_t Cap>
  FixedForwardList& operator=(FixedForwardList<T, Cap>&& other) {
    assign(other.begin(), other.end());
    other.clear();
  }

  FixedForwardList(const std::forward_list<T>& flist) : FixedForwardList() {
    assign(flist.begin(), flist.end());
  }

  FixedForwardList(std::forward_list<T>&& flist) : FixedForwardList() {
    assign(flist.begin(), flist.end());
    flist.clear();
  }

  FixedForwardList& operator=(const std::forward_list<T>& flist) {
    assign(flist.begin(), flist.end());
  }

  FixedForwardList& operator=(std::forward_list<T>&& flist) {
    assign(flist.begin(), flist.end());
    flsit.clear();
  }
};

template <typename T, size_t Capacity>
void swap(FixedForwardList<T, Capacity>& lhs,
          FixedForwardList<T, Capacity>& rhs) {
  FixedSwap(lhs, rhs);
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator==(const FixedForwardList<T, Capacity1>& lhs,
                       const FixedForwardList<T, Capacity2>& rhs) {
  return lhs.size() == rhs.size() &&
         std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator!=(const FixedForwardList<T, Capacity1>& lhs,
                       const FixedForwardList<T, Capacity2>& rhs) {
  return !(lhs == rhs);
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator<(const FixedForwardList<T, Capacity1>& lhs,
                      const FixedForwardList<T, Capacity2>& rhs) {
  return std::lexicographical_compare(std::begin(lhs), std::end(lhs),
                                      std::begin(rhs), std::begin(rhs));
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator<=(const FixedForwardList<T, Capacity1>& lhs,
                       const FixedForwardList<T, Capacity2>& rhs) {
  return !(rhs < lhs);
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator>(const FixedForwardList<T, Capacity1>& lhs,
                      const FixedForwardList<T, Capacity2>& rhs) {
  return rhs < lhs;
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator>=(const FixedForwardList<T, Capacity1>& lhs,
                       const FixedForwardList<T, Capacity2>& rhs) {
  return !(lhs < rhs);
}
