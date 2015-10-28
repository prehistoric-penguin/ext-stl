#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "fixed_string.hpp"
#include "gtest/gtest.h"

TEST(FixedString, general) {
  const int kMax = 128;
  FixedString<kMax> fs = "123";
  EXPECT_TRUE(fs.capacity() == kMax);

  EXPECT_TRUE(fs == "123");
  EXPECT_TRUE(fs[0] == '1');
  EXPECT_TRUE(fs.front() == '1');
  EXPECT_TRUE(fs.back() == '3');
  EXPECT_TRUE(fs.size() == 3);

  fs += "4";
  EXPECT_TRUE(fs.size() == 4);
  EXPECT_TRUE(fs.capacity() == kMax);

  FixedString<kMax>::iterator it = fs.begin();
  EXPECT_TRUE(*it == '1');
}
