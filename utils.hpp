#pragma once
#include <memory>

// maximum fixed container memory usage
// default value is one memory page
// when comes to fixedswap, another
// one page memory will be used
constexpr size_t kMaxStackUsage = 4 * 1024;
template <typename T>
void FixedSwap(T& a, T& b) {
  if (sizeof(a) < kMaxStackUsage) {
    T tmp(a);
    a = b;
    b = tmp;
  } else {
    std::unique_ptr<T> uptr(new T(a));
    a = b;
    b = *uptr;
  }
}
