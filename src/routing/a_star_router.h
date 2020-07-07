#pragma once

#include <functional>  // std::function
#include <memory>      // std::unique_ptr, std::move

#include "routing/map.h"     // Map
#include "routing/route.h"   // Route
#include "routing/router.h"  // Router

namespace routing {

class AStarRouter : public Router {
 public:
  typedef std::function<double(Map::Location, Map::Location)> Heuristic;

  AStarRouter(const Heuristic heuristic) : heuristic(heuristic) {}

  virtual std::unique_ptr<Route> route(const Map& map,
                                       const Map::Location& start,
                                       const Map::Location& goal) override;

 private:
  const Heuristic heuristic;
};

}  // namespace routing
