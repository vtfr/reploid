#pragma once

#include <memory>  // std::move
#include <vector>  // std::vector

#include "math/point.h"
#include "routing/route.h"

namespace routing {

struct Route {
 public:
  const std::vector<math::Point> points;

  Route(std::vector<math::Point>&& points) : points(std::move(points)) {}
};

}  // namespace routing