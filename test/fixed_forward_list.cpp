#include <vector>
#include <list>
#include <memory>
#include <iostream>
#include <algorithm>
#include "fixed_forward_list.hpp"
#include "gtest/gtest.h"

TEST(FixedList, general) {
  const int kMax = 100;
  std::vector<int> vec(kMax);

  using ListType = FixedForwardList<int, kMax>;
  ListType flist = {1, 2};

  EXPECT_EQ(flist.front(), 1);

  ListType::iterator it = flist.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*std::next(it), 2);
}
