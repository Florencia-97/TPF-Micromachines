#include <iostream>

#include "TilesFactory.h"
#include "../../config/tileConstants.h"

TilesFactory::TilesFactory() {
    this->ib = InfoBlock("config/tilesInfo.yaml", true);
}

std::shared_ptr<Tile> TilesFactory::getTile(int tyleType, int x, int y, SDL_Renderer *gRenderer){
  std::string key;
    switch (tyleType){
      case GRASS_TILE: key = "grass_tile";
        break;
      case straight_road_tile: key = "straight_road_tile";
        break;
      case down_left_road_tile: key = "down_left_road_tile";
        break;
      case down_right_road_tile: key = "down_right_road_tile";
        break;
      case straight_vertical_tile: key = "straight_vertical_tile";
        break;
      case up_left_road_tile: key = "up_left_road_tile";
        break;
      case up_right_road_tile: key = "up_right_road_tile";
        break;
      case straight_vertical_aux_tile: key = "straight_vertical_aux_tile";
        break;
      case straight_horizontal_aux_tile: key = "straight_horizontal_aux_tile";
        break;
      case tree_spikes_tile: key = "tree_spikes_tile";
        break;
      case tree_round_tile: key = "tree_round_tile";
        break;
      case pavilion_blue_tile: key = "pavilion_blue_tile";
        break;
      case finish_line: key = "finish_line";
        break;
      case flashy : key = "flashy_tile";
        break;
      default: key = "grass_tile";
        break;
    }
    std::string path = this->ib.getString(key);
    int width = this->ib.getInt(key + "_w");
    int height = this->ib.getInt(key + "_h");
    std::shared_ptr<Tile> t(new Tile(x, y, tyleType, tLoader.load_texture(path, gRenderer), width, height));
    return t;
}


TilesFactory::~TilesFactory() {}