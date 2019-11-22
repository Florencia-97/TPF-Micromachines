//
// Created by brian on 11/2/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_

#include <SDL2/SDL_ttf.h>
#include "../LTexture.h"
#include "../../../config/constants.h"
#include <queue>

class TextLabel {
  std::queue<std::string> stagedText;
  std::queue<SDL_Color> stagedColors;
  int rate;
 protected:
  TTF_Font *font;
  LTexture textTexture;

  SDL_Rect textArea;
  SDL_Color color;
  SDL_Renderer *renderer;

  /*Update the message shown if there was any modification since the last
   * call*/
  void _update();

  float oldWidth;
  float oldHeight;
  int current_frame;
 public:
  std::string text = "";
  int x;
  int y;
  bool renderText;

  /*Constructor of the class*/
  TextLabel();

  /* Initialize the class.
   * PRE: For the correct functioning of the object, it is necessary that this
   * function be executed first */
  virtual void init(const std::string &msg, int x, int y, int size,
					SDL_Color c, SDL_Renderer *sdl_renderer);

  /*Sets the rate for the intermittent animation*/
  void set_intermittent_rate(int rate);

  /*Adds a change in the text to the queue stagedText*/
  void stage_text_change(std::string m);

  /*Implementation of the rendering for the class.
   * * PRE: screenWidth and screenHeight must be the width and length of the
   * screen corresponding at the time of executing this function. If any of the
   * two parameters differ from the original resolution, they will be used for
   * recalculate the position of the button in the new resolution.*/
  virtual void render(float screenWidth, float screenHeight);

  /*Virtual function that must be implemented by the classes that inherit
   * from this*/
  virtual void receiveInput(SDL_Event *e) {};

  /*Update the borders of the image that represents the text*/
  void updateBounds();

  /*Destructor of the class*/
  ~TextLabel();
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_
