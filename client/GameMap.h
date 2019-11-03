#ifndef MICROMACHINES_GAMEMAP_H
#define MICROMACHINES_GAMEMAP_H

#include <vector>
#include "tiles/Tile.h"
#include "yaml-cpp/yaml.h"
#include "tiles/TilesFactory.h"

class GameMap {
  std::vector<std::vector<std::shared_ptr<Tile>>> map;
  TilesFactory tiles_factory;

public:
    int width;
    int height;
    
    void loadMap(const std::string &map, SDL_Renderer *gRenderer);

    void render(SDL_Rect &camera, SDL_Renderer *renderer);
};


#endif //MICROMACHINES_GAMEMAP_H
