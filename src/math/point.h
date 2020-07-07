#pragma once

#include <functional>  // std::hash
#include <ostream>     // std::ostream

namespace math {

struct Point {
  typedef int Component;

  Component x;
  Component y;

  Point() : Point{0, 0} {}
  Point(const Point &other) : Point(other.x, other.y) {}
  Point(Component x, Component y) : x{x}, y{y} {}

  void operator=(const Point &other) {
    x = other.x;
    y = other.y;
  }

  Point operator+(const Point &other) const {
    return Point{x + other.x, y + other.y};
  }
  Point operator-(const Point &other) const {
    return Point{x - other.x, y - other.y};
  }

  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Point &other) const { return !(*this == other); }
};

}  // namespace math

std::ostream &operator<<(std::ostream &os, const math::Point &point);

namespace std {
template <>
struct hash<math::Point> {
  size_t operator()(const math::Point &point) const {
    std::size_t h1 = std::hash<int>{}(point.x);
    std::size_t h2 = std::hash<int>{}(point.y);
    return h1 ^ (h2 << 1);
  }
};
}  // namespace std