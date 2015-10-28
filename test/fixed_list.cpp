#include <vector>
#include <list>
#include <memory>
#include <iostream>
#include <algorithm>
#include "fixed_list.hpp"
#include "gtest/gtest.h"

TEST(FixedList, general) {
  const int kMax = 100;
  std::vector<int> vec(kMax);
  using ListType = FixedList<int, kMax>;
  FixedList<int, kMax> flist;
  flist.push_back(1);
  flist.push_back(2);

  EXPECT_EQ(flist.front(), 1);
  EXPECT_EQ(flist.size(), 2);

  ListType::iterator it = flist.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*std::next(it), 2);
}
