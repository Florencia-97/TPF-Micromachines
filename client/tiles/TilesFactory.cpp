#include <iostream>

#include "TilesFactory.h"
#include "../../config/tileConstants.h"

TilesFactory::TilesFactory() {
    this->ib = InfoBlock("config/tilesInfo.yaml", true);
}

std::shared_ptr<Tile> TilesFactory::getTile(int tyleType, int x, int y, SDL_Renderer *gRenderer){
    std::string path;
    int width = 512;
    int height = 512;
    switch (tyleType){
        case GRASS_TILE:
            path = this->ib.getString("grass_tile");
            break;
        case STRAIGHT_ROAD_TILE:
            path = this->ib.getString("straight_road_tile");
            width = 512;
            height = 688;
            break;
        case CURVE_ROAD_LEFT_TILE:
            path = this->ib.getString("left_road_tile");
            width = 691;
            height = 691;
            break;
        case CURVE_ROAD_RIGHT_TILE:
            path = this->ib.getString("right_road_tile");
            break;
        case STRAIGHT_ROAD_MUD_TILE:
            path = this->ib.getString("straight_road_mud_tile");
            break;
        case CURVE_ROAD_LEFT_MUD_TILE:
            path = this->ib.getString("left_road_mud_tile");
            break;
        case CURVE_ROAD_RIGHT_MUD_TILE:
            path = this->ib.getString("right_road_mud_tile");
            break;
        default:
            // we could make a default tile here, or an error tile if we want to!
            break;
    }
    std::shared_ptr<Tile> t(new Tile(x, y, tyleType, tLoader.load_texture(path, gRenderer), width, height));
    return t;
}


TilesFactory::~TilesFactory() {}