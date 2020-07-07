#pragma once

#include <memory>     //std::move
#include <stdexcept>  // std::runtime_error
#include <utility>    // std::pair, std::make_pair
#include <vector>     //std::vector

#include "math/point.h"  // Point

namespace data {

class InvalidPositionException : public std::runtime_error {
 public:
  InvalidPositionException() : std::runtime_error("Invalid position"){};
};

template <class T>
class Grid {
 public:
  typedef math::Point Position;
  typedef std::pair<unsigned int, unsigned int> Dimensions;

  Grid(const unsigned int width, const unsigned int height)
      : width{width}, height{height} {
    elements.resize(width * height);
  }

  Grid(const unsigned int width, const unsigned int height,
       std::vector<T>&& elements)
      : width{width}, height{height}, elements(std::move(elements)) {
    elements.resize(width * height);
  };

  Dimensions getDimensions() const { return std::make_pair(width, height); }

  unsigned int getWidth() const { return width; }
  unsigned int getHeight() const { return height; }

  bool isInbound(const Position& position) const {
    return position.x > 0 && position.y > 0 && position.x < width &&
           position.y < height;
  }

  T get(const Position& position) const {
    assertInbound(position);

    return elements[position.y * width + position.x];
  }

  void set(const Position& position, const T& element) {
    assertInbound(position);

    elements[position.y * width + position.x] = element;
  }

 private:
  void assertInbound(const Position& position) const {
    if (position.x >= width || position.y >= height) {
      throw InvalidPositionException();
    }
  }

  std::vector<T> elements;
  const unsigned int width;
  const unsigned int height;
};

}  // namespace data
