#include "math/point.h"

namespace math {}  // namespace math

std::ostream &operator<<(std::ostream &os, const math::Point &point) {
  os << "(" << point.x << ", " << point.y << ")";
  return os;
}
