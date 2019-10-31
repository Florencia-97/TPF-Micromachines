#include "GameMap.h"
#include "tiles/TilesFactory.h"

void GameMap::loadMap(const std::string &mapPath, SDL_Renderer *gRenderer) {
  YAML::Node config = YAML::LoadFile(mapPath);
  YAML::Node mapYaml = config["Map"];
  int y = 0;
  int x = 0;
  int rowTile = -1;
  int num = 1;

  for (YAML::iterator it = mapYaml.begin(); it != mapYaml.end(); ++it) {
    rowTile += 1;
    x = 0;

    int columnTile = 0;
    const YAML::Node &row = *it;
    std::string numberRow = std::to_string(num);
    this->map.emplace_back();
    YAML::Node column = row[numberRow];
    int colNum = 0;

    for (YAML::iterator c = column.begin(); c != column.end(); ++c) {
      y = rowTile * 512;
      x = columnTile * 512;
      const YAML::Node &col_value = *c;
      auto tile = tiles_factory.getTile(col_value.as<int>(), x, y, gRenderer);
      this->map.back().push_back(tile);

      colNum++;
      columnTile += 1;
    }

    num++;
  }
}

void GameMap::dummyInit(int x, int y, LTexture* texture) {
  for (int i = 0; i < y; i++) {
    map.emplace_back();
    for (int j = 0; j < x; j++) {
      Tile *tile = new Tile(j * TILE_WIDTH, i * TILE_HEIGHT, 1, texture, 512, 512);
      map.back().push_back(tile);
    }
  }
}

void GameMap::render(SDL_Rect &camera, SDL_Renderer *renderer){
    for (const auto& row: map){
        for (auto tile: row){
          tile->render(camera, renderer);
        }
    }
}

GameMap::~GameMap() {
    for (int row = 0; row < this->map.size(); ++row) {
        for (int col = 0; col < this->map[row].size(); ++col) {
            delete this->map[row][col];
        }
    }
}
