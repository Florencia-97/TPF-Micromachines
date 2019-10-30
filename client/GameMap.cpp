

#include "GameMap.h"
#include "tiles/TilesFactory.h"

void GameMap::loadMap(const std::string &mapPath, SDL_Renderer *gRenderer) {
    YAML::Node config = YAML::LoadFile(mapPath);
    YAML::Node mapYaml = config["Map"];
  TilesFactory tiles_factory;
    int num = 1;
    for (YAML::iterator it = mapYaml.begin(); it != mapYaml.end(); ++it) {
        const YAML::Node& row = *it;
        std::string numberRow = std::to_string(num);
        this->map.emplace_back();
        YAML::Node column = row[numberRow];
        int colNum = 0;
        for (YAML::iterator c = column.begin(); c != column.end(); ++c) {
            const YAML::Node& col_value = *c;
          auto tile = tiles_factory.getTile(col_value.as<int>(), 0, 0, gRenderer);
          this->map.back().emplace_back(tile);
            colNum++;
        }
        num ++;
    }
}

void GameMap::dummyInit(int x, int y, LTexture* texture) {
    for (int i=0; i<y; i++){
        map.emplace_back();
        for (int j= 0; j<x; j++){
            map[i].emplace_back(j*TILE_WIDTH, i*TILE_HEIGHT,1, texture, 512, 512);
        }
    }
}

void GameMap::render(SDL_Rect &camera, SDL_Renderer *renderer){
    for (const auto& row: map){
        for (auto tile: row){
            tile.render(camera, renderer);
        }
    }
}
