#include "routing/a_star_router.h"

#include <algorithm>      // std::reverse, std::find
#include <iostream>       //std::cout, std::endl
#include <set>            // std::set
#include <stdexcept>      //std::runtime_exception
#include <unordered_map>  // std::unordered_map
#include <utility>        //std::pair

namespace routing {

struct Node {
  Map::Location location;
  double cost;

  Node(Map::Location location, const double cost)
      : location{location}, cost{cost} {}

  bool operator<(const Node& node) const { return cost < node.cost; }
  bool operator==(const Node& node) const { return location == node.location; }
  bool operator==(const Map::Location& location_) const {
    return location == location_;
  }
};

std::vector<Map::Location> reconstruct(
    const std::unordered_map<Map::Location, std::pair<Map::Location, double>>&
        cameFrom,
    Map::Location current) {
  std::vector<Map::Location> path;
  path.push_back(current);

  while (true) {
    auto it = cameFrom.find(current);
    if (it == cameFrom.end()) {
      std::reverse(std::begin(path), std::end(path));
      return path;
    }

    current = it->second.first;
    path.push_back(current);
  }
}

std::unique_ptr<Route> AStarRouter::route(const Map& map,
                                          const Map::Location& start,
                                          const Map::Location& goal) {
  std::vector<Node> queue;
  std::vector<Map::Location> closed;
  std::unordered_map<Map::Location, std::pair<Map::Location, double>> cameFrom;

  queue.push_back(Node{start, 0});

  while (!queue.empty()) {
    const auto current = *std::min_element(std::begin(queue), std::end(queue));
    if (current.location == goal) {
      return std::make_unique<Route>(reconstruct(cameFrom, current.location));
    }

    std::cout << "Current: (" << current.location.x << ", "
              << current.location.y << "). Cost: " << current.cost << std::endl;

    std::remove(std::begin(queue), std::end(queue), current);
    closed.push_back(current.location);

    const auto neighbours = map.getNeighbours(current.location);

    for (const auto neighbour : neighbours) {
      const auto cost = current.cost + heuristic(neighbour, goal);

      if (std::find(std::begin(closed), std::end(closed), neighbour) ==
              std::end(closed) &&
          std::find(std::begin(queue), std::end(queue), neighbour) ==
              std::end(queue)) {
        queue.push_back(Node{neighbour, cost});

        auto cameFromNeighbourIt = cameFrom.find(neighbour);
        if (cameFromNeighbourIt == cameFrom.end() ||
            cameFromNeighbourIt->second.second < cost) {
          cameFrom[neighbour] = std::make_pair(current.location, cost);
        }
      }
    }
  }

  throw std::runtime_error("Impossível gerar caminho para essas condições");
}

}  // end namespace routing