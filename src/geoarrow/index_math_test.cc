
#include <gtest/gtest.h>

#include "index_math.hpp"

using namespace geoarrow::util::indices;

TEST(IndexMathTest, TestIndeMathFlatten) {
  EXPECT_EQ(Index2(2, 3).CellRowMajor(Shape2(5, 6)), 13);
  EXPECT_EQ(Index2::RowMajor(13, Shape2(5, 6)), Index2(2, 3));
}
