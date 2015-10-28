#pragma once
#include <memory>
#include <type_traits>
#include <cassert>
#include "utils.hpp"

template <typename T, size_t Capacity>
class StackAllocatorVector : public std::allocator<T> {
 public:
  using pointer = typename std::allocator<T>::pointer;
  using size_type = typename std::allocator<T>::size_type;

  struct ReservedMemory {
    using AlignedStorage =
        typename std::aligned_storage<sizeof(T), alignof(T)>::type;
    ReservedMemory() = default;
    T* Data() { return reinterpret_cast<T*>(buffer_); }

    bool in_use_ = false;
    AlignedStorage buffer_[Capacity];
  };

  template <typename U>
  struct rebind {
    using other = StackAllocatorVector<U, Capacity>;
  };

  StackAllocatorVector(const StackAllocatorVector<T, Capacity>& other)
      : std::allocator<T>(), reserved_memory_(other.reserved_memory_) {}

  template <typename U, size_type OtherCapacity>
  StackAllocatorVector(const StackAllocatorVector<U, OtherCapacity>& other)
      : reserved_memory_(nullptr) {}

  StackAllocatorVector(ReservedMemory* reserved) : reserved_memory_(reserved) {}
  StackAllocatorVector() = default;

  pointer allocate(size_type n, void* hint = 0) {
    if (reserved_memory_ != nullptr && !reserved_memory_->in_use_ &&
        n <= Capacity) {
      reserved_memory_->in_use_ = true;
      return reserved_memory_->Data();
    }
    return std::allocator<T>::allocate(n, hint);
  }

  bool use_stack_memory() {
    return reserved_memory_ != nullptr && reserved_memory_->in_use_;
  }

  void deallocate(pointer p, size_type n) {
    if (reserved_memory_ != nullptr && p == reserved_memory_->Data()) {
      reserved_memory_->in_use_ = false;
    } else {
      std::allocator<T>::deallocate(p, n);
    }
  }

 private:
  ReservedMemory* reserved_memory_ = nullptr;
};

template <typename T, size_t Capacity>
inline bool operator==(const StackAllocatorVector<T, Capacity>& lhs,
                       const StackAllocatorVector<T, Capacity>& rhs) {
  return false;
}
