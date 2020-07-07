#pragma once

#include <memory>  // std::unique_ptr

#include "routing/map.h"    // Map
#include "routing/route.h"  // Route

namespace routing {

class Router {
 public:
  virtual std::unique_ptr<Route> route(const Map& map,
                                       const Map::Location& inicio,
                                       const Map::Location& final) = 0;
};

}  // namespace routing