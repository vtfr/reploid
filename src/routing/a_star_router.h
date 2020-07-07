#pragma once

#include <functional>  // std::function
#include <memory>      // std::unique_ptr, std::move

#include "routing/map.h"     // Map
#include "routing/route.h"   // Route
#include "routing/router.h"  // Router
#include "sys/logger.h"      // Logger

namespace routing {

class AStarRouter : public Router {
 public:
  typedef std::function<double(Map::Location, Map::Location)> Heuristic;

  AStarRouter(const Heuristic heuristic, sys::Logger& logger)
      : heuristic(heuristic), logger{logger} {}

  virtual std::unique_ptr<Route> route(const Map& map,
                                       const Map::Location& start,
                                       const Map::Location& goal) override;

 private:
  const Heuristic heuristic;
  sys::Logger& logger;
};

}  // namespace routing
