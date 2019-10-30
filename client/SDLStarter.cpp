//
// Created by brian on 10/26/19.
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDLStarter.h"


bool SDLStarter::init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("Warning: Linear texture filtering not enabled!");
    }
    window = SDL_CreateWindow("Micromachines",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              this->screenWidth,
                              this->screenHeight,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (renderer == nullptr) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      } else {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
          success = false;
        }
      }
    }
  }
  return success;
}
SDL_Renderer *SDLStarter::get_global_renderer() {
  return renderer;
}
void SDLStarter::close(Tile *tiles[]) {
  //Deallocate tiles
  for (int i = 0; i < 192; ++i) {
    if (tiles[i] == nullptr) {
      delete tiles[i];
      tiles[i] = nullptr;
    }
  }

  //Destroy window
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = nullptr;
  renderer = nullptr;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}
