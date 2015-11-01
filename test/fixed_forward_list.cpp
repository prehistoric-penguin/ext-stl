#include "fixed_forward_list.hpp"

#include <vector>
#include <list>
#include <memory>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "gtest/gtest.h"

static constexpr size_t kMax = 100;
static std::vector<int> vec(kMax);
using ListType = FixedForwardList<int, kMax>;

TEST(FixedForwardList, general) {
  std::generate(std::begin(vec), std::begin(vec), rand);

  ListType flist = {1, 2};
  EXPECT_EQ(flist.front(), 1);

  ListType::iterator it = flist.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*std::next(it), 2);

  flist.clear();
  EXPECT_TRUE(flist.empty());
}

TEST(FixedForwardList, assign) {
  ListType flist;
  flist.assign(std::begin(vec), std::end(vec));

  EXPECT_TRUE(std::equal(std::begin(vec), std::end(vec), std::begin(flist)));
}

TEST(FixedForwardList, iterators) {
  ListType flist;
  EXPECT_TRUE(flist.empty());
  auto itr = flist.before_begin();

  for (int i : vec) flist.insert_after(itr, i);
  EXPECT_TRUE(std::equal(std::begin(flist), std::end(flist), vec.rbegin()));
}

TEST(FixedForwardList, modifiers) {
  ListType flist;
  auto itr = flist.insert_after(flist.before_begin(), 0);
  flist.insert_after(itr, 1);

  EXPECT_TRUE(flist == ListType({0, 1}));
  EXPECT_EQ(flist.front(), 0);

  ListType flist2;
  for (int i : vec) flist2.push_front(i);
  EXPECT_TRUE(std::equal(std::begin(flist2), std::end(flist2), vec.rbegin()));

  auto vec_size = vec.size();
  while (vec_size-- > 0) flist2.pop_front();
  EXPECT_TRUE(flist2.empty());

  flist2.push_front(0);
  EXPECT_EQ(flist2.front(), 0);

  ListType flist3(std::begin(vec), std::end(vec));
  flist.swap(flist3);
  EXPECT_TRUE(std::equal(std::begin(flist), std::end(flist), vec.rbegin()));

  flist.resize(kMax / 2);
  EXPECT_TRUE(std::equal(std::begin(vec), std::next(std::begin(vec), kMax / 2),
                         std::begin(flist)));
}

TEST(FixedForwardList, operations) {
  ListType flist;
  flist.assign(std::begin(vec), std::end(vec));

  flist.remove_if([](int val) { return val % 2 == 0; });
  std::vector<int> vec_tmp;
  std::copy_if(std::begin(vec), std::end(vec), std::back_inserter(vec_tmp),
               [](int val) { return val % 2 != 0; });

  EXPECT_TRUE(
      std::equal(std::begin(vec_tmp), std::end(vec_tmp), std::begin(flist)));

  ListType flist2;
  flist2.assign(std::begin(vec), std::end(vec));
  flist2.reverse();
  EXPECT_TRUE(std::equal(std::begin(flist2), std::end(flist2), vec.rbegin()));

  std::vector<int> vec_tmp2 = vec;
  vec_tmp2.erase(std::unique(std::begin(vec_tmp2), std::end(vec_tmp2)),
                 std::end(vec_tmp2));
  ListType flist3;
  flist3.assign(std::begin(vec), std::end(vec));
  flist3.unique();
  EXPECT_TRUE(
      std::equal(std::begin(flist3), std::end(flist3), std::begin(vec_tmp2)));

  flist3.sort();
  std::sort(std::begin(vec_tmp2), std::end(vec_tmp2));
  EXPECT_TRUE(
      std::equal(std::begin(flist3), std::end(flist3), std::begin(vec_tmp2)));
}

TEST(FixedForwardList, global_operator) {
  ListType flist = {1, 2};
  ListType flist2 = flist;
  ListType flist3 = {3};

  EXPECT_TRUE(flist == flist2);
  EXPECT_TRUE(flist < flist3);
  EXPECT_TRUE(flist != flist3);
}
