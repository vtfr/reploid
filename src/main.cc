#include <iostream>
#include <memory>     // std::unique_ptr, std::make_unique
#include <stdexcept>  // std::exception

#include "graphics/image.h"         // Image
#include "graphics/loader.h"        // LoadImage
#include "math/distance.h"          // math::distance
#include "routing/a_star_router.h"  // AStarRouter
#include "routing/map.h"            // Map
#include "sys/system_logger.h"      // SystemLogger

using namespace routing;
using namespace graphics;
using namespace sys;

std::unique_ptr<Map> converterParaMapa(const Image &imagem,
                                       Map::Location &start,
                                       Map::Location &end) {
  const auto [width, height] = imagem.getDimensions();

  auto map = std::make_unique<Map>(width, height);

  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      const auto color = imagem.get({x, y});

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

std::unique_ptr<Image> converterParaImagem(const Map &map, const Route &route) {
  auto [width, height] = map.getDimensions();

  auto image = std::make_unique<Image>(width, height);

  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      if (map.isOccupied({x, y})) {
        image->set({x, y}, Color::BLACK());
      } else {
        image->set({x, y}, Color::WHITE());
      }
    }
  }

  for (auto &point : route.points) {
    image->set({point.x, point.y}, Color::RED());
  }

  return image;
}

static const Map::Location EMPTY{-1, -1};

int main(int argc, char **argv) {
  SystemLogger logger;

  try {
    Map::Location start{EMPTY};
    Map::Location end{EMPTY};

    const auto imagem = loadImage("./entrada.png");
    const auto mapa = converterParaMapa(*imagem, start, end);

    if (start == EMPTY) {
      logger.log(
          "Erro: posição inicial desconhecida. Verifique se existe um ponto "
          "com a cor exata #FF0000");
      return -1;
    }

    if (end == EMPTY) {
      logger.log(
          "Erro: posição final desconhecida. Verifique se existe um ponto "
          "com a cor exata #00FF00");
      return -2;
    }

    logger.log([=](auto &s) { s << "Start position: " << start; });
    logger.log([=](auto &s) { s << "Goal position: " << end; });

    AStarRouter router(math::distance, logger);
    const auto route = router.route(*mapa, start, end);

    graphics::writeImage("./saida.png", *converterParaImagem(*mapa, *route));

    logger.log("Operação realizada com sucesso");

  } catch (std::exception &e) {
    logger.log([=](auto& s) { s << "Erro: " << e.what(); });
    return -3;
  }
}