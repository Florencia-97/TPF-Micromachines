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

	/*Constructor de la clase Button.*/
	explicit Button(std::string id, SDL_Renderer *sdl_renderer,
					LTexture *buttonSpriteSheet);

  /*Establece la posicion del boton.
   * PRE: El origen de coordenadas se encuentra en el extremo superior
   * izquierdo*/
  virtual void setPosition(int x, int y);

  /*Agrega una funcion al boton que se ejecutara al momento de clickear el
   * boton
   * POST: La nueva funcion, no sobreescribe las anteriores.*/
  void addCallbackFunction(const std::function<void(std::string)> &cf);

  /*Ejecuta todas las funciones almacenadas en el boton por medio de la
   * funcion
   * addCallbackFunction()*/
	void callCallbackFunctions();

  /*Filtra los eventos para quedarse solamente con aquellos del tipo
   * SDL_MOUSEMOTION,SDL_MOUSEBUTTONDOWN y SDL_MOUSEBUTTONUP. En el caso del
   * 2do, devuelve true y ejecutacallCallbackFunctions(); En el resto de los
   * casos, solo devuelve false;*/
	virtual bool handleEvent(SDL_Event *e, std::queue<std::string> *soundQueue);

  /*Setea el area que sera representara el espacio que ocupara el boton en
   * pantalla. PRE: tanto x como y deben ser mayores que 0 para su correcto
   * funcionamiento*/
	virtual void set_area(int x, int y);

  /*Renderiza el boton con todos los efectos correspondientes.
   * PRE: screenWidth y screenHeight deben ser el ancho y largo de la pantalla
   * correspondientes al momento de ejecutar esta funcion. Si alguno de los
   * dos parametros difiere de la resolucion original, se utilizaran para
   * recalcular la posicion en la nueva resolucion.*/
  virtual void render(float screenWidth, float screenHeight);

  /*Cambia el color de la textura utilizando los valores
   * RGB pasado por parametros. El parametro duration, es la cantidad de frames
   * que se va a mantener este cambio.
   * PRE: Si el valor es negativo, el cambio persiste hasta el proximo
   * llamado de la funcion*/
  void changeColor(int r, int g, int b, int duration);
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_H_
