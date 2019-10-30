//
// Created by brian on 10/26/19.
//

#ifndef MICROMACHINES_CLIENT_LTEXTURE_H_
#define MICROMACHINES_CLIENT_LTEXTURE_H_

#include <SDL_render.h>
#include <string>
class LTexture {
 private:
  SDL_Texture *texture;
  int width;
  int height;
 public:
  LTexture();
  ~LTexture();
  bool load_from_file(const std::string &path,
                      SDL_Renderer *renderer);
  void free();

  void set_color(Uint8 red, Uint8 green, Uint8 blue);

  void set_blend_mode(SDL_BlendMode blending);

  void set_alpha(Uint8 alpha);

  void render(int x,
              int y,
              SDL_Rect *clip = nullptr,
              double angle = 0.0,
              SDL_Point *center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE,
              SDL_Renderer *renderer = nullptr);
  int getWidth();

  int getHeight();

};

#endif //MICROMACHINES_CLIENT_LTEXTURE_H_
