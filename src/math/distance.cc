
#include "math/distance.h"

#include <cmath>  // std::sqrt, std::pow

namespace math {

double distance(const math::Point& a, const math::Point& b) {
  return std::sqrt(std::pow((double)(a.x - b.x), 2.0) +
                   std::pow((double)(a.y - b.y), 2.0));
}

}  // namespace math