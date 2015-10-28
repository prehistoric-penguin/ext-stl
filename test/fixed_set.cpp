#include <vector>
#include <memory>
#include <algorithm>
#include "fixed_set.hpp"
#include "gtest/gtest.h"

static constexpr size_t kMax = 100;
static std::vector<size_t> vec(kMax);

TEST(FixedSet, ctor_dtor) {
  std::iota(std::begin(vec), std::end(vec), 0ul);

  FixedSet<int, kMax> fset;
  FixedSet<int, kMax> fset1(std::begin(vec), std::end(vec));
  FixedSet<int, kMax> fset2({0, 1, 2});
  FixedSet<int, kMax> fset3(fset1);

  FixedSet<int, kMax, std::greater<int>> fset4(std::greater<int>());
  FixedSet<int, kMax, std::greater<int>> fset5(std::begin(vec), std::end(vec),
                                               std::greater<int>());
}

TEST(FixedSet, assign_operator) {
  {
    FixedSet<int, kMax> fset;
    fset = {1, 2, 3};
  }
  {
    FixedSet<int, kMax> fset(std::begin(vec), std::end(vec));
    FixedSet<int, kMax> fset1;
    fset1 = fset;
  }
  {
    FixedSet<int, kMax> fset;
    fset = FixedSet<int, kMax>(std::begin(vec), std::end(vec));
  }
  {
    FixedSet<int, kMax> fset;
    std::set<int> stdset(std::begin(vec), std::end(vec));
    fset = stdset;
  }
  {
    FixedSet<int, kMax> fset;
    fset = std::set<int>(std::begin(vec), std::end(vec));
  }
}

TEST(FixedSet, begin_end) {
  {
    FixedSet<int, kMax> fset;
    fset = {1, 2, 3};
    auto it = fset.begin();
    EXPECT_EQ(*it, 1);
  }
  {
    FixedSet<int, kMax> fset;
    fset = {1, 2, 3};
    auto it = fset.begin();
    auto it_end = fset.end();
    size_t fssize = fset.size();
    EXPECT_EQ(fssize, 3);
    EXPECT_EQ(std::distance(it, it_end), fssize);
  }
  {
    FixedSet<int, kMax> fset(std::begin(vec), std::end(vec));
    auto it = fset.begin();
    auto it_end = fset.end();
    EXPECT_TRUE(std::equal(it, it_end, std::begin(vec)));
  }
}
