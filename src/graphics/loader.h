#pragma once

#include "graphics/image.h"
#include <memory> // std::unique_ptr

namespace graphics {

std::unique_ptr<Image> LoadImage(const char *filename);

void WriteImage(const char *filename, const Image &image);

} // namespace graphics