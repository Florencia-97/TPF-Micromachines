//
// Created by flox on 30/10/19.
//
#include <iostream>

#include "TilesFactory.h"
#include "../../config/tileConstants.h"

TilesFactory::TilesFactory() {
    this->ib = InfoBlock("config/tilesInfo.yaml", true);
}

Tile* TilesFactory::getTile(int tyleType, int x, int y, SDL_Renderer *gRenderer){
    Tile* tile = nullptr;
  std::string path;
    switch (tyleType){
        case GRASS_TILE:
            path = this->ib.getString("grass_tile");
            break;
        case STRAIGHT_ROAD_TILE:
            path = this->ib.getString("straight_road_tile");
            break;
        default:
            // we could make a default tile here, or an error tile if we want to!
            break;
    }
    //Create a smart pointer? Should avoid potencial problems
    tile = new Tile(x, y, tyleType, tLoader.load_texture(path, gRenderer), 512, 512);
    return tile;
}


TilesFactory::~TilesFactory() {}