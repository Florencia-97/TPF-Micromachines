#ifndef MICROMACHINES_CLIENT_TEXTURELOADER_H_
#define MICROMACHINES_CLIENT_TEXTURELOADER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "LTexture.h"
#include "../tiles/Tile.h"

class TextureLoader {
 private:
  std::unordered_map<std::string, LTexture> texture_cache;
 public:

  /*Builder of the class*/
  TextureLoader() = default;

  /*Makes a LTexture using the path "client/rendering/assets/" + name
   * POST: If the path was used previously, returns the same pointer
   * than the previous call to the fuction*/
  LTexture *load_texture(std::string name, SDL_Renderer *renderer);

};

#endif //MICROMACHINES_CLIENT_TEXTURELOADER_H_
