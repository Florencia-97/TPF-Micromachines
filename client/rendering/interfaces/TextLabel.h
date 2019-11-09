//
// Created by brian on 11/2/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_

#include <SDL2/SDL_ttf.h>
#include "../LTexture.h"
#include "../../../config/constants.h"
class TextLabel {
    protected:
    TTF_Font *font;
    LTexture textTexture;

    SDL_Rect textArea;
    SDL_Color color;
    SDL_Renderer *renderer;

    public:
    std::string text = "";
    int x;
    int y;

    virtual void init(const std::string &msg, int x, int y, SDL_Color c, SDL_Renderer *sdl_renderer);

    void render();

    virtual void receiveInput(SDL_Event *e){};

    void updateBounds();
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_
