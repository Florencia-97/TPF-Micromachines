#include "GameMap.h"
#include "tiles/TilesFactory.h"
#include "../common/MapsLayer.h"

void GameMap::loadMap(const std::string &mapPath, SDL_Renderer *gRenderer) {
    MapsLayer mapsLayer(mapPath);
    _loadLayer(mapsLayer.ground, gRenderer,"ground");
    _loadLayer(mapsLayer.road, gRenderer, "road");
    _loadLayer(mapsLayer.extras, gRenderer, "extras");
    height = mapsLayer.height;
    width = mapsLayer.width;
}

void GameMap::_loadLayer(std::vector<std::vector<int>> layerMatrix, SDL_Renderer *gRenderer, const std::string& mapName){
    int x = 0;
    int y = 0;

    for (std::size_t i = 0; i < layerMatrix.size(); ++i){
        std::vector<int> row = layerMatrix[i];
        if (mapName == "ground") this->ground.emplace_back();
        else if (mapName == "road") this->road.emplace_back();
        else this->extras.emplace_back();
        for (std::size_t j = 0; j < row.size(); ++j){
            x = j * TILE_SIZE;
            y = i * TILE_SIZE;
            int tileType = row[j];
            if (tileType == 0){
                continue;
            }
		  auto tile = tiles_factory.get_tile(tileType, x, y, gRenderer);
            if (mapName == "ground") this->ground.back().push_back(tile);
            else if (mapName == "road") this->road.back().push_back(tile);
            else this->extras.back().push_back(tile);
        }
    }
}

void GameMap::render(SDL_Rect &camera, SDL_Renderer *renderer){
    for (const auto& row: ground){
        for (const auto& tile: row){
		  tile->render(camera, renderer);
        }
    }
    for (const auto& row: road){
        for (const auto& tile: row){
		  tile->render(camera, renderer);
        }
    }
}

void GameMap::renderDeco(SDL_Rect &camera, SDL_Renderer *renderer, int x, int y) {
    for (const auto& row: extras){
        for (const auto& tile: row){
            tile->getBox().x += x;
            tile->getBox().y += y;
		    tile->render(camera, renderer);
            tile->getBox().x -= x;
            tile->getBox().y -= y;
        }
    }
}
void GameMap::clear() {
  this->ground.clear();
  this->extras.clear();
  this->road.clear();
}
