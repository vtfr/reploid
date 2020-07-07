#pragma once

#include <sstream>    // std::stringstream
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string

#include "math/point.h"  // std::Point

namespace data {

class InvalidPositionError : public std::runtime_error {
 public:
  InvalidPositionError() : std::runtime_error("Invalid position"){};

  InvalidPositionError(const math::Point& position)
      : std::runtime_error(createMessage(position)), position{position} {};

  const math::Point position;

 private:
  static std::string createMessage(const math::Point& position) {
    std::stringstream stream;
    stream << "Invalid position " << position;

    return stream.str();
  }
};

}  // namespace data
