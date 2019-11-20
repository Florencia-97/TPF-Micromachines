#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_EXPLOSION_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_EXPLOSION_H_

#include <SDL_rect.h>
#include "../LTexture.h"
#include "Animation.h"
#include "../../../config/constants.h"
class Explosion : public Animation {
 private:
  LTexture actualSprite;
  SDL_Rect totalSprites[TOTAL_FRAMES];
  int frame;

 public:

  /*Constructor de la clase explosion*/
  Explosion();

  /*Implementacion con de la funcion heredada para la creacion de los frames
   * de la animacion de la explosion.
   * PRE: Utiliza el archivo client/rendering/assets/decoration/explosion.png*/
  void load_frames(SDL_Renderer *gRenderer) override;

  /*Implementacion de la funcion de renderizado de un frame de la animacion.*/
  void render(int x, int y, SDL_Rect *clip, SDL_Renderer *gRenderer) override;

  /*Implementacion de la funcion de reproduccion de la animacion*/
  void play(SDL_Renderer *gRenderer, int x, int y) override;
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_EXPLOSION_H_
