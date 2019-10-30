
#include "Car.h"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

Car::Car(LTexture* myTexture){
    //Initialize the collision box
    mBox.x = 0;
    mBox.y = 0;
    mBox.w = CAR_WIDTH;
    mBox.h = CAR_HEIGHT;
    texture = myTexture;
}

void Car::move() {
  //Move the dot left or right
  //todo change

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

void Car::render(SDL_Rect &camera, SDL_Renderer *renderer) {
  texture->render(mBox.x - camera.x, mBox.y - camera.y, nullptr, 0.0, nullptr, SDL_FLIP_NONE, renderer);
}
void Car::handleEvent(SDL_Event event) {
  //todo delete
}

Car::~Car() {
    if (texture != nullptr){
        texture->free();
    }
}
