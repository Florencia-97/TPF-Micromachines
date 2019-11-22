#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_LUABUTTON_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_LUABUTTON_H_

#include "Button.h"
#include "TextLabel.h"
class LuaButton : public Button {
 private:
  TextLabel msg;
 public:

  /*LuaButton class builder*/
  LuaButton(SDL_Renderer *sdl_renderer, LTexture *texture);

  /*Implementation of the function to render the button.
   * The use of the screenWidth and screenHeight parameters is the same as
   * in the parent class*/
  void render(float screenWidth, float screenHeight) override;

  /* Implementation of the setPosition function inherited from the Button
   * class.
   * PRE: Internally, call Button :: set_position () and then establish the
   * correct position of the message associated with the button.
   * X and Y follow the same conditions as in the parent class*/
  void set_position(int x, int y) override;

  /*Changes the degree of transparency of the button
   * PRE: the range of i is [0: 255] being 0 transparent and 255 totally
   * opaque*/
  void change_opacity(int i);
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_LUABUTTON_H_
