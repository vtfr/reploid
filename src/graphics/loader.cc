#include "graphics/loader.h"

#include "lodepng/lodepng.h"

namespace graphics {

std::unique_ptr<Image> loadImage(const char *filename) {
  unsigned int width;
  unsigned int height;
  std::vector<unsigned char> buffer;

  const auto error = lodepng::decode(buffer, width, height, filename);
  if (error) {
    throw std::runtime_error(
      std::string{"Falha carregando imagem: "} + lodepng_error_text(error));
  }

  auto image = std::make_unique<Image>(width, height);
  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      const auto index = 4 * (y * width + x);
      const auto r = buffer[index + 0];
      const auto g = buffer[index + 1];
      const auto b = buffer[index + 2];

      image->set({x, y}, {r, g, b});
    }
  }

  return image;
}

void writeImage(const char *filename, const Image &image) {
  const auto [width, height] = image.getDimensions();

  std::vector<unsigned char> buffer;
  buffer.resize(width * height * 4);

  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      const auto color = image.get({x, y});
      const auto index = 4 * (y * width + x);

      buffer[index + 0] = color.r;
      buffer[index + 1] = color.g;
      buffer[index + 2] = color.b;
      buffer[index + 3] = 255;
    }
  }

  const auto error = lodepng::encode(filename, buffer, width, height);
  if (error) {
    throw std::runtime_error(
      std::string{"Falha salvando imagem: "} + lodepng_error_text(error));
  }
}

}  // namespace graphics