#pragma once

#include <cstdint>  // uint32
#include <utility>  // std::move
#include <vector>   // std::vector

#include "data/grid.h"       // data::Grid
#include "graphics/color.h"  // Color
#include "math/point.h"      // Point

namespace graphics {

typedef data::Grid<Color> Image;

}  // end namespace graphics