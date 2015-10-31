#include "fixed_map.hpp"

#include <vector>
#include <memory>
#include <algorithm>

#include "gtest/gtest.h"

static constexpr size_t kMax = 100;
static std::vector<std::pair<size_t, size_t>> vec(kMax);

TEST(FixedSet, ctor_dtor) {
  size_t i = 0;
  std::generate(std::begin(vec), std::end(vec), [&i]() {
    ++i;
    return std::make_pair(i, i);
  });

  FixedMap<size_t, size_t, kMax> fmap(std::begin(vec), std::end(vec));

  FixedMap<size_t, size_t, kMax> fmap1(fmap);
  FixedMap<size_t, size_t, kMax> fmap2({{0ul, 0ul}, {1ul, 1ul}});

  FixedMap<size_t, size_t, kMax, std::greater<size_t>> fmap3(
      std::greater<size_t>());
  FixedMap<size_t, size_t, kMax, std::greater<size_t>> fmap4(std::begin(vec),
                                                             std::end(vec));
}

TEST(FixedSet, assign_operator) {
  {
    FixedMap<size_t, size_t, kMax> fmap;
    fmap = {{0ul, 0ul}, {1ul, 1ul}};
  }
  {
    FixedMap<size_t, size_t, kMax> fmap(std::begin(vec), std::end(vec));
    FixedMap<size_t, size_t, kMax> fmap1;
    fmap1 = fmap;
  }
  {
    FixedMap<size_t, size_t, kMax> fmap;
    fmap = FixedMap<size_t, size_t, kMax>(std::begin(vec), std::end(vec));
  }
  {
    FixedMap<size_t, size_t, kMax> fmap;
    std::map<size_t, size_t> smap(std::begin(vec), std::end(vec));
    fmap = smap;
  }
  {
    FixedMap<size_t, size_t, kMax> fmap;
    fmap = std::map<size_t, size_t>(std::begin(vec), std::end(vec));
  }
}

TEST(FixedSet, begin_end) {
  {
    FixedMap<size_t, size_t, kMax> fmap;
    fmap = {{0ul, 0ul}, {1ul, 1ul}};

    auto it = fmap.begin();
    EXPECT_TRUE(it->first == 0ul && it->second == 0ul);
  }
  {
    FixedMap<size_t, size_t, kMax> fmap;
    fmap = {{0ul, 0ul}, {1ul, 1ul}};

    auto it = fmap.begin();
    auto it_end = fmap.end();

    size_t fssize = fmap.size();
    EXPECT_EQ(fssize, 2);
    EXPECT_EQ(std::distance(it, it_end), fssize);
  }
  {
    FixedMap<size_t, size_t, kMax> fmap(std::begin(vec), std::end(vec));
    auto it = fmap.begin();
    auto it_end = fmap.end();
    EXPECT_TRUE(std::equal(
        it, it_end, std::begin(vec), [](std::pair<const size_t, size_t>& lhs,
                                        std::pair<size_t, size_t>& rhs) {
          return lhs.first == rhs.first && lhs.second == rhs.second;
        }));
  }
}
