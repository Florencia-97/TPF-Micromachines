#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_

#include "../../../config/constants.h"
#include "../LTexture.h"
#include <SDL_events.h>
#include <SDL_system.h>
#include <list>
#include <functional>
#include <queue>

class Button {
 protected:
  SDL_Renderer *gRenderer = nullptr;
  LTexture *texture;
  SDL_Point mPosition;
  SDL_Rect area;
  std::list<std::function<void(std::string)>> callbacks;
  float oldWidth;
  float oldHeight;
  int colorChangeDuration;

 public:
  std::string id;
  std::string soundWhenPressed;

  /* Button class constructor. */
  explicit Button(std::string id, SDL_Renderer *sdl_renderer,
				  LTexture *buttonSpriteSheet);

  /*Sets the position of the button.
   * PRE: The origin of coordinates is in the upper left corner*/
  virtual void set_position(int x, int y);

  /*Adds a function to the button that runs when you click the button
   * POST: The new function does not overwrite the previous ones.*/
  void add_callback_function(const std::function<void(std::string)> &cf);

  /*Executes all the functions stored in the button by the function
   * add_callback_function()*/
  void call_callback_functions();

  /*Filter events to stay only with those of the type
   * SDL_MOUSEMOTION,SDL_MOUSEBUTTONDOWN and SDL_MOUSEBUTTONUP. In the second
   * case, returns true and executes call_callback_functions(); In the rest of the
   * cases, returns false;*/
  virtual bool handle_event(SDL_Event *e,
							std::queue<std::string> *soundQueue);

  /*Sets the area that will be the space that the button will occupy in screen.
   *PRE: both x and y must be greater than 0 for proper functioning*/
  virtual void set_area(int x, int y);

  /*Renders the button with all the corresponding effects.
   * PRE: screenWidth and screenHeight must be the width and length of the
   * screen corresponding at the time of executing this function. If any of the
   * two parameters differ from the original resolution, they will be used for
   * recalculate the position of the button in the new resolution.*/
  virtual void render(float screenWidth, float screenHeight);

  /*Changes the texture color using the values RGB passed by parameters.
   * The duration parameter is the number of frames this change is going to be
   * maintained.
   * PRE: If the value is negative, the change persists until the next
   * call of the function*/
  void change_color(int r, int g, int b, int duration);
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
