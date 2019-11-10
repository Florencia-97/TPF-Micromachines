//
// Created by brian on 10/30/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_

#include "../../../config/constants.h"
#include "../LTexture.h"
#include "ButtonAnswer.h"

#include <SDL_events.h>
#include <SDL_system.h>
#include <list>
#include <functional>
#include <queue>

class Button {
    void callCallbackFunctions();

 protected:
    SDL_Renderer *gRenderer = nullptr;
    LTexture *texture;
    SDL_Point mPosition;
    SDL_Rect area;
    std::list<std::function<void(std::string)>> callbacks;
  float oldWidth;
  float oldHeight;
  int colorChangeDuration;
 public:
    std::string id;
    std::string soundWhenPressed;
    explicit Button(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet);

    explicit Button(std::string id, SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet);

    //POS adds a function that will be called when the button is clicked;
    void addCallbackFunction(std::function<void(std::string)> cf);

    virtual void setPosition(int x, int y);

    //Handles mouse event. If the button is clicked, returns true
    virtual bool handleEvent(SDL_Event *e, std::queue<std::string>* soundQueue);

  virtual void render(float screenWidth, float screenHeight);

    virtual void set_area(int x, int y);


    //POS apply a color(r,g,b) change to the button for duration frames
    //if duration is negative then the change persists until called again
    void changeColor(int r, int g, int b, int duration);

    std::string getId();
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
