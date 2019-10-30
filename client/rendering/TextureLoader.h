//
// Created by brian on 10/26/19.
//

#ifndef MICROMACHINES_CLIENT_TEXTURELOADER_H_
#define MICROMACHINES_CLIENT_TEXTURELOADER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "LTexture.h"
#include "../tiles/Tile.h"

class TextureLoader {
    std::unordered_map<std::string, LTexture> texture_cache;

    public:

    TextureLoader() = default;

    LTexture* load_texture(std::string name, SDL_Renderer *renderer);

    void close(Tile **tiles, int totalTiles, std::vector<LTexture> vector,
                    SDL_Renderer *renderer, SDL_Window *window);
};

#endif //MICROMACHINES_CLIENT_TEXTURELOADER_H_
