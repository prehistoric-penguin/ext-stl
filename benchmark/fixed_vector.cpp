#include "fixed_vector.hpp"

#include <vector>
#include <iostream>
#include <algorithm>
#include "stop_watch.hpp"

constexpr int kRunLoops = 1000000;
constexpr int kVecSize = 100;

template <typename T>
void do_not_optmise(T&& val) {
  asm volatile ("" : "+r" (val));
}

struct PrintLine { ~PrintLine() { std::cout << std::endl; } };

template <typename Container>
void ctor_dtor() {
  for (int i = 0; i < kRunLoops; ++i) {
    Container con(kVecSize);
    do_not_optmise(con.begin());
  }
}

void bench_ctor_dtor() {
  PrintLine printline;
  std::cout << "constructing and destructing" << std::endl;
  std::cout << "std::vector cost:" << std::endl;

  StopWatch sw;
  ctor_dtor<std::vector<int>>();
  sw.Stop();
  std::cout << sw << std::endl;

  std::cout << "fixed vector cost:" << std::endl;
  sw.Restart();
  ctor_dtor<FixedVector<int, kVecSize>>();
  sw.Stop();
  std::cout << sw << std::endl;
}

template <typename Container>
void iota() {
  for (int i = 0; i < kRunLoops; ++i) {
    Container con;
    con.resize(kVecSize);
    std::iota(std::begin(con), std::end(con), 0);
    do_not_optmise(con.size());
  }
}

void bench_iota() {
  PrintLine pline;
  std::cout << "iota fill for 100 elements" << std::endl;
  std::cout << "std::vector cost:" << std::endl;

  StopWatch sw;
  iota<std::vector<int>>();
  sw.Stop();
  std::cout << sw << std::endl;

  std::cout << "fixed vector cost:" << std::endl;
  sw.Restart();
  iota<FixedVector<int, kVecSize>>();
  sw.Stop();
  std::cout << sw << std::endl;
}

template <typename Container>
void sum_up() {
  for (int i = 0; i < kRunLoops; ++i) {
    Container con;
    con.resize(kVecSize);
    std::fill(std::begin(con), std::end(con), 0xff);
    auto sum = std::accumulate(std::begin(con), std::end(con), 0);
    do_not_optmise(sum);
  }
}

void bench_sum() {
  PrintLine pline;
  std::cout << "sum up for 100 elements" << std::endl;
  std::cout << "std::vector cost:" << std::endl;

  StopWatch sw;
  sum_up<std::vector<int>>();
  sw.Stop();
  std::cout << sw << std::endl;

  std::cout << "fixed vector cost:" << std::endl;
  sw.Restart();
  sum_up<FixedVector<int, kVecSize>>();
  sw.Stop();
  std::cout << sw << std::endl;
}

template <typename Container>
void push_elements() {
  for (int i = 0; i < kRunLoops; ++i) {
    Container con;
    for (int j = 0; j < kVecSize; ++j) {
      con.push_back(j);
    }
    do_not_optmise(con.front());
  }
}

void bench_push() {
  PrintLine pline;
  std::cout << "push for 100 elements once each" << std::endl;
  std::cout << "std::vector cost:" << std::endl;

  StopWatch sw;
  push_elements<std::vector<int>>();
  sw.Stop();
  std::cout << sw << std::endl;

  std::cout << "fixed vector cost:" << std::endl;
  sw.Restart();
  push_elements<FixedVector<int, kVecSize>>();
  sw.Stop();
  std::cout << sw << std::endl;
}



int main() {
  std::cout << "total loops:" << kRunLoops << std::endl;
  bench_ctor_dtor();
  bench_iota();
  bench_sum();
  bench_push();

  return 0;
}
