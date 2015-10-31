#include "fixed_forward_list.hpp"

#include <vector>
#include <list>
#include <memory>
#include <iostream>
#include <algorithm>
#include "gtest/gtest.h"

TEST(FixedForwardList, general) {
  const int kMax = 100;
  std::vector<int> vec(kMax);

  using ListType = FixedForwardList<int, kMax>;
  ListType flist = {1, 2};

  EXPECT_EQ(flist.front(), 1);

  ListType::iterator it = flist.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*std::next(it), 2);
}

TEST(FixedForwardList, global_operaotor) {
  const int kMax = 100;
  std::vector<int> vec(kMax);

  using ListType = FixedForwardList<int, kMax>;
  ListType flist = {1, 2};
  ListType flist2 = flist;

  EXPECT_TRUE(flist == flist2);
}
