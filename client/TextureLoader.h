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
#include "LTexture.h"

class TextureLoader {
 public:
  TextureLoader() = default;
  bool load_texture(std::string path, LTexture texture);
};

#endif //MICROMACHINES_CLIENT_TEXTURELOADER_H_
