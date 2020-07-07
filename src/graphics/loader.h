#pragma once

#include <memory>  // std::unique_ptr

#include "graphics/image.h"

namespace graphics {

std::unique_ptr<Image> loadImage(const char *filename);

void writeImage(const char *filename, const Image &image);

}  // namespace graphics