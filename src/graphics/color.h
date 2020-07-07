#pragma once

namespace graphics {

struct Color {
  typedef unsigned char Component;

  Component r, g, b;

  inline void operator=(const Color &other) {
    r = other.r;
    g = other.g;
    b = other.b;
  }

  inline bool operator==(const Color &other) const {
    return r == other.r && g == other.g && b == other.b;
  }

  inline bool operator!=(const Color &other) const { return !(*this == other); }

  inline bool operator>(const Color &other) const {
    return r > other.r && g > other.g && b > other.b;
  }

  inline bool operator<(const Color &other) const {
    return r < other.r && g < other.g && b < other.b;
  }

  static constexpr Color BLACK() { return {0, 0, 0}; }
  static constexpr Color GRAY() { return {128, 128, 128}; }
  static constexpr Color WHITE() { return {255, 255, 255}; }
  static constexpr Color RED() { return {255, 0, 0}; }
  static constexpr Color GREEN() { return {0, 255, 0}; }
  static constexpr Color BLUE() { return {0, 0, 255}; }
};

}  // end namespace graphics
