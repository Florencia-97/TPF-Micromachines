

#ifndef MICROMACHINES_TEXTBOX_H
#define MICROMACHINES_TEXTBOX_H

#include "TextLabel.h"

class TextBox : public TextLabel {

 public:

  /*Itializes the TextBox class.
   * PRE: X and Y are the position values. The (0,0) is in the left upper
   * corner. Size is the size of the font.*/
  void init(const std::string &msg, int x, int y, int size, SDL_Color c,
			SDL_Renderer *sdl_renderer) override;

  /*Handles the SDL_Event changing the msg showed only if event->type is
   * SDL_TEXTINPUT*/
  void receiveInput(SDL_Event *event) override;

  /*Renders the TextBox.
   * PRE: screenWidth and screenHeight must be the width and length of the
   * screen corresponding at the time of executing this function. If any of the
   * two parameters differ from the original resolution, they will be used for
   * recalculate the position of the button in the new resolution.*/
  void render(float screenWidth, float screenHeight) override;
};

#endif //MICROMACHINES_TEXTBOX_H
