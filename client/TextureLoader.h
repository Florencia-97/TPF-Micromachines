//
// Created by brian on 10/26/19.
//

#ifndef MICROMACHINES_CLIENT_TEXTURELOADER_H_
#define MICROMACHINES_CLIENT_TEXTURELOADER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include "LTexture.h"
#include "Tile.h"

class TextureLoader {
 public:

  TextureLoader() = default;

  static bool load_texture(const std::string &path, LTexture *texture, SDL_Renderer *renderer);

  static void close(Tile **tiles, int totalTiles, std::vector<LTexture> vector,
                    SDL_Renderer *renderer, SDL_Window *window);
};

#endif //MICROMACHINES_CLIENT_TEXTURELOADER_H_
