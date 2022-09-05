
#include <iostream>

#include "common.hpp"

namespace geoarrow {

namespace util {

namespace indices {

class Box2 {
 public:
  double mins[2];
  double maxes[2];
};

class Shape2 {
 public:
  Shape2(int64_t size0, int64_t size1) : sizes_{size0, size1} {}
  int64_t size(int dim) const { return sizes_[dim]; }

 private:
  int64_t sizes_[2];
};

// These make googletest magic work with these classes
inline bool operator==(const Shape2& x, const Shape2& y) {
  return x.size(0) == y.size(0) && x.size(1) == y.size(1);
}

std::ostream& operator<<(std::ostream& os, const Shape2& x) {
  os << "Shape2(" << x.size(0) << ", " << x.size(1) << ")";
  return os;
}

class Index2 {
 public:
  Index2(int64_t i0, int64_t i1) : i_{i0, i1} {}

  int64_t i(int dim) const { return i_[dim]; }

  // This math isn't quite right, just adding for demo purposes
  int64_t CellRowMajor(const Shape2& shape) const {
    return i_[0] * shape.size(0) + i_[1];
  }

  static Index2 RowMajor(int64_t cell, const Shape2& shape) {
    return Index2(cell / shape.size(0), cell / shape.size(1));
  }

 private:
  int64_t i_[2];
};

// These make googletest magic work with these classes
inline bool operator==(const Index2& x, const Index2& y) {
  return x.i(0) == y.i(0) && x.i(1) == y.i(1);
}

std::ostream& operator<<(std::ostream& os, const Index2& x) {
  os << "Index2(" << x.i(0) << ", " << x.i(1) << ")";
  return os;
}

class Grid2 {
 public:
  Grid2(Shape2 shape, Box2 box) : shape_(shape), box_(box) {}

 private:
  Shape2 shape_;
  Box2 box_;
};

}  // namespace indices

}  // namespace util

}  // namespace geoarrow
