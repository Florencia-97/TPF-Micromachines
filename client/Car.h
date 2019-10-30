#ifndef MICROMACHINES_CLIENT_CAR_H
#define MICROMACHINES_CLIENT_CAR_H

#include <SDL_rect.h>
#include <SDL_events.h>
#include "rendering/LTexture.h"
#include "tiles/Tile.h"

class Car {
  SDL_Rect mBox;
  const int w = 20;
  const int h = 20;
  LTexture* texture;

 public:
  explicit Car();
  void addTexture(LTexture* my_texture);
  // Centers the camera over the car
  void setCamera(SDL_Rect &camera);
  void render(SDL_Rect &camera, SDL_Renderer *renderer);
  void move();
  ~Car();
};

#endif