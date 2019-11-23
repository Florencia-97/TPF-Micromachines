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

  /*Builder of the class LTexture*/
  LTexture();

  /*Using the parameter path, this function loads the image in the LTexture
   * object*/
  bool load_from_file(const std::string &path, SDL_Renderer *renderer);

  /*Release the texture using SDL methods*/
  void free();

  /*Sets a color mask over the image using the rgb values. These must belong
   * to the interval [0: 255]*/
  void set_color(Uint8 red, Uint8 green, Uint8 blue);

  /*Render the image in the x position and respecting the SDL convention.
   * PRE: Center and angle, represent the center and angle of rotation. Finally,
   * flip is Finally, flip, is one of the SDL constants to select if you want
   * to flip in any direction.
   * POST: The size of the image is the same than the file used in
   * load_from_file()*/
  void render(int x, int y, SDL_Rect *clip, double angle,
			  SDL_Point *center, SDL_RendererFlip flip, SDL_Renderer *renderer);

  /*Returns the width of the image stored in the object*/
  int get_width();

  /*Returns the height of the image stored in the object*/
  int getHeight();

  /*Returns  the pointer to the SDL_Texture stored in the object.
   * POST: If there is not a texture stored, it returns nullptr*/
  SDL_Texture *get_texture();

  /*REnders the image in the x and y position respecting the SDL convention.
   * In this version, the image will have the dimensions given by height and
   * width.
   * PRE: R is the value of the rotation that you want to apply to the image*/
  void render_with_size(float x, float y, int r, SDL_Renderer *renderer,
						int widthParam, int heightParam, bool id);

  /*Create an image in which the message given by parameter will be using the
   * font given by parameter*/
  void loadFromRenderedText(const std::string &msg, SDL_Color color,
							TTF_Font *font, SDL_Renderer *renderer);

  /*Sets an alpha mask to the image stored in the object*/
  void setAlpha(Uint8 alpha);

  /*Destroyer of the object*/
  ~LTexture();
};

#endif //MICROMACHINES_CLIENT_LTEXTURE_H_
