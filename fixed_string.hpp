#pragma once
#include <string>
#include <algorithm>
#include "stack_allocator_vec.hpp"

template <typename CharT, size_t Capacity>
class FixedBasicString
    : public std::basic_string<CharT, std::char_traits<char>,
                               StackAllocatorVector<CharT, Capacity>> {
 public:
  using BaseType = std::basic_string<CharT, std::char_traits<CharT>,
                                     StackAllocatorVector<CharT, Capacity>>;
  using Allocator = StackAllocatorVector<CharT, Capacity>;
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

  FixedBasicString() : BaseType(Allocator(&stack_data_)) { reserve(Capacity); }

  explicit FixedBasicString(size_type n) : FixedBasicString() { resize(n); }

  explicit FixedBasicString(size_type n, const CharT& value)
      : FixedBasicString() {
    assign(n, value);
  }

  FixedBasicString(const FixedBasicString& other) : FixedBasicString() {
    assign(other.begin(), other.end());
  }

  FixedBasicString(FixedBasicString&& other) : FixedBasicString() {
    assign(other.begin(), other.end());
    other.clear();
  }

  FixedBasicString(const CharT* s, size_type count) : FixedBasicString() {
    assign(s, count);
  }

  FixedBasicString(const CharT* s) : FixedBasicString() { assign(s); }

  ~FixedBasicString() = default;

  FixedBasicString(std::initializer_list<CharT> ilist) { assign(ilist); }

  FixedBasicString& operator=(const FixedBasicString<CharT, Capacity>& other) {
    assign(other.begin(), other.end());
    return *this;
  }

  FixedBasicString& operator=(std::initializer_list<CharT> ilist) {
    assign(ilist);
    return *this;
  }

  template <typename InputIterator>
  FixedBasicString(InputIterator first, InputIterator last)
      : FixedBasicString() {
    assign(first, last);
  }

  FixedBasicString(const std::basic_string<CharT>& other) : FixedBasicString() {
    assign(other);
  }

  FixedBasicString(std::basic_string<CharT>&& other) : FixedBasicString() {
    assign(other);
    other.clear();
  }

  FixedBasicString& operator=(const std::basic_string<CharT>& other) {
    assign(other);
  }

  FixedBasicString& operator=(std::basic_string<CharT>&& other) {
    assign(other);
    other.clear();
  }

  // rewrite this function
  void shrink_to_fit() {
    Allocator alloc = get_allocator();
    if (alloc.use_stack_memory()) {
      return;
    }
    // copy back from heap to stack
    if (size() < Capacity) {
      FixedBasicString tmp(*this);
      tmp.swap(*this);
    } else {
      BaseType::shrink_to_fit();
    }
  }

 private:
  ReservsedMemoryType stack_data_;
};

template <typename T, size_t Capacity>
void swap(FixedBasicString<T, Capacity>& lhs,
          FixedBasicString<T, Capacity>& rhs) {
  FixedSwap(lhs, rhs);
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator==(const FixedBasicString<T, Capacity1>& lhs,
                       const FixedBasicString<T, Capacity2>& rhs) {
  return lhs.compare(rhs) == 0;
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator!=(const FixedBasicString<T, Capacity1>& lhs,
                       const FixedBasicString<T, Capacity2>& rhs) {
  return !(lhs == rhs);
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator<(const FixedBasicString<T, Capacity1>& lhs,
                      const FixedBasicString<T, Capacity2>& rhs) {
  return lhs.compare(rhs) < 0;
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator<=(const FixedBasicString<T, Capacity1>& lhs,
                       const FixedBasicString<T, Capacity2>& rhs) {
  return !(rhs < lhs);
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator>(const FixedBasicString<T, Capacity1>& lhs,
                      const FixedBasicString<T, Capacity2>& rhs) {
  return rhs < lhs;
}

template <typename T, size_t Capacity1, size_t Capacity2>
inline bool operator>=(const FixedBasicString<T, Capacity1>& lhs,
                       const FixedBasicString<T, Capacity2>& rhs) {
  return !(lhs < rhs);
}

template <size_t Capacity>
using FixedString = FixedBasicString<char, Capacity>;

template <size_t Capacity>
using FixedWString = FixedBasicString<wchar_t, Capacity>;

template <size_t Capacity>
using FixedU16String = FixedBasicString<char16_t, Capacity>;

template <size_t Capacity>
using FixedU32String = FixedBasicString<char32_t, Capacity>;
