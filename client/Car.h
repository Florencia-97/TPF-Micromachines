#ifndef MICROMACHINES_CLIENT_CAR_H
#define MICROMACHINES_CLIENT_CAR_H

#include <SDL_rect.h>
#include <SDL_events.h>
#include <queue>
#include <common/ThreadQueue.h>
#include "rendering/LTexture.h"
#include "tiles/Tile.h"
#include "rendering/interfaces/Explosion.h"

class Car {
  SDL_Rect mBox;
  int rotation;
  LTexture *texture;
  Explosion explosion;
  short id;
  int health;

 public:

  /*Constructor of the class*/
  explicit Car(short id);

  /*Adds a texture to the car in order to represent the car in the screen
   * at the moment of rendering*/
  void add_texture(LTexture *my_texture);

  /*Centers the camera over the car using the level values for this.
  * PRE: level_width and level_height must be greather than 0*/
  void set_camera(SDL_Rect &camera, int level_width, int level_height);

  /*Renders the texture stored in the car.
   * PRE: For this function to work properly, it is necessary that a texture
   * has been previously saved using the add_texture method
   * POST: For making the efect of the car moving, this function renders
   * the car in the position x+ rand(2), y + rand(1) */
  void render(SDL_Rect &camera, SDL_Renderer *renderer, int frames, ThreadQueue *sq);

  /*Places the car in the position x,y and rotates it using the rotation
   * parameter.
   * POST: There is not animation between one position or other*/
  void move(int x, int y, int rotationValue);

  /*Changes the value of the health of the car.
   * POST: The value newLife is the new valor*/
  void modify_health(int newLife);

  /*Returns the id of the car.
   * POST: This value given in the constructor of the class is never modified*/
  short get_id();

  /*Loads the animation of the explosion to the car in order to play it in the
   * future*/
  void load_animations(SDL_Renderer *gRenderer);

};

#endif