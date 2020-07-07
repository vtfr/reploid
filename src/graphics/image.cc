#include "graphics/image.h" // Image
#include <cassert>          // assert

namespace graphics {

#define INDEX(x, y, w) (y * w + x)

Image::Image(uint32_t width, uint32_t height) : width_{width}, height_{height} {
  pixels_.reserve(width * height);
}

Color Image::GetColorAt(Position position) const {
  return pixels_[INDEX(position.x, position.y, width_)];
}

void Image::SetColorAt(Position position, Color color) {
  pixels_[INDEX(position.x, position.y, width_)] = color;
}

} // end namespace graphics
