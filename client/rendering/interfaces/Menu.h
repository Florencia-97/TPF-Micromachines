#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_MENU_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_MENU_H_

#include <SDL_system.h>
#include <queue>
#include "../LTexture.h"
#include "../../../config/constants.h"
#include "Button.h"
#include "TextLabel.h"
#include "TextBox.h"
#include <condition_variable>
#include <common/ThreadQueue.h>
#include "../TextureLoader.h"
#include "../../../common/infostream/InfoBlock.h"
#include "LuaButton.h"

class Menu {
 private:
  LTexture wallpaper;
  TextureLoader textureLoader;
  std::queue<SDL_Event> *mouse_queue;
  std::queue<SDL_Event> *text_queue;
  ThreadQueue *sound_queue;
  std::shared_ptr<Button> connectButton;
  SDL_Renderer *gRenderer;

  std::vector<Button> carButtons;
  std::vector<Button> mapButtons;
  std::vector<Button> *active_buttons;
  LuaButton *iaButton;
  std::condition_variable *game_ready_cv;
  std::list<TextLabel> open_games;

  TextLabel label_choose_car;
  TextLabel flavor_text;
  TextBox notification;

  /*Loads all necessary textures and images for the correct class performance*/
  void load_media();

  /*Sets the positions and the corresponded function for the buttons in the
   * first screen of the game. In order to do that, uses
   *  Button::add_callback_function()*/
  void set_buttons_positions();

  /*Creates the buttons for the first screen of the game*/
  void create_buttons_first_menu();

  /*Sets all the elements needed in set_main_menu_mode()*/
  void set_elements();

 public:
  std::string car_selected;
  std::string map_selected;
  TextBox textbox_lobby_name;
  bool ready;
  bool iaOn;
  std::queue<InfoBlock> open_games_update;

  /* Initialize the menu.
   * PRE: For the correct functioning of the object, it is
   * necessary that this function be executed first */
  void init(SDL_Renderer *sdl_renderer, std::queue<SDL_Event> *mouseEventsQueue,
			std::queue<SDL_Event> *textQueue,
			std::condition_variable *attemptConnectionCV,
            ThreadQueue *soundQueue);

  /*Renders the first screen of the game.
   * PRE: screenWidth and screenHeight must be the screen resolution parameters
   * at the moment of the execution*/
  void render_first_menu(float screenWidth, float screenHeight);

  /*Sets positions and images of the buttons for the first screen of the game
 * Also, adds the correct callback function for each button using
 * Button::add_callback_function()*/
  void set_buttons_map_screen();

  /*Renders the second screen of the game for the owner of the lobby.
   * PRE: screenWidth and screenHeight must be the screen resolution parameters
   * at the moment of the execution*/
  void render_as_leader(int screenWidth, int screenHeight);

  /*Creates all the buttons needed for the second screen of the game for the
   * owner of the lobby*/
  void create_map_buttons();

  /*Renders the second screen of the game for the player who is not the owner
   * of the lobby.
   * PRE: screenWidth and screenHeight must be the screen resolution parameters
   * at the moment of the execution*/
  void render_as_follower(int screenWidth, int screenHeight);

  /*Process all events that have come from the keyboard and are stored in the
   * queue textQueue passed by parameter at the time of executing the init ()
   * function*/
  void process_events_keyboard();

  /*Process all events that have come from the mouse and are stored in the
   * queue mouseEventsQueue passed by parameter at the time of executing the
   * init() function*/
  bool process_events_mouse();

  /*Sets all the elements needed for the menu. Loads images, sets buttons,
   * plays the music and loads all the lobby's names*/
  void set_main_menu_mode();

  /*Displays the notifications in the first menu*/
  void display_notification(std::string msg);

  /*Activates the lobby buttons*/
  void start_lobby_buttons();

  /*Updates the menu with the name of all the open games at the moment of the
   * execution*/
  void _updateOpenGames();


  /*Destroyer of the class*/
  ~Menu();

  bool get_ia();
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_MENU_H_
