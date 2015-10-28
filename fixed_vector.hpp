#pragma once
#include <vector>
#include <algorithm>
#include "stack_allocator_vec.hpp"

template <typename T, size_t Capacity>
class FixedVector : public std::vector<T, StackAllocatorVector<T, Capacity>> {
 public:
  using BaseType = std::vector<T, StackAllocatorVector<T, Capacity>>;
  using Allocator = StackAllocatorVector<T, Capacity>;
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
  using BaseType::resize;
  using BaseType::reserve;
  using BaseType::begin;
  using BaseType::end;
  using BaseType::get_allocator;
  FixedVector() : BaseType(Allocator(&stack_data_)) { reserve(Capacity); }

  explicit FixedVector(size_type n) : FixedVector() {
    resize(n);
  }

  FixedVector(size_type n, const T& value) : FixedVector() { assign(n, value); }

  FixedVector(const FixedVector& other) : FixedVector() {
    assign(other.begin(), other.end());
  }

  FixedVector(FixedVector&& other) : FixedVector() {
    std::move(other.begin(), other.end(), begin());
    other.clear();
  }

  ~FixedVector() = default;

  FixedVector(std::initializer_list<T> ilist) { assign(ilist); }

  FixedVector& operator=(const FixedVector<T, Capacity>& other) {
    assign(other.begin(), other.end());
    return *this;
  }

  FixedVector& operator=(FixedVector<T, Capacity>&& other) {
    std::move(other.begin(), other.end(), begin());
    other.clear();
    return *this;
  }

  FixedVector& operator=(std::initializer_list<T> ilist) {
    assign(ilist);
    return *this;
  }

  FixedVector(const std::vector<T>& other) : FixedVector() {
    assign(other.begin(), other.end());
  }

  FixedVector(std::vector<T>&& other) : FixedVector() {
    assign(other.begin(), other.end());
    other.clear();
  }

  FixedVector& operator=(const std::vector<T>& other) {
    assign(other.begin(), other.end());
  }

  FixedVector& operator=(std::vector<T>&& other) {
    assign(other.begin(), other.end());
    other.clear();
  }

  template <typename InputIterator>
  FixedVector(InputIterator first, InputIterator last)
      : FixedVector() {
    assign(first, last);
  }

  // rewrite this function
  void shrink_to_fit() {
    Allocator alloc = get_allocator();
    if (alloc.use_stack_memory()) {
      return;
    }
    // copy back from heap to stack
    if (size() < Capacity) {
      FixedVector tmp(*this);
      tmp.swap(*this);
    } else {
      BaseType::shrink_to_fit();
    }
  }

 private:
  ReservsedMemoryType stack_data_;
};

template <typename T, size_t Capacity>
void swap(FixedVector<T, Capacity>& lhs, FixedVector<T, Capacity>& rhs) {
  FixedSwap(lhs, rhs);
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator==(const FixedVector<T, Capacity1>& lhs,
                       const FixedVector<T, Capacity2>& rhs) {
  return lhs.size() == rhs.size() &&
         std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator!=(const FixedVector<T, Capacity1>& lhs,
                       const FixedVector<T, Capacity2>& rhs) {
  return !(lhs == rhs);
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator<(const FixedVector<T, Capacity1>& lhs,
                      const FixedVector<T, Capacity2>& rhs) {
  return std::lexicographical_compare(std::begin(lhs), std::end(lhs),
                                      std::begin(rhs), std::begin(rhs));
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator<=(const FixedVector<T, Capacity1>& lhs,
                       const FixedVector<T, Capacity2>& rhs) {
  return !(rhs < lhs);
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator>(const FixedVector<T, Capacity1>& lhs,
                      const FixedVector<T, Capacity2>& rhs) {
  return rhs < lhs;
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator>=(const FixedVector<T, Capacity1>& lhs,
                       const FixedVector<T, Capacity2>& rhs) {
  return !(lhs < rhs);
}
