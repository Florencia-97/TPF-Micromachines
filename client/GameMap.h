

#ifndef MICROMACHINES_GAMEMAP_H
#define MICROMACHINES_GAMEMAP_H

#include <vector>
#include "Tile.h"
#include "yaml-cpp/yaml.h"

#define TILE_WIDTH  512
#define TILE_HEIGHT  512

class GameMap {
    std::vector<std::vector<Tile>> map;

public:
    GameMap() = default;

    void dummyInit(int xSize, int ySize, LTexture* texture);//todo remove

    void loadMap(std::string map);

    void render(SDL_Rect &camera, SDL_Renderer *renderer);
};


#endif //MICROMACHINES_GAMEMAP_H
