#pragma once

#include <cstdint>  // uint32_t
#include <memory>   // std::move
#include <vector>   // std::vector

#include "data/grid.h"   // Grid
#include "math/point.h"  // Point

namespace routing {

class Map {
 public:
  enum class Occupancy { OCCUPIED, EMPTY };

  typedef data::Grid<Occupancy>::Position Location;
  typedef data::Grid<Occupancy>::Dimensions Dimensions;

  Map(data::Grid<Occupancy> &&grid) : grid(std::move(grid)) {}
  Map(unsigned int width, unsigned int height) : grid(width, height) {}

  Dimensions getDimensions() const { return grid.getDimensions(); }

  std::vector<Location> getNeighbours(const Location &location) const;

  bool isInbound(const Location &p) const { return grid.isInbound(p); }

  bool isEmpty(const Location &p) const {
    return grid.get(p) == Occupancy::EMPTY;
  }

  bool isOccupied(const Location &p) const {
    return grid.get(p) == Occupancy::OCCUPIED;
  }

  void occupy(const Location &p) { grid.set(p, Occupancy::OCCUPIED); }
  void empty(const Location &p) { grid.set(p, Occupancy::EMPTY); }

 protected:
  data::Grid<Occupancy> grid;
};

}  // end namespace routing