#pragma once
#include <set>
#include <algorithm>
#include "stack_allocator.hpp"

// TODO consider not to use internal type
template <typename T>
using __std_tree_node_t = std::_Rb_tree_node<T>;

template <typename T, size_t Capacity, typename Compare = std::less<T>>
class FixedSet
    : public std::set<T, Compare,
                      StackAllocator<__std_tree_node_t<T>, Capacity>> {
 public:
  using Allocator = StackAllocator<__std_tree_node_t<T>, Capacity>;
  using BaseType = std::set<T, Compare, Allocator>;
  using ReservsedMemoryType = typename Allocator::ReservedMemory;

  using key_type = typename BaseType::key_type;
  using value_type = typename BaseType::value_type;
  using key_compare = typename BaseType::key_compare;
  using value_compare = typename BaseType::value_compare;

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

  using BaseType::insert;
  using BaseType::size;
  using BaseType::begin;
  using BaseType::end;

  FixedSet() : FixedSet(Compare()) {}

  explicit FixedSet(const Compare& comp)
      : BaseType(comp, Allocator(&stack_data_)) {}

  template <typename InputIterator>
  FixedSet(InputIterator first, InputIterator last,
           const Compare& comp = Compare())
      : FixedSet(comp) {
    insert(first, last);
  }

  FixedSet(const FixedSet& other) : FixedSet() {
    insert(std::begin(other), std::end(other));
  }

  FixedSet(FixedSet&& other) : FixedSet() {
    insert(std::begin(other), std::end(other));
    other.clear();
  }

  FixedSet(std::initializer_list<T> init) : FixedSet() { insert(init); }

  ~FixedSet() = default;

  FixedSet& operator=(const FixedSet& other) {
    insert(std::begin(other), std::end(other));
    return *this;
  }

  FixedSet& operator=(FixedSet&& other) {
    insert(std::begin(other), std::end(other));
    other.clear();
    return *this;
  }

  FixedSet& operator=(std::initializer_list<T> init) {
    insert(init);
    return *this;
  }

  template <typename Comp, typename Alloc>
  FixedSet(const std::set<T, Comp, Alloc>& other)
      : FixedSet() {
    insert(std::begin(other), std::end(other));
  }

  template <typename Comp, typename Alloc>
  FixedSet(std::set<T, Comp, Alloc>&& other)
      : FixedSet() {
    insert(std::begin(other), std::end(other));
    other.clear();
  }

  template <typename Comp, typename Alloc>
  FixedSet& operator=(const std::set<T, Comp, Alloc>& other) {
    insert(std::begin(other), std::end(other));
    return *this;
  }

  template <typename Comp, typename Alloc>
  FixedSet& operator=(std::set<T, Comp, Alloc>&& other) {
    insert(std::begin(other), std::end(other));
    other.clear();
    return *this;
  }

 private:
  ReservsedMemoryType stack_data_;
};

template <typename T, size_t Capacity, typename Compare>
void swap(FixedSet<T, Capacity, Compare>& lhs,
          FixedSet<T, Capacity, Compare>& rhs) {
  FixedSwap(lhs, rhs);
}

template <typename T, size_t Capacity1, size_t Capacity2, typename Compare>
inline bool operator==(const FixedSet<T, Capacity1, Compare>& lhs,
                       const FixedSet<T, Capacity2, Compare>& rhs) {
  return lhs.size() == rhs.size() &&
         std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
}

template <typename T, size_t Capacity1, size_t Capacity2, typename Compare>
inline bool operator!=(const FixedSet<T, Capacity1, Compare>& lhs,
                       const FixedSet<T, Capacity2, Compare>& rhs) {
  return !(lhs == rhs);
}

template <typename T, size_t Capacity1, size_t Capacity2, typename Compare>
inline bool operator<(const FixedSet<T, Capacity1, Compare>& lhs,
                      const FixedSet<T, Capacity2, Compare>& rhs) {
  return std::lexicographical_compare(std::begin(lhs), std::end(lhs),
                                      std::begin(rhs), std::begin(rhs));
}

template <typename T, size_t Capacity1, size_t Capacity2, typename Compare>
inline bool operator<=(const FixedSet<T, Capacity1, Compare>& lhs,
                       const FixedSet<T, Capacity2, Compare>& rhs) {
  return !(rhs < lhs);
}

template <typename T, size_t Capacity1, size_t Capacity2, typename Compare>
inline bool operator>(const FixedSet<T, Capacity1, Compare>& lhs,
                      const FixedSet<T, Capacity2, Compare>& rhs) {
  return rhs < lhs;
}

template <typename T, size_t Capacity1, size_t Capacity2, typename Compare>
inline bool operator>=(const FixedSet<T, Capacity1, Compare>& lhs,
                       const FixedSet<T, Capacity2, Compare>& rhs) {
  return !(lhs < rhs);
}

// definitoin for FixedMutiSet

template <typename T, size_t Capacity, typename Compare = std::less<T>>
class FixedMultiSet
    : public std::multiset<T, Compare,
                           StackAllocator<__std_tree_node_t<T>, Capacity>> {
 public:
  using Allocator = StackAllocator<__std_tree_node_t<T>, Capacity>;
  using BaseType = std::multiset<T, Compare, Allocator>;
  using ReservsedMemoryType = typename Allocator::ReservedMemory;

  using key_type = typename BaseType::key_type;
  using value_type = typename BaseType::value_type;
  using key_compare = typename BaseType::key_compare;
  using value_compare = typename BaseType::value_compare;

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

  using BaseType::insert;
  using BaseType::size;
  using BaseType::begin;
  using BaseType::end;
  FixedMultiSet() : BaseType(Compare(), Allocator(&stack_data_)) {}

  explicit FixedMultiSet(const Compare& comp = Compare())
      : BaseType(comp, Allocator(&stack_data_)) {}

  template <typename InputIterator>
  FixedMultiSet(InputIterator first, InputIterator last,
                const Compare& comp = Compare())
      : FixedMultiSet(comp) {
    insert(first, last);
  }

  FixedMultiSet(const FixedMultiSet& other) : FixedMultiSet() {
    insert(std::begin(other), std::end(other));
  }

  FixedMultiSet(FixedMultiSet&& other) : FixedMultiSet() {
    insert(std::begin(other), std::end(other));
    other.clear();
  }

  FixedMultiSet(std::initializer_list<T> init) : FixedMultiSet() {
    insert(init);
  }

  ~FixedMultiSet() = default;

  FixedMultiSet& operator=(const FixedMultiSet& other) {
    insert(std::begin(other), std::end(other));
    return *this;
  }

  FixedMultiSet& operator=(FixedMultiSet&& other) {
    insert(std::begin(other), std::end(other));
    other.clear();
    return *this;
  }

  FixedMultiSet& operator=(std::initializer_list<T> init) {
    insert(init);
    return *this;
  }

  template <typename Comp, typename Alloc>
  FixedMultiSet(const std::multiset<T, Comp, Alloc>& other)
      : FixedMultiSet() {
    insert(std::begin(other), std::end(other));
  }

  template <typename Comp, typename Alloc>
  FixedMultiSet(std::multiset<T, Comp, Alloc>&& other)
      : FixedMultiSet() {
    insert(std::begin(other), std::end(other));
    other.clear();
  }

  template <typename Comp, typename Alloc>
  FixedMultiSet& operator=(const std::multiset<T, Comp, Alloc>& other) {
    insert(std::begin(other), std::end(other));
    return *this;
  }

  template <typename Comp, typename Alloc>
  FixedMultiSet& operator=(std::multiset<T, Comp, Alloc>&& other) {
    insert(std::begin(other), std::end(other));
    other.clear();
    return *this;
  }

 private:
  ReservsedMemoryType stack_data_;
};

template <typename T, size_t Capacity, typename Compare>
void swap(FixedMultiSet<T, Capacity, Compare>& lhs,
          FixedMultiSet<T, Capacity, Compare>& rhs) {
  FixedMultiSwap(lhs, rhs);
}

template <typename T, size_t Capacity1, size_t Capacity2, typename Compare>
inline bool operator==(const FixedMultiSet<T, Capacity1, Compare>& lhs,
                       const FixedMultiSet<T, Capacity2, Compare>& rhs) {
  return lhs.size() == rhs.size() &&
         std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
}

template <typename T, size_t Capacity1, size_t Capacity2, typename Compare>
inline bool operator!=(const FixedMultiSet<T, Capacity1, Compare>& lhs,
                       const FixedMultiSet<T, Capacity2, Compare>& rhs) {
  return !(lhs == rhs);
}

template <typename T, size_t Capacity1, size_t Capacity2, typename Compare>
inline bool operator<(const FixedMultiSet<T, Capacity1, Compare>& lhs,
                      const FixedMultiSet<T, Capacity2, Compare>& rhs) {
  return std::lexicographical_compare(std::begin(lhs), std::end(lhs),
                                      std::begin(rhs), std::begin(rhs));
}

template <typename T, size_t Capacity1, size_t Capacity2, typename Compare>
inline bool operator<=(const FixedMultiSet<T, Capacity1, Compare>& lhs,
                       const FixedMultiSet<T, Capacity2, Compare>& rhs) {
  return !(rhs < lhs);
}

template <typename T, size_t Capacity1, size_t Capacity2, typename Compare>
inline bool operator>(const FixedMultiSet<T, Capacity1, Compare>& lhs,
                      const FixedMultiSet<T, Capacity2, Compare>& rhs) {
  return rhs < lhs;
}

template <typename T, size_t Capacity1, size_t Capacity2, typename Compare>
inline bool operator>=(const FixedMultiSet<T, Capacity1, Compare>& lhs,
                       const FixedMultiSet<T, Capacity2, Compare>& rhs) {
  return !(lhs < rhs);
}
