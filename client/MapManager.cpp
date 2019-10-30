//
// Created by brian on 10/27/19.
//

#include <fstream>
#include "MapManager.h"
#define TILE_WIDTH  80
#define TILE_HEIGHT  80
#define LEVEL_WIDTH  1280
#define LEVEL_HEIGHT  960

bool MapManager::checkCollision(SDL_Rect a, SDL_Rect b) {
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

bool MapManager::setTiles(Tile *tiles[], int totalTiles) {
  bool tilesLoaded = true;
  //The tile offsets
  int x = 0, y = 0;
  std::ifstream map("lazy.map");
  if (map.fail()) {
    printf("Unable to load map file!\n");
    tilesLoaded = false;
  } else {
    //Initialize the tiles
    for (int i = 0; i < totalTiles; ++i) {
      //Determines what kind of tile will be made
      int tileType = -1;
      //Read tile from map file
      map >> tileType;
      if (map.fail()) {
        printf("Error loading map: Unexpected end of file!\n");
        tilesLoaded = false;
        break;
      }
      //If the number is a valid tile number
      if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES)) {
        tiles[i] = new Tile(x, y, tileType);
      } else {
        //Stop loading map
        printf("Error loading map: Invalid tile type at %d!\n", i);
        tilesLoaded = false;
        break;
      }
      //Move to next tile spot
      x += TILE_WIDTH;
      //If we've gone too far
      if (x >= LEVEL_WIDTH) {
        x = 0;
        //Move to the next row
        y += TILE_HEIGHT;
      }
      printf("X:%d\n", x);
      printf("Y:%d\n", y);
    }
    //Clip the sprite sheet (Clip de img. Only for example)
    if (tilesLoaded) {
      const int TILE_CENTER = 3;
      const int TILE_TOP = 4;
      const int TILE_TOPRIGHT = 5;
      const int TILE_RIGHT = 6;
      const int TILE_BOTTOMRIGHT = 7;
      const int TILE_BOTTOM = 8;
      const int TILE_BOTTOMLEFT = 9;
      const int TILE_LEFT = 10;
      const int TILE_TOPLEFT = 11;

      gTileClips[0].x = 0;
      gTileClips[0].y = 0;
      gTileClips[0].w = TILE_WIDTH;
      gTileClips[0].h = TILE_HEIGHT;

      gTileClips[1].x = 0;
      gTileClips[1].y = 80;
      gTileClips[1].w = TILE_WIDTH;
      gTileClips[1].h = TILE_HEIGHT;

      gTileClips[2].x = 0;
      gTileClips[2].y = 160;
      gTileClips[2].w = TILE_WIDTH;
      gTileClips[2].h = TILE_HEIGHT;

      gTileClips[TILE_TOPLEFT].x = 80;
      gTileClips[TILE_TOPLEFT].y = 0;
      gTileClips[TILE_TOPLEFT].w = TILE_WIDTH;
      gTileClips[TILE_TOPLEFT].h = TILE_HEIGHT;

      gTileClips[TILE_LEFT].x = 80;
      gTileClips[TILE_LEFT].y = 80;
      gTileClips[TILE_LEFT].w = TILE_WIDTH;
      gTileClips[TILE_LEFT].h = TILE_HEIGHT;

      gTileClips[TILE_BOTTOMLEFT].x = 80;
      gTileClips[TILE_BOTTOMLEFT].y = 160;
      gTileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
      gTileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;

      gTileClips[TILE_TOP].x = 160;
      gTileClips[TILE_TOP].y = 0;
      gTileClips[TILE_TOP].w = TILE_WIDTH;
      gTileClips[TILE_TOP].h = TILE_HEIGHT;

      gTileClips[TILE_CENTER].x = 160;
      gTileClips[TILE_CENTER].y = 80;
      gTileClips[TILE_CENTER].w = TILE_WIDTH;
      gTileClips[TILE_CENTER].h = TILE_HEIGHT;

      gTileClips[TILE_BOTTOM].x = 160;
      gTileClips[TILE_BOTTOM].y = 160;
      gTileClips[TILE_BOTTOM].w = TILE_WIDTH;
      gTileClips[TILE_BOTTOM].h = TILE_HEIGHT;

      gTileClips[TILE_TOPRIGHT].x = 240;
      gTileClips[TILE_TOPRIGHT].y = 0;
      gTileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
      gTileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;

      gTileClips[TILE_RIGHT].x = 240;
      gTileClips[TILE_RIGHT].y = 80;
      gTileClips[TILE_RIGHT].w = TILE_WIDTH;
      gTileClips[TILE_RIGHT].h = TILE_HEIGHT;

      gTileClips[TILE_BOTTOMRIGHT].x = 240;
      gTileClips[TILE_BOTTOMRIGHT].y = 160;
      gTileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
      gTileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;
    }

  }

  //Close the file
  map.close();

  //If the map was loaded fine
  return tilesLoaded;
}

bool MapManager::touchesWall(SDL_Rect box, Tile **tiles) {
  //Go through the tiles
  for (int i = 0; i < 192; ++i) {
    //If the tile is a wall type tile
    if ((tiles[i]->getType() >= 3) && (tiles[i]->getType() <= 11)) {
      //If the collision box touches the wall tile
      if ((this->checkCollision(box, tiles[i]->getBox()))) {
        return true;
      }
    }
  }

  //If no wall tiles were touched
  return false;
}
SDL_Rect *MapManager::get_tiles_clip() {
  return gTileClips; //chequearEsto
}

