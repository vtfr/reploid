
#include "routing/map.h"  // Map

#include <cstdint>  // uint32_t
#include <memory>   // std::move

namespace routing {

std::vector<Map::Location> Map::getNeighbours(
    const Map::Location& location) const {
  std::vector<Map::Location> neighbours;
  neighbours.reserve(8);

#define ADD_SHIFT_IF_INBOUND_AND_EMPTY(shift)                     \
  if (isInbound(location + shift) && isEmpty(location + shift)) { \
    neighbours.push_back(location + shift);                       \
  }

  ADD_SHIFT_IF_INBOUND_AND_EMPTY(Map::Location(1, 0));
  ADD_SHIFT_IF_INBOUND_AND_EMPTY(Map::Location(1, -1));
  ADD_SHIFT_IF_INBOUND_AND_EMPTY(Map::Location(0, -1));
  ADD_SHIFT_IF_INBOUND_AND_EMPTY(Map::Location(-1, -1));
  ADD_SHIFT_IF_INBOUND_AND_EMPTY(Map::Location(-1, 0));
  ADD_SHIFT_IF_INBOUND_AND_EMPTY(Map::Location(-1, 1));
  ADD_SHIFT_IF_INBOUND_AND_EMPTY(Map::Location(0, 1));
  ADD_SHIFT_IF_INBOUND_AND_EMPTY(Map::Location(1, 1));

#undef ADD_SHIFT_IF_INBOUND_AND_EMPTY

  return neighbours;
}

};  // namespace routing
