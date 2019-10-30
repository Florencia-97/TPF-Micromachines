#ifndef MICROMACHINES_CLIENT_CAR_H
#define MICROMACHINES_CLIENT_CAR_H

#include <SDL_rect.h>
#include <SDL_events.h>
#include "rendering/LTexture.h"
#include "tiles/Tile.h"

class Car {
 private:
  //Collision box of the dot
  SDL_Rect mBox;
  //The dimensions of the car
  const int CAR_WIDTH = 20;
  const int CAR_HEIGHT = 20;

  LTexture* texture;


 public:
  //Initializes the variables
  explicit Car();

  void addTexture(LTexture* my_texture);

  //Centers the camera over the car
  void setCamera(SDL_Rect &camera);

  //Shows the car on the screen
  void render(SDL_Rect &camera, SDL_Renderer *renderer);

  void move();

  ~Car();
};

#endif