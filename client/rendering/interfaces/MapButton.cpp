//
// Created by brian on 11/2/19.
//

#include "MapButton.h"
MapButton::MapButton(SDL_Renderer *sdl_renderer, LTexture *buttonSpriteSheet) : Button(sdl_renderer,
                                                                                       buttonSpriteSheet) {

}
void MapButton::set_area(int x, int y) {
  area = {x, y, MAP_BUTTON_WIDTH, MAP_BUTTON_HEIGHT};
}
