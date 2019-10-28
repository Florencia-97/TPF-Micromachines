#ifndef _CAR_
#define _CAR_

#include <SDL_rect.h>
#include <SDL_events.h>
#include "LTexture.h"
class Car{
 private:
  //Collision box of the dot
  SDL_Rect mBox;
  //The dimensions of the car
  const int CAR_WIDTH = 20;
  const int CAR_HEIGHT = 20;
  //Speed of car
  const int CAR_VEL = 10;
  int mVelX, mVelY;
 public:
  //Initializes the variables
  Car();
  //Centers the camera over the car
  void setCamera(SDL_Rect &camera);
  //Shows the car on the screen
  void render(SDL_Rect &camera, LTexture *texture);
  void handleEvent(SDL_Event event);
};

#endif