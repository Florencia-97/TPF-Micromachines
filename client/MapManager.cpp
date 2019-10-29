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
        //tiles[i] = new Tile(x, y, tileType);
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
    }
    //Clip the sprite sheet (Clip de img. Only for example)
    if (tilesLoaded) {
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

      gTileClips[3].x = 80;
      gTileClips[3].y = 0;
      gTileClips[3].w = TILE_WIDTH;
      gTileClips[3].h = TILE_HEIGHT;

      gTileClips[4].x = 80;
      gTileClips[4].y = 80;
      gTileClips[4].w = TILE_WIDTH;
      gTileClips[4].h = TILE_HEIGHT;

      gTileClips[5].x = 80;
      gTileClips[5].y = 160;
      gTileClips[5].w = TILE_WIDTH;
      gTileClips[5].h = TILE_HEIGHT;

      gTileClips[6].x = 160;
      gTileClips[6].y = 0;
      gTileClips[6].w = TILE_WIDTH;
      gTileClips[6].h = TILE_HEIGHT;

      gTileClips[7].x = 160;
      gTileClips[7].y = 80;
      gTileClips[7].w = TILE_WIDTH;
      gTileClips[7].h = TILE_HEIGHT;

      gTileClips[8].x = 160;
      gTileClips[8].y = 160;
      gTileClips[8].w = TILE_WIDTH;
      gTileClips[8].h = TILE_HEIGHT;

      gTileClips[9].x = 240;
      gTileClips[9].y = 0;
      gTileClips[9].w = TILE_WIDTH;
      gTileClips[9].h = TILE_HEIGHT;

      gTileClips[10].x = 240;
      gTileClips[10].y = 80;
      gTileClips[10].w = TILE_WIDTH;
      gTileClips[10].h = TILE_HEIGHT;

      gTileClips[11].x = 240;
      gTileClips[11].y = 160;
      gTileClips[11].w = TILE_WIDTH;
      gTileClips[11].h = TILE_HEIGHT;
    }
  }

  //Close the file
  map.close();

  //If the map was loaded fine
  return tilesLoaded;
}

bool MapManager::touchesWall(SDL_Rect box, Tile **tiles) {
  //Go through the tiles
  for (int i = 0; i < 12; ++i) { //Tiene numeros hardcodeados que son para el ejemplo solamente
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

