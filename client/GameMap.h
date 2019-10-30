

#ifndef MICROMACHINES_GAMEMAP_H
#define MICROMACHINES_GAMEMAP_H

#include <vector>
#include "Tile.h"
#include "yaml-cpp/yaml.h"

#define TILE_WIDTH  512
#define TILE_HEIGHT  512

class GameMap {
    std::vector<std::vector<Tile>> map; //TODO maybe make vector so we can use []

public:
    GameMap() = default;

    void dummyInit(int xSize, int ySize);//todo remove

    void loadMap(std::string map);

    void render();
};


#endif //MICROMACHINES_GAMEMAP_H
