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
  int health;
  Explosion *explosion;

 public:
    short id;

    explicit Car(short id);

    void addTexture(LTexture* my_texture);

    // Centers the camera over the car
    void setCamera(SDL_Rect &camera, int level_width, int level_height);

    void render(SDL_Rect &camera, SDL_Renderer *renderer);

    void move(int x, int y, int r);
  void explode(Explosion animation, SDL_Renderer *renderer);
    SDL_Texture *get_texture();

    ~Car();
    bool compare_id(short i);
};

#endif