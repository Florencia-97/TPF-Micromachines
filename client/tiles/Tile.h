#ifndef MICROMACHINES_CLIENT_TILE_H_
#define MICROMACHINES_CLIENT_TILE_H_

#include <SDL_rect.h>
#include "../rendering/LTexture.h"

class Tile {
  SDL_Rect mBox;
  LTexture *texture;
 public:

  /*Builder of the class Tile*/
  Tile(int x, int y, LTexture *my_text, float width, float height);

  /*Renders a tile with the size of the image used for its creation and stored
   * in the LTexture designated in its builder.
   * PRE: The camera parameter is used for cases where the image does not
   * completely enter the screen*/
  void render(SDL_Rect &camera, SDL_Renderer *renderer);

  SDL_Rect &getBox();
};

#endif //MICROMACHINES_CLIENT_TILE_H_
