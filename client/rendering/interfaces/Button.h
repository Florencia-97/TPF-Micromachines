//
// Created by brian on 10/30/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_

#include "../../../config/constants.h"
#include "../LTexture.h"

#include <SDL_events.h>
#include <SDL_system.h>
class Button {
 private:
//The window we'll be rendering to
  SDL_Window *gWindow = nullptr;
//The window renderer
  SDL_Renderer *gRenderer = nullptr;

//Mouse button sprites
  SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
  LTexture gButtonSpriteSheetTexture;
//Buttons objects
 public:
  //Initializes internal variables
  Button(SDL_Window *window, SDL_Renderer *sdl_renderer);
  //Sets top left position
  void setPosition(int x, int y);
  bool load_media();
  //Handles mouse event
  void handleEvent(SDL_Event *e);

  //Shows button sprite
  void render();

 private:
  //Top left position
  SDL_Point mPosition;
  //Currently used global sprite
  ButtonSprite mCurrentSprite;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
