//
// Created by brian on 10/26/19.
//
#ifndef MICROMACHINES_SDLSTARTER_H
#define MICROMACHINES_SDLSTARTER_H
#include "../tiles/Tile.h"

class SDLStarter {
 private:
  const int screenWidth;
  const int screenHeight;
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
 public:
  SDLStarter(const int width,
             const int height) :
      screenWidth(width),
      screenHeight(height),
      window(nullptr),
      renderer(nullptr) {};
  bool init();
  SDL_Renderer *get_global_renderer();
  void close();

};

#endif //MICROMACHINES_SDLSTARTER_H
