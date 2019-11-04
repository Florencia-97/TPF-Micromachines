#include "GameMap.h"
#include "tiles/TilesFactory.h"
#include "../common/MapsLayer.h"

void GameMap::loadMap(const std::string &mapPath, SDL_Renderer *gRenderer) {

    MapsLayer mapsLayer(mapPath);
    // You can acces to each layer as the attr is public.
    // Now it has height and width

    YAML::Node config = YAML::LoadFile(mapPath);
    YAML::Node mapYaml = config["Road"];
    int y = 0;
    int x = 0;
    int rowTile = -1;
    int num = 1;
    // TODO: load real h and m with mapsLayer
    height = 0;
    width = 0;

    for (YAML::iterator it = mapYaml.begin(); it != mapYaml.end(); ++it) {
        rowTile += 1;
        x = 0;

        int columnTile = 0;
        const YAML::Node &row = *it;
        std::string numberRow = std::to_string(num);
        this->map.emplace_back();
        YAML::Node column = row[numberRow];
        int colNum = 0;
        width +=512;

    for (YAML::iterator c = column.begin(); c != column.end(); ++c) {
        y = rowTile * 512;
        x = columnTile * 512;
        const YAML::Node &col_value = *c;
        auto tile = tiles_factory.getTile(col_value.as<int>(), x, y, gRenderer);
        this->map.back().push_back(tile);

        colNum++;
        columnTile += 1;
        height += 512;
    }

    num++;
  }
}

void GameMap::render(SDL_Rect &camera, SDL_Renderer *renderer){
    for (const auto& row: map){
        for (const auto& tile: row){
          tile->render(camera, renderer);
        }
    }
}