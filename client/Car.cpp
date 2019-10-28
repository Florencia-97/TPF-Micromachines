
#include "Car.h"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;
Car::Car(){
    //Initialize the collision box

    mBox.x = 0;
    mBox.y = 0;
  mBox.w = CAR_WIDTH;
  mBox.h = CAR_HEIGHT;

}

void Car::move(Tile *tiles[], MapManager manager) {
  //Move the dot left or right
  mBox.x += mVelX;
  //If the dot went too far to the left or right or touched a wall
  if ((mBox.x < 0) || (mBox.x + CAR_WIDTH > LEVEL_WIDTH) || manager.touchesWall(mBox, tiles)) {
    //move back
    mBox.x -= mVelX;
  }
  //Move the dot up or down
  mBox.y += mVelY;
  //If the dot went too far up or down or touched a wall
  if ((mBox.y < 0) || (mBox.y + CAR_HEIGHT > LEVEL_HEIGHT) || manager.touchesWall(mBox, tiles)) {
    //move back
    mBox.y -= mVelY;
  }
}

void Car::setCamera( SDL_Rect& camera ){
    //Center the camera over the dot
  camera.x = (mBox.x + CAR_WIDTH / 2) - SCREEN_WIDTH / 2;
  camera.y = (mBox.y + CAR_HEIGHT / 2) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds
    if( camera.x < 0 ) camera.x = 0;
    if( camera.y < 0 ) camera.y = 0;
    if( camera.x > LEVEL_WIDTH - camera.w ) camera.x = LEVEL_WIDTH - camera.w;
    if( camera.y > LEVEL_HEIGHT - camera.h ) camera.y = LEVEL_HEIGHT - camera.h;
}

void Car::render(SDL_Rect &camera, LTexture *texture) {
  texture->render(mBox.x - camera.x, mBox.y - camera.y);
}
void Car::handleEvent(SDL_Event event) {
  //If a key was pressed
  if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
    //Adjust the velocity
    switch (event.key.keysym.sym) {
      case SDLK_UP: mVelY -= CAR_VEL;
        break;
      case SDLK_DOWN: mVelY += CAR_VEL;
        break;
      case SDLK_LEFT: mVelX -= CAR_VEL;
        break;
      case SDLK_RIGHT: mVelX += CAR_VEL;
        break;
    }
  }
    //If a key was released
  else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
    //Adjust the velocity
    switch (event.key.keysym.sym) {
      case SDLK_UP: mVelY += CAR_VEL;
        break;
      case SDLK_DOWN: mVelY -= CAR_VEL;
        break;
      case SDLK_LEFT: mVelX += CAR_VEL;
        break;
      case SDLK_RIGHT: mVelX -= CAR_VEL;
        break;
    }
  }
}
