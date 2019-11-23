#ifndef MICROMACHINES_SDLSTARTER_H
#define MICROMACHINES_SDLSTARTER_H
#include "../tiles/Tile.h"

class SDLStarter {
 private:
  const int screenWidth;
  const int screenHeight;
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_Surface* icon;

 public:
  /*Builder of the class SDLStarter.
   * PRE: screenWidth and screenHeight are the dimensions of the window which
   * is initialized here*/
  SDLStarter(const int width, const int height) :
	  screenWidth(width), screenHeight(height), window(nullptr),
      renderer(nullptr) {};

  /*Initializes all the SDL libraries. If any of the libraries fails to
   * initialize, it does not throw an exception, but reports the same by
   * console*/
  bool init();

  /*Returns the renderer asociated to this object*/
  SDL_Renderer *get_global_renderer();

  /*Returns the dimensions of the window at the moment of the execution of this
   * function*/
  void get_screen_dimensions(int *width, int *height);

  /*Closes all the libraries and frees all the memorie used in the init
   * function*/
  void close();

  /*Initializes the libraries SDL_Img, SDL_Mix and SDL_TTF.If any of the
   * libraries fails to initialize, returns false*/
  bool initialize_libraries(bool success) const;
};

#endif //MICROMACHINES_SDLSTARTER_H
