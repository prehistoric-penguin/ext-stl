#pragma once
#include <map>
#include <algorithm>
#include "stack_allocator.hpp"

// TODO consider not to use internal type
template <typename T>
using __std_tree_node_t = std::_Rb_tree_node<T>;

template <typename KeyType, typename ValueType, size_t Capacity,
          typename Compare = std::less<KeyType>>
class FixedMap
    : public std::map<
          KeyType, ValueType, Compare,
          StackAllocator<__std_tree_node_t<std::pair<const KeyType, ValueType>>,
                         Capacity>> {
 public:
  using Allocator =
      StackAllocator<__std_tree_node_t<std::pair<const KeyType, ValueType>>,
                     Capacity>;
  using BaseType = std::map<KeyType, ValueType, Compare, Allocator>;
  using ReservsedMemoryType = typename Allocator::ReservedMemory;

  using key_type = typename BaseType::key_type;
  using mapped_type = typename BaseType::mapped_type;
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

  FixedMap() : FixedMap(Compare()) {}

  explicit FixedMap(const Compare& comp)
      : BaseType(comp, Allocator(&stack_data_)) {}

  template <typename InputIterator>
  FixedMap(InputIterator first, InputIterator last,
           const Compare& comp = Compare())
      : FixedMap(comp) {
    insert(first, last);
  }

  FixedMap(const FixedMap& other) : FixedMap() {
    insert(std::begin(other), std::end(other));
  }

  FixedMap(FixedMap&& other) : FixedMap() {
    insert(std::begin(other), std::end(other));
    other.clear();
  }

  FixedMap(std::initializer_list<value_type> init) : FixedMap() {
    insert(init);
  }

  ~FixedMap() = default;

  FixedMap& operator=(const FixedMap& other) {
    insert(std::begin(other), std::end(other));
    return *this;
  }

  FixedMap& operator=(FixedMap&& other) {
    insert(std::begin(other), std::end(other));
    other.clear();
    return *this;
  }

  FixedMap& operator=(std::initializer_list<value_type> init) {
    insert(init);
    return *this;
  }

  template <typename Comp, typename Alloc>
  FixedMap(const std::map<KeyType, ValueType, Comp, Alloc>& other)
      : FixedMap() {
    insert(std::begin(other), std::end(other));
  }

  template <typename Comp, typename Alloc>
  FixedMap(std::map<KeyType, ValueType, Comp, Alloc>&& other)
      : FixedMap() {
    insert(std::begin(other), std::end(other));
    other.clear();
  }

  template <typename Comp, typename Alloc>
  FixedMap& operator=(const std::map<KeyType, ValueType, Comp, Alloc>& other) {
    insert(std::begin(other), std::end(other));
    return *this;
  }

  template <typename Comp, typename Alloc>
  FixedMap& operator=(std::map<KeyType, ValueType, Comp, Alloc>&& other) {
    insert(std::begin(other), std::end(other));
    other.clear();
    return *this;
  }

 private:
  ReservsedMemoryType stack_data_;
};

template <typename KeyType, typename ValueType, size_t Capacity,
          typename Compare>
void swap(FixedMap<KeyType, ValueType, Capacity, Compare>& lhs,
          FixedMap<KeyType, ValueType, Capacity, Compare>& rhs) {
  FixedSwap(lhs, rhs);
}

template <typename KeyType, typename ValueType, size_t Capacity1,
          size_t Capacity2, typename Compare>
inline bool operator==(
    const FixedMap<KeyType, ValueType, Capacity1, Compare>& lhs,
    const FixedMap<KeyType, ValueType, Capacity2, Compare>& rhs) {
  return lhs.size() == rhs.size() &&
         std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
}

template <typename KeyType, typename ValueType, size_t Capacity1,
          size_t Capacity2, typename Compare>
inline bool operator!=(
    const FixedMap<KeyType, ValueType, Capacity1, Compare>& lhs,
    const FixedMap<KeyType, ValueType, Capacity2, Compare>& rhs) {
  return !(lhs == rhs);
}

template <typename KeyType, typename ValueType, size_t Capacity1,
          size_t Capacity2, typename Compare>
inline bool operator<(
    const FixedMap<KeyType, ValueType, Capacity1, Compare>& lhs,
    const FixedMap<KeyType, ValueType, Capacity2, Compare>& rhs) {
  return std::lexicographical_compare(std::begin(lhs), std::end(lhs),
                                      std::begin(rhs), std::begin(rhs));
}

template <typename KeyType, typename ValueType, size_t Capacity1,
          size_t Capacity2, typename Compare>
inline bool operator<=(
    const FixedMap<KeyType, ValueType, Capacity1, Compare>& lhs,
    const FixedMap<KeyType, ValueType, Capacity2, Compare>& rhs) {
  return !(rhs < lhs);
}

template <typename KeyType, typename ValueType, size_t Capacity1,
          size_t Capacity2, typename Compare>
inline bool operator>(
    const FixedMap<KeyType, ValueType, Capacity1, Compare>& lhs,
    const FixedMap<KeyType, ValueType, Capacity2, Compare>& rhs) {
  return rhs < lhs;
}

template <typename KeyType, typename ValueType, size_t Capacity1,
          size_t Capacity2, typename Compare>
inline bool operator>=(
    const FixedMap<KeyType, ValueType, Capacity1, Compare>& lhs,
    const FixedMap<KeyType, ValueType, Capacity2, Compare>& rhs) {
  return !(lhs < rhs);
}

// definition for FixedMultiMap

template <typename KeyType, typename ValueType, size_t Capacity,
          typename Compare = std::less<KeyType>>
class FixedMultiMap
    : public std::multimap<
          KeyType, ValueType, Compare,
          StackAllocator<__std_tree_node_t<std::pair<const KeyType, ValueType>>,
                         Capacity>> {
 public:
  using Allocator =
      StackAllocator<__std_tree_node_t<std::pair<const KeyType, ValueType>>,
                     Capacity>;
  using BaseType = std::multimap<KeyType, ValueType, Compare, Allocator>;
  using ReservsedMemoryType = typename Allocator::ReservedMemory;

  using key_type = typename BaseType::key_type;
  using mapped_type = typename BaseType::mapped_type;
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

  FixedMultiMap() : FixedMultiMap(Compare()) {}

  explicit FixedMultiMap(const Compare& comp)
      : BaseType(comp, Allocator(&stack_data_)) {}

  template <typename InputIterator>
  FixedMultiMap(InputIterator first, InputIterator last,
                const Compare& comp = Compare())
      : FixedMultiMap(comp) {
    insert(first, last);
  }

  FixedMultiMap(const FixedMultiMap& other) : FixedMultiMap() {
    insert(std::begin(other), std::end(other));
  }

  FixedMultiMap(FixedMultiMap&& other) : FixedMultiMap() {
    insert(std::begin(other), std::end(other));
    other.clear();
  }

  FixedMultiMap(std::initializer_list<value_type> init) : FixedMultiMap() {
    insert(init);
  }

  ~FixedMultiMap() = default;

  FixedMultiMap& operator=(const FixedMultiMap& other) {
    insert(std::begin(other), std::end(other));
    return *this;
  }

  FixedMultiMap& operator=(FixedMultiMap&& other) {
    insert(std::begin(other), std::end(other));
    other.clear();
    return *this;
  }

  FixedMultiMap& operator=(std::initializer_list<value_type> init) {
    insert(init);
    return *this;
  }

  template <typename Comp, typename Alloc>
  FixedMultiMap(const std::multimap<KeyType, ValueType, Comp, Alloc>& other)
      : FixedMultiMap() {
    insert(std::begin(other), std::end(other));
  }

  template <typename Comp, typename Alloc>
  FixedMultiMap(std::multimap<KeyType, ValueType, Comp, Alloc>&& other)
      : FixedMultiMap() {
    insert(std::begin(other), std::end(other));
    other.clear();
  }

  template <typename Comp, typename Alloc>
  FixedMultiMap& operator=(
      const std::multimap<KeyType, ValueType, Comp, Alloc>& other) {
    insert(std::begin(other), std::end(other));
    return *this;
  }

  template <typename Comp, typename Alloc>
  FixedMultiMap& operator=(
      std::multimap<KeyType, ValueType, Comp, Alloc>&& other) {
    insert(std::begin(other), std::end(other));
    other.clear();
    return *this;
  }

 private:
  ReservsedMemoryType stack_data_;
};

template <typename KeyType, typename ValueType, size_t Capacity,
          typename Compare>
void swap(FixedMultiMap<KeyType, ValueType, Capacity, Compare>& lhs,
          FixedMultiMap<KeyType, ValueType, Capacity, Compare>& rhs) {
  FixedMultiSwap(lhs, rhs);
}

template <typename KeyType, typename ValueType, size_t Capacity1,
          size_t Capacity2, typename Compare>
inline bool operator==(
    const FixedMultiMap<KeyType, ValueType, Capacity1, Compare>& lhs,
    const FixedMultiMap<KeyType, ValueType, Capacity2, Compare>& rhs) {
  return lhs.size() == rhs.size() &&
         std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs));
}

template <typename KeyType, typename ValueType, size_t Capacity1,
          size_t Capacity2, typename Compare>
inline bool operator!=(
    const FixedMultiMap<KeyType, ValueType, Capacity1, Compare>& lhs,
    const FixedMultiMap<KeyType, ValueType, Capacity2, Compare>& rhs) {
  return !(lhs == rhs);
}

template <typename KeyType, typename ValueType, size_t Capacity1,
          size_t Capacity2, typename Compare>
inline bool operator<(
    const FixedMultiMap<KeyType, ValueType, Capacity1, Compare>& lhs,
    const FixedMultiMap<KeyType, ValueType, Capacity2, Compare>& rhs) {
  return std::lexicographical_compare(std::begin(lhs), std::end(lhs),
                                      std::begin(rhs), std::begin(rhs));
}

template <typename KeyType, typename ValueType, size_t Capacity1,
          size_t Capacity2, typename Compare>
inline bool operator<=(
    const FixedMultiMap<KeyType, ValueType, Capacity1, Compare>& lhs,
    const FixedMultiMap<KeyType, ValueType, Capacity2, Compare>& rhs) {
  return !(rhs < lhs);
}

template <typename KeyType, typename ValueType, size_t Capacity1,
          size_t Capacity2, typename Compare>
inline bool operator>(
    const FixedMultiMap<KeyType, ValueType, Capacity1, Compare>& lhs,
    const FixedMultiMap<KeyType, ValueType, Capacity2, Compare>& rhs) {
  return rhs < lhs;
}

template <typename KeyType, typename ValueType, size_t Capacity1,
          size_t Capacity2, typename Compare>
inline bool operator>=(
    const FixedMultiMap<KeyType, ValueType, Capacity1, Compare>& lhs,
    const FixedMultiMap<KeyType, ValueType, Capacity2, Compare>& rhs) {
  return !(lhs < rhs);
}
