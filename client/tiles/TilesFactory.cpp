#include <iostream>

#include "TilesFactory.h"
#include "../../config/tileConstants.h"

TilesFactory::TilesFactory() {
    this->ib = InfoBlock("config/tilesInfo.yaml", true);
}

std::shared_ptr<Tile> TilesFactory::getTile(int tyleType, int x, int y, SDL_Renderer *gRenderer){
  std::string key;
    switch (tyleType){
        case GRASS_TILE:
            key = "grass_tile";
            break;
        case STRAIGHT_ROAD_TILE:
            key = "straight_road_tile";
            break;
        case CURVE_ROAD_LEFT_TILE:
            key = "road_lower_turn_no_side";
            break;
        case CURVE_ROAD_LEFT_SIDE_TILE:
            key = "road_lower_turn_side";
            break;
        case STRAIGHT_ROAD_MUD_TILE:
            key = "left_road_tile";
            break;
        case CURVE_ROAD_LEFT_MUD_TILE:
            key = "left_road_mud_tile";
            break;
        case CURVE_ROAD_RIGHT_MUD_TILE:
            key = "right_road_mud_tile";
            break;
        default:
            key = "grass_tile";
            break;
    }
    std::string path = this->ib.getString(key);
    int width = this->ib.getInt(key + "_w");
    int height = this->ib.getInt(key + "_h");
    std::shared_ptr<Tile> t(new Tile(x, y, tyleType, tLoader.load_texture(path, gRenderer), width, height));
    return t;
}


TilesFactory::~TilesFactory() {}