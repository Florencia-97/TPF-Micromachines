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
  float rotation;
  LTexture* texture;

 public:
  explicit Car();
  void addTexture(LTexture* my_texture);
  // Centers the camera over the car
  void setCamera(SDL_Rect &camera);
  void render(SDL_Rect &camera, SDL_Renderer *renderer);
  void move(int x, int y, float r);
  ~Car();
};

#endif