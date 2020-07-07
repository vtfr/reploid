#pragma once

#include "graphics/color.h" // Color
#include "math/point.h"     // Point
#include <cstdint>          // uint32
#include <utility>          // std::move
#include <vector>           // std::vector

namespace graphics {

class Image {
public:
  typedef math::Point Position;
  typedef math::Point Dimensions;

  Image(uint32_t width, uint32_t height);
  Image(uint32_t width, uint32_t height, std::vector<Color> &&pixels)
      : width_{width}, height_{height}, pixels_(std::move(pixels)) {}

  inline int GetWidth() const { return width_; }
  inline int GetHeight() const { return height_; }

  Color GetColorAt(Position position) const;

  void SetColorAt(Position position, Color color);

private:
  const uint32_t width_;
  const uint32_t height_;
  std::vector<Color> pixels_;
};

} // end namespace graphics