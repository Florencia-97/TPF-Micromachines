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
  bool load_from_file(const std::string &path, SDL_Renderer *renderer);
  void free();

  // RGB
  void set_color(Uint8 red, Uint8 green, Uint8 blue);

  void render(int x, int y, SDL_Rect *clip, double angle,
              SDL_Point *center, SDL_RendererFlip flip, SDL_Renderer *renderer);

  int getWidth();
  SDL_Texture *get_texture();
  void render_with_size(int x, int y, int r, SDL_Renderer *renderer, int width, int height);
  int getHeight();

};

#endif //MICROMACHINES_CLIENT_LTEXTURE_H_
