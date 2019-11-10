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
    int current_frame;
    int rate;

    protected:
    TTF_Font *font;
    LTexture textTexture;

    SDL_Rect textArea;
    SDL_Color color;
    SDL_Renderer *renderer;

    void _update();

    public:
    std::string text = "";
    int x;
    int y;

    virtual void init(const std::string &msg, int x, int y, int size, SDL_Color c, SDL_Renderer *sdl_renderer);

    void init_intermitent_anim(int rate);

    void stageTextChange(std::string m);

    void stageColorChange(SDL_Color c);

    void render();

    virtual void receiveInput(SDL_Event *e){};

    void updateBounds();

    bool renderText;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_FONT_H_
