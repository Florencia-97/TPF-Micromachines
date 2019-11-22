#ifndef MICROMACHINES_CLIENT_LTEXTURE_H_
#define MICROMACHINES_CLIENT_LTEXTURE_H_

#include <SDL_render.h>
#include <string>
#include <SDL_ttf.h>

class LTexture {
 private:
  SDL_Texture *texture;
  int width;
  int height;
  std::string texture_name;
 public:
  LTexture();
  ~LTexture();
  bool load_from_file(const std::string &path, SDL_Renderer *renderer);
  void free();
  std::string get_string_name();
  // RGB
  void set_color(Uint8 red, Uint8 green, Uint8 blue);

  void render(int x, int y, SDL_Rect *clip, double angle,
              SDL_Point *center, SDL_RendererFlip flip, SDL_Renderer *renderer);

  int getWidth();
  SDL_Texture *get_texture();
  void render_with_size(float x,
                        float y,
                        int r,
                        SDL_Renderer *renderer,
                        int widthParam,
                        int heightParam,
                        bool id);
  int getHeight();
  void loadFromRenderedText(const std::string &msg, SDL_Color color, TTF_Font *font, SDL_Renderer *renderer);
  void setAlpha(Uint8 alpha);

  bool isLoaded();
};

#endif //MICROMACHINES_CLIENT_LTEXTURE_H_
