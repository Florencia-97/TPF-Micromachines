//
// Created by brian on 10/26/19.
//

#include <SDL2/SDL_image.h>
#include "LTexture.h"

/*Constructor of LTexture*/
LTexture::LTexture() {
  texture = nullptr;
  width = 0;
  height = 0;
}
/*Destructor of LTexture*/
LTexture::~LTexture() {
  free();
}

/*Loads a texture from the path, using the renderer*/
bool LTexture::load_from_file(const std::string &path,
                              SDL_Renderer *renderer) {
  free();
  SDL_Texture *newTexture = nullptr;
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
    printf("Unable to load image %s! SDL_image Error: %s\n",
           path.c_str(),
           IMG_GetError());
  } else {
    SDL_SetColorKey(loadedSurface,
                    SDL_TRUE,
                    SDL_MapRGB(loadedSurface->format,
                               0,
                               0xFF,
                               0xFF));
    newTexture = SDL_CreateTextureFromSurface(renderer,
                                              loadedSurface);
    if (newTexture == nullptr) {
      printf("Unable to create texture from %s! SDL_Error: %s\n",
             path.c_str(),
             SDL_GetError());
    } else {
      width = loadedSurface->w;
      height = loadedSurface->h;
    }
    SDL_FreeSurface(loadedSurface);
  }
  texture = newTexture;
  return texture != nullptr;
}

/*Resets the LTexture*/
void LTexture::free() {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
    texture = nullptr;
    width = 0;
    height = 0;
  }
}

/* Modules the color in the texture*/
void LTexture::set_color(Uint8 red,
                         Uint8 green,
                         Uint8 blue) {
  SDL_SetTextureColorMod(texture,
                         red,
                         green,
                         blue);
}

/*Set blending*/
void LTexture::set_blend_mode(SDL_BlendMode blending) {
  SDL_SetTextureBlendMode(texture, blending);
}
/*Set alpha mod*/
void LTexture::set_alpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(texture,
                         alpha);
}
/*Renders the texture. If some values are not passed, there are default
 *SDL_Rect *clip = nullptr,
 *double angle = 0.0,
 *SDL_Point *center = nullptr,
 *SDL_RendererFlip flip= SDL_FLIP_NONE,
 * SDL_Renderer* renderer = nullptr*/
void LTexture::render(int x,
                      int y,
                      SDL_Rect *clip,
                      double angle,
                      SDL_Point *center,
                      SDL_RendererFlip flip,
                      SDL_Renderer *renderer) {
  SDL_Rect renderQuad = {x, y, width, height};
  if (clip != nullptr) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  SDL_RenderCopyEx(renderer,
                   texture,
                   clip,
                   &renderQuad,
                   angle,
                   center,
                   flip);

}

int LTexture::getHeight() {
  return height;
}
int LTexture::getWidth() {
  return width;
}


