#ifndef MICROMACHINES_CLIENT_CAR_H
#define MICROMACHINES_CLIENT_CAR_H

#include <SDL_rect.h>
#include <SDL_events.h>
#include "rendering/LTexture.h"
#include "tiles/Tile.h"
#include "rendering/interfaces/Explosion.h"

class Car {
  SDL_Rect mBox;
  int rotation;
  LTexture* texture;
  Explosion explosion;

 public:
    short id;
    int health;

    explicit Car(short id);

    void addTexture(LTexture* my_texture);

    // Centers the camera over the car
    void setCamera(SDL_Rect &camera, int level_width, int level_height);

    void render(SDL_Rect &camera, SDL_Renderer *renderer, int frames);

    void move(int x, int y, int r);

    SDL_Texture *get_texture();

    ~Car();

    bool compare_id(short i);

    void loadAnimations(SDL_Renderer *gRenderer);
};

#endif