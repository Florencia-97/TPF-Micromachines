

#ifndef MICROMACHINES_TEXTBOX_H
#define MICROMACHINES_TEXTBOX_H

#include "TextLabel.h"

class TextBox : public TextLabel {

public:
    void init(const std::string &msg, int x, int y, int size, SDL_Color c, SDL_Renderer *sdl_renderer) override;

    void receiveInput(SDL_Event *e) override;

  void render(float screenWidth, float screenHeight) override;
};


#endif //MICROMACHINES_TEXTBOX_H
