#include "fixed_vector.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "gtest/gtest.h"

TEST(FixedVector, general) {
  const int kSize = 100;
  const int kMax = 1008;
  FixedVector<size_t, kMax> fv0;

  std::vector<size_t> vec(kSize);
  std::iota(std::begin(vec), std::end(vec), 0ul);
  FixedVector<size_t, kMax> fv(std::begin(vec), std::end(vec));
  for (size_t i = 0; i < kSize; ++i) {
    EXPECT_TRUE(fv[i] == i);
  }
  fv.push_back(1);
  EXPECT_TRUE(fv.back() == 1);

  FixedVector<size_t, kMax> fv_shd(fv);

  EXPECT_TRUE(std::equal(std::begin(fv), std::end(fv), std::begin(fv_shd)));
}
