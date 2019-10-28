//
// Created by brian on 10/28/19.
//
#include "Tile.h"
Tile::Tile(int x, int y, int tileType) {
  //Get the offsets
  mBox.x = x;
  mBox.y = y;
  //Set the collision box
  mBox.w = 80;
  mBox.h = 80;
  //Get the tile type
  mType = tileType;
}
void Tile::render(SDL_Rect &camera, MapManager manager, LTexture *tileTexture) {
  //If the tile is on screen
  if (MapManager::checkCollision(camera, mBox)) { // ver como agregar esta funcion!!!
    //Show the tile
    SDL_Rect *gTileClips = manager.get_tiles_clip();
    tileTexture->render(mBox.x - camera.x, mBox.y - camera.y, &gTileClips[mType]);
  }
}

int Tile::getType() {
  return mType;
}

SDL_Rect Tile::getBox() {
  return mBox;
}

