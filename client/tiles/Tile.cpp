//
// Created by brian on 10/28/19.
//
#include "Tile.h"

Tile::Tile(int x, int y, LTexture *my_text, float width, float height) {

  //Get the offsets
  texture = my_text;
  mBox.x = x;
  mBox.y = y;
  //Set the collision box
  mBox.w = width;
  mBox.h = height;
  //Get the tile type

}
void Tile::render(SDL_Rect &camera, SDL_Renderer *renderer) {
  //If the tile is on screen
  texture->render(mBox.x - camera.x, mBox.y - camera.y, nullptr,
				  0.0, nullptr, SDL_FLIP_NONE, renderer);
}

SDL_Rect &Tile::getBox() {
  return mBox;
}