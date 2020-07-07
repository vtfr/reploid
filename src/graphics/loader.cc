#include "graphics/loader.h"

#include "lodepng/lodepng.h"

namespace graphics {

std::unique_ptr<Image> LoadImage(const char *filename) {
  unsigned width;
  unsigned height;
  std::vector<unsigned char> buffer;

  const auto error = lodepng::decode(buffer, width, height, filename);
  if (error) {
    //
  }

  auto image = std::make_unique<Image>(width, height);
  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      const auto index = 4 * (y * width + x);
      const auto r = buffer[index + 0];
      const auto g = buffer[index + 1];
      const auto b = buffer[index + 2];

      image->SetColorAt({x, y}, {r, g, b});
    }
  }

  return image;
}

void WriteImage(const char *filename, const Image &image) {
  const auto width = image.GetWidth();
  const auto height = image.GetHeight();

  std::vector<unsigned char> buffer;
  buffer.resize(width * height * 4);

  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      const auto color = image.GetColorAt({x, y});
      const auto index = 4 * (y * width + x);

      buffer[index + 0] = color.r;
      buffer[index + 1] = color.g;
      buffer[index + 2] = color.b;
      buffer[index + 3] = 255;
    }
  }

  const auto error = lodepng::encode(filename, buffer, width, height);
  // todo
}

} // namespace graphics