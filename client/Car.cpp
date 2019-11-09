
#include <iostream>
#include "Car.h"
#include "../config/constants.h"

Car::Car(short id){
    mBox.x = 0;
    mBox.y = 0;
    mBox.w = CAR_WIDTH;
    mBox.h = CAR_HEIGHT;
    rotation = 0;
    this->id = id;
  health = 100;
  explosion = new Animation();
}

void Car::addTexture(LTexture *my_texture) {
    texture = my_texture;
}

void Car::move(int x, int y, int r) {
  this->mBox.x = x -  CAR_WIDTH/2;
  this->mBox.y = y - CAR_HEIGHT/2;
  this->rotation = r;
}

void Car::setCamera( SDL_Rect& camera, int level_width, int level_height ){
  camera.x = (mBox.x + mBox.w / 2) - SCREEN_WIDTH / 2;
  camera.y = (mBox.y + mBox.h / 2) - SCREEN_HEIGHT / 2;;
    // Keep the camera in bounds
  if (camera.x < 0) camera.x = 0;
  if (camera.y < 0) camera.y = 0;
  if (camera.x > level_width - camera.w) camera.x = level_width - camera.w;
  if (camera.y > level_height - camera.h) camera.y = level_height - camera.h;
}

void Car::render(SDL_Rect &camera, SDL_Renderer *renderer) {
  //SDL_RenderCopy(gRenderer, texture->get_texture(), nullptr, &area);
  int x = rand()%2;
  int y = rand()%2;
  texture->render_with_size(mBox.x + x - camera.x,
                            mBox.y + y - camera.y,
                            rotation,
                            renderer,
                            CAR_WIDTH,
                            CAR_HEIGHT,
                            false);
  if (health == 0) {
    this->explosion->play(renderer, mBox.x, mBox.y);
  }
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