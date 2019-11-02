
#include "Car.h"
#include "../config/constants.h"

Car::Car(){
    mBox.x = 0;
    mBox.y = 0;
    mBox.w = w;
    mBox.h = h;
    rotation = 0;
  id = 0;
}

void Car::addTexture(LTexture *my_texture) {
    texture = my_texture;
}

void Car::move(int x, int y, int r) {
  this->mBox.x = x;
  this->mBox.y = y;
  this->rotation = r;
}

void Car::setCamera( SDL_Rect& camera ){
  camera.x = (mBox.x + w / 2) - SCREEN_WIDTH / 2;
  camera.y = (mBox.y + h / 2) - SCREEN_HEIGHT / 2;
    // Keep the camera in bounds
  if (camera.x < 0) camera.x = 0;
  if (camera.y < 0) camera.y = 0;
  if (camera.x > LEVEL_WIDTH - camera.w) camera.x = LEVEL_WIDTH - camera.w;
  if (camera.y > LEVEL_HEIGHT - camera.h) camera.y = LEVEL_HEIGHT - camera.h;
}

void Car::render(SDL_Rect &camera, SDL_Renderer *renderer) {
  //SDL_RenderCopy(gRenderer, texture->get_texture(), nullptr, &area);
  texture->render_with_size(mBox.x, mBox.y, rotation, renderer, CAR_WIDTH, CAR_HEIGHT);
}

Car::~Car() {
    if (texture != nullptr){
        texture->free();
    }
}
SDL_Texture *Car::get_texture() {
  return this->texture->get_texture();
}
bool Car::compare_id(short i) {
  return this->id == i;
}
void Car::set_id(short givenID) {
  this->id = givenID;

}
