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
void Tile::render(SDL_Rect &camera, SDL_Rect *gTileClips, LTexture *tileTexture, SDL_Renderer *renderer) {
  //If the tile is on screen
  if (checkCollision(camera, mBox)) {
    tileTexture->render(mBox.x - camera.x,
                        mBox.y - camera.y,
                        &gTileClips[mType],
                        0.0,
                        nullptr,
                        SDL_FLIP_NONE,
                        renderer);
  }
}

int Tile::getType() {
  return mType;
}

SDL_Rect Tile::getBox() {
  return mBox;
}
bool Tile::checkCollision(SDL_Rect a, SDL_Rect b) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB) {
      return false;
    }

    if (topA >= bottomB) {
      return false;
    }

    if (rightA <= leftB) {
      return false;
    }
    return leftA < rightB;
}

