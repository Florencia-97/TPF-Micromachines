//
// Created by brian on 10/27/19.
//

#ifndef MICROMACHINES_CLIENT_MAPMANAGER_H_
#define MICROMACHINES_CLIENT_MAPMANAGER_H_
#define TOTAL_TILE_SPRITES 12
#include <SDL_rect.h>
#include "Tile.h"
class MapManager {
 private:
  SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
 public:
  MapManager() = default;
  bool checkCollision(SDL_Rect a, SDL_Rect b);
  bool setTiles(Tile *tiles[], int totalTiles);
  bool touchesWall(SDL_Rect box, Tile *tiles[]);
};
#endif //MICROMACHINES_CLIENT_MAPMANAGER_H_
