//
// Created by brian on 10/28/19.
//

#ifndef MICROMACHINES_CLIENT_TILE_H_
#define MICROMACHINES_CLIENT_TILE_H_

#include <SDL_rect.h>
#include "../rendering/LTexture.h"

class Tile{
    SDL_Rect mBox;
    int mType;
    LTexture* texture;
public:
    Tile(int x, int y, int tileType, LTexture* texture, float width, float height);
    void render(SDL_Rect &camera, SDL_Renderer *renderer);
    void renderWithSize(SDL_Rect &camera, SDL_Renderer *renderer);
    int getType();
    SDL_Rect& getBox();
    // Why static?? TODO: method one collides with other one.checkCollision(other);
    // bool chechCollision(SDL_Rect b); I am a, why i am a parameter?
    static bool checkCollision(SDL_Rect a, SDL_Rect b);
};

#endif //MICROMACHINES_CLIENT_TILE_H_
