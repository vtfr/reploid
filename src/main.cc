#include <iostream>
#include <memory>     // std::unique_ptr, std::make_unique
#include <stdexcept>  // std::exception

#include "graphics/image.h"         // Image
#include "graphics/loader.h"        // LoadImage
#include "math/distance.h"          // math::distance
#include "routing/a_star_router.h"  // AStarRouter
#include "routing/map.h"            // Map

using namespace routing;
using namespace graphics;

std::unique_ptr<Map> ConverterParaMapa(const Image &imagem,
                                       Map::Location &start,
                                       Map::Location &end) {
  const auto width = imagem.GetWidth();
  const auto height = imagem.GetHeight();

  auto map = std::make_unique<Map>(width, height);

  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      const auto color = imagem.GetColorAt({x, y});

      if (color == Color::RED()) {
        start = Map::Location(x, y);
        map->empty({x, y});
      } else if (color == Color::GREEN()) {
        end = Map::Location(x, y);
        map->empty({x, y});
      } else if (color > Color::GRAY()) {
        map->empty({x, y});
      } else {
        map->occupy({x, y});
      }
    }
  }

  return map;
}

std::unique_ptr<Image> ConverterParaImagem(const Map &map, const Route &route) {
  auto [width, height] = map.getDimensions();

  auto image = std::make_unique<Image>(width, height);

  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      if (map.isOccupied({x, y})) {
        image->SetColorAt({x, y}, Color::BLACK());
      } else {
        image->SetColorAt({x, y}, Color::WHITE());
      }
    }
  }

  for (auto &point : route.points) {
    image->SetColorAt({point.x, point.y}, Color::RED());
  }

  return image;
}

int main(int argc, char **argv) {
  try {
    Map::Location start {-1, -1};
    Map::Location end {-1, -1};

    const auto imagem = LoadImage("./entrada.png");
    const auto mapa = ConverterParaMapa(*imagem, start, end);

    std::cout << "start: (" << start.x << ", " << start.y << ")" << std::endl
              << "end: (" << end.x << ", " << end.y << ")" << std::endl;

    AStarRouter router(math::distance);
    const auto route = router.route(*mapa, start, end);

    for (auto &point : route->points) {
      std::cout << point.x << ", " << point.y << std::endl;
    }

    graphics::WriteImage("./saida.png", *ConverterParaImagem(*mapa, *route));
    std::cout << "Sucesso!\n";
  } catch (std::exception &e) {
    std::cerr << "Erro: " << e.what() << std::endl;
  }
}