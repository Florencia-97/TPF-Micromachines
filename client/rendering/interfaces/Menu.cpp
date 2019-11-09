#include <iostream>
#include "Menu.h"
#include "../../../config/constants.h"
#include "CarButton.h"
#include "ConnectButton.h"
#include "MapButton.h"
#include "TextLabel.h"

void Menu::init(SDL_Renderer *sdl_renderer, std::queue<SDL_Event> *gQueue, std::queue<SDL_Event> *textQueue,
                std::condition_variable *attempConnectionCV) {
    this->text_queue = textQueue;
    this->mouse_queue = gQueue;
    this->gRenderer = sdl_renderer;
    this->game_ready_cv = attempConnectionCV;
    map_selected = "\n";
    car_selected = "RED_CAR";
}

void Menu::setMainMenuMode(){
    try {
      if (!carButtons.empty()) return;
        load_media();
        set_buttons_positions();
    } catch(...) {
        throw std::runtime_error("Failed to initialize textures!\n");
    }
    SDL_StartTextInput();
    SDL_Color gold{255, 189, 27, 0xFF};
    SDL_Color white{255, 255, 255, 0xFF};
    label_choose_car.init("CLICK A CAR TO SELECT", SCREEN_WIDTH/2, 200, gold, gRenderer);
    textbox_lobby_name.init("START TYPING THE NAME OF YOUR SESSION", SCREEN_WIDTH/2, 450, gold, gRenderer);
    flavor_text.init("fiuba 2019 all rights reserved",
            SCREEN_WIDTH/2, SCREEN_HEIGHT-30, white, gRenderer);
    active_buttons = &carButtons;
}

bool Menu::processEventsMouse() {
  while (!mouse_queue->empty()) {
       for (auto &button : *active_buttons) {
          if (button.handleEvent(&mouse_queue->front())){
            while (!mouse_queue->empty()) mouse_queue->pop();
            return true;
            }
        }
      if (connectButton->handleEvent(&mouse_queue->front())){
          while (!mouse_queue->empty()) mouse_queue->pop();
          return true;
      }
      mouse_queue->pop();
    }
  return false;
}

void Menu::processEventsKeyboard() {
  while (!text_queue->empty()) {
    textbox_lobby_name.receiveInput(&text_queue->front());
    text_queue->pop();
  }
  textbox_lobby_name.updateBounds();
}


void Menu::render_first_menu() {
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    wallpaper.render_with_size(0, 0, 0, gRenderer, SCREEN_HEIGHT, SCREEN_WIDTH, true);
    for (auto &button : carButtons) {
      button.render();
    }
    label_choose_car.render();
    textbox_lobby_name.render();
    flavor_text.render();
    connectButton->render();
    SDL_RenderPresent(gRenderer);
}

void Menu::dummy_init_as_leader() {
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
  set_buttons_as_leader();
  LTexture msg;
  wallpaper.render_with_size(0, 0, 0, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT,true);
  msg.load_from_file("client/rendering/assets/all_images/Decor/ChooseMsg.png", gRenderer);
  msg.render_with_size(720, 500, 0, gRenderer, 800, 500,false);
  for (auto &button : mapButtons) {
    button.render();
  }
  SDL_RenderPresent(gRenderer);
}


void Menu::init_as_follower() {
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
  wallpaper.load_from_file("client/rendering/assets/all_images/Decor/waiting.png", gRenderer);
  wallpaper.render_with_size(0, 0, 0, gRenderer, 0, 0,true);
  SDL_RenderPresent(gRenderer);
}

void Menu::set_buttons_positions() {
  carButtons[0].setPosition(BLUE_CAR_BUTTON_X, BLUE_CAR_BUTTON_Y);
  carButtons[1].setPosition(BLACK_CAR_BUTTON_X, BLACK_CAR_BUTTON_Y);
  carButtons[2].setPosition(RED_CAR_BUTTON_X, RED_CAR_BUTTON_Y);
  carButtons[3].setPosition(WHITE_CAR_BUTTON_X, WHITE_CAR_BUTTON_Y);
  connectButton->setPosition(PLAY_BUTTON_X, PLAY_BUTTON_Y);
}

void Menu::set_buttons_as_leader() {

}

void Menu::load_media() {
    wallpaper.load_from_file("client/rendering/assets/all_images/Decor/background.png", gRenderer);

  auto callback_start_game = [&](const std::string &clickedId) {
        map_selected = "race_1";
        this->game_ready_cv->notify_all();
    };
    //car buttons
  auto callback = [&](const std::string &clickedId) {
        std::cout<<clickedId<<std::endl;
        for (auto &b : carButtons){
            if (b.id == clickedId){
                b.changeColor(255,255,255,-1);
                car_selected = b.id;
            } else {
                b.changeColor(80,80,80,-1);
            }
        }
    };

    carButtons.emplace_back("BLUE_CAR", gRenderer,
                            textureLoader.load_texture("cars/blue_car.png", gRenderer));
    carButtons.emplace_back("BLACK_CAR", gRenderer,
                            textureLoader.load_texture("cars/black_car.png", gRenderer));
    carButtons.emplace_back("RED_CAR", gRenderer,
                            textureLoader.load_texture("cars/red_car.png", gRenderer));
    carButtons.emplace_back("WHITE_CAR", gRenderer,
                            textureLoader.load_texture("cars/white_car.png", gRenderer));
    connectButton = std::make_shared<ConnectButton>(gRenderer,
                            textureLoader.load_texture("buttons/connect.png", gRenderer));
    connectButton->addCallbackFunction(callback_start_game);

  for (auto &button : carButtons) {
    button.addCallbackFunction(callback);
    button.changeColor(80, 80, 80, -1);
    }

    //map buttons
    mapButtons.emplace_back(gRenderer, textureLoader.load_texture("all_images/Decor/dragon.png", gRenderer));
    mapButtons.emplace_back(gRenderer, textureLoader.load_texture("all_images/Decor/dragon.png", gRenderer));
    mapButtons.emplace_back(gRenderer, textureLoader.load_texture("all_images/Decor/dragon.png", gRenderer));
    mapButtons[0].setPosition(MAP_BUTTON_1_X, MAP_BUTTON_1_Y);
    mapButtons[1].setPosition(MAP_BUTTON_2_X, MAP_BUTTON_2_Y);
    mapButtons[2].setPosition(MAP_BUTTON_3_X, MAP_BUTTON_3_Y);
}