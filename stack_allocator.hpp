#pragma once
#include <set>  // for _Rb_tree_node
#include <memory>
#include <type_traits>
#include <iostream>
#include <cassert>
#include "utils.hpp"

template <typename T>
using __std_tree_node_t = std::_Rb_tree_node<T>;

template <typename T, size_t Capacity>
class StackAllocator : public std::allocator<T> {
 public:
  // be friend to a rebinded allocator
  template <typename U, size_t Cap>
  friend class StackAllocator;

  using pointer = typename std::allocator<T>::pointer;
  using size_type = typename std::allocator<T>::size_type;

  struct ReservedMemory {
    using AlignedStorage =
        typename std::aligned_storage<sizeof(T), alignof(T)>::type;
    struct Link {
      Link* link_;
    };

    ReservedMemory()
        : head_(nullptr),
          next_(reinterpret_cast<Link*>(buffer_)),
          tail_(reinterpret_cast<Link*>(buffer_ + Capacity)) {}

    pointer Data() { return reinterpret_cast<pointer>(buffer_); }
    pointer DataEnd() { return Data() + Capacity; }
    bool Remain() { return head_ != nullptr || next_ != tail_; }
    bool InRange(pointer p) { return p >= Data() && p < DataEnd(); }
    pointer Get() {
      pointer cur = reinterpret_cast<pointer>(head_);
      if (cur != nullptr) {
        head_ = head_->link_;
        return cur;
      } else {
        if (next_ != tail_) {
          cur = reinterpret_cast<pointer>(next_);
          next_ = reinterpret_cast<Link*>(
              reinterpret_cast<unsigned char*>(next_) + sizeof(T));
          return cur;
        } else {
          assert(0);
        }
      }
    }
    void Put(pointer p) {
      Link* cur = reinterpret_cast<Link*>(p);
      cur->link_ = head_;
      head_ = cur;
    }
    Link* head_;
    Link* next_;
    Link* tail_;

    AlignedStorage buffer_[Capacity];
  };

  template <typename U>
  struct rebind {
    using other = StackAllocator<U, Capacity>;
  };
  StackAllocator() = default;

  StackAllocator(const StackAllocator<T, Capacity>& other)
      : std::allocator<T>(), reserved_memory_(other.reserved_memory_) {}

  /*
  template <typename U, size_t OtherCapacity>
  StackAllocator(const StackAllocator<U, OtherCapacity>& other)
      : reserved_memory_(nullptr) {}
      */

  // because the libstdc++'s source use rebind twice in std::set
  // and the internal type _Rb_tree_node
  // they should share the memory
  template <typename U, size_t OtherCapacity, typename Dummy = T>
  StackAllocator(
      const StackAllocator<U, OtherCapacity>& other,
      typename std::enable_if<
          std::is_same<__std_tree_node_t<Dummy>, U>::value ||
          std::is_same<__std_tree_node_t<U>, Dummy>::value>::type* = nullptr)
      : reserved_memory_(
            reinterpret_cast<ReservedMemory*>(other.reserved_memory_)) {}

  template <typename U, size_t OtherCapacity, typename Dummy = T>
  StackAllocator(
      const StackAllocator<U, OtherCapacity>& other,
      typename std::enable_if<
          !std::is_same<__std_tree_node_t<Dummy>, U>::value &&
          !std::is_same<__std_tree_node_t<U>, Dummy>::value>::type* = nullptr)
      : reserved_memory_(nullptr) {}

  explicit StackAllocator(ReservedMemory* reserved)
      : reserved_memory_(reserved) {}

  // This allocator is for node based container
  // we can only allocator one node a time
  pointer allocate(size_type n, void* hint = 0) {
    assert(n == 1);
    if (reserved_memory_->Remain()) {
      return reserved_memory_->Get();
    }
    return std::allocator<T>::allocate(n, hint);
  }

  void deallocate(pointer p, size_type n) {
    assert(n == 1);
    if (reserved_memory_->InRange(p)) {
      reserved_memory_->Put(p);
    } else {
      std::allocator<T>::deallocate(p, n);
    }
  }

 private:
  ReservedMemory* reserved_memory_ = nullptr;
};

template <typename T, size_t Capacity>
inline bool operator==(const StackAllocator<T, Capacity>& lhs,
                       const StackAllocator<T, Capacity>& rhs) {
  return false;
}
