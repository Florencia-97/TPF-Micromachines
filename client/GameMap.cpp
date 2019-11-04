#include "GameMap.h"
#include "tiles/TilesFactory.h"
#include "../common/MapsLayer.h"

void GameMap::loadMap(const std::string &mapPath, SDL_Renderer *gRenderer) {

    MapsLayer mapsLayer(mapPath);
    // You can access each layer as the attr is public.
    // Now it has height and width
//    _loadLayer(mapsLayer.ground, gRenderer);
//    _loadLayer(mapsLayer.road, gRenderer);
//    _loadLayer(mapsLayer.extras, gRenderer);

    YAML::Node config = YAML::LoadFile(mapPath);
    YAML::Node mapYaml = config["Road"];
    int y = 0;
    int x = 0;
    int rowTile = -1;
    int num = 1;
    // TODO: load real h and m with mapsLayer
//    height = mapsLayer.height;
//    width = mapsLayer.width;
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

void GameMap::_loadLayer(std::vector<std::vector<int>> layerMatrix, SDL_Renderer *gRenderer){
    // TODO: Discuss if this is for the best
    int x = 0;
    int y = 0;
    for (std::size_t i = 0; i < layerMatrix.size(); ++i){
        std::vector<int> row = layerMatrix[i];
        for (std::size_t j = 0; j < row.size(); ++i){
            int tileType = row[j];
            if (tileType == 0){
                x += j * 512; // Maybe we need a check here, whether we are over height or width
                y += i * 512; // Same
                continue;
            }
            auto tile = tiles_factory.getTile(tileType, x, y, gRenderer);
            this->map.back().push_back(tile); // It goes in different maps
            SDL_Rect mBox = tile->getBox();
            x += j * (int) mBox.w;
            y += i * (int) mBox.y;
        }
    }
}

void GameMap::render(SDL_Rect &camera, SDL_Renderer *renderer){
    for (const auto& row: map){
        for (const auto& tile: row){
          tile->render(camera, renderer);
        }
    }
}