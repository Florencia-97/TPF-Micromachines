//
// Created by brian on 10/28/19.
//

#ifndef MICROMACHINES_CLIENT_TILE_H_
#define MICROMACHINES_CLIENT_TILE_H_

#include <SDL_rect.h>
#include "rendering/LTexture.h"

class Tile{

 private:

  //The attributes of the tile
  SDL_Rect mBox;

  //The tile type
  int mType;

  LTexture* texture;

 public:

  //Initializes position and type
  Tile(int x, int y, int tileType, LTexture* texture);

  //Shows the tile
  void render(SDL_Rect &camera, SDL_Renderer *renderer);

  //Get the tile type
  int getType();

  //Get the collision box
  SDL_Rect getBox();

  static bool checkCollision(SDL_Rect a, SDL_Rect b);
};

#endif //MICROMACHINES_CLIENT_TILE_H_
