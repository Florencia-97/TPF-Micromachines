#include <iostream>
#include "Menu.h"
#include "../../../config/constants.h"
#include "CarButton.h"
#include "ConnectButton.h"
#include "MapButton.h"
#include "TextLabel.h"

void Menu::init(SDL_Renderer *sdl_renderer, std::queue<SDL_Event> *gQueue, std::queue<SDL_Event> *textQueue) {
    this->text_queue = textQueue;
    this->mouse_queue = gQueue;
    this->gRenderer = sdl_renderer;
}

void Menu::setMainMenuMode(){
    try {
        if (!carButtons.empty()) return;;
        load_media();
        set_buttons_positions();
    } catch(...) {
        throw std::runtime_error("Failed to initialize textures!\n");
    }
    SDL_Color gold{255, 189, 27, 0xFF};
    label_choose_car.init("CLICK A CAR TO SELECT", SCREEN_WIDTH, 200, gold, gRenderer);
    textbox_lobby_name.init("START TYPING THE NAME OF YOUR SESSION", SCREEN_WIDTH, 450, gold, gRenderer);
    active_buttons = &carButtons;
}

bool Menu::processEventsMouse(ButtonAnswer &button_answer) {
  while (!mouse_queue->empty()) {
        for (auto &button : *active_buttons) {
          button.handleEvent(&mouse_queue->front(), &button_answer);
          if (button_answer.get_clicked()) {
            while (!mouse_queue->empty()) mouse_queue->pop();
            return button_answer.get_clicked();
            }
        }
        connectButton->handleEvent(&mouse_queue->front(), &button_answer);
    mouse_queue->pop();
    }
  return button_answer.get_clicked();
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
    connectButton->render();
    SDL_RenderPresent(gRenderer);
}

void Menu::dummy_init_as_leader() {//todo fix
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
  LTexture map1;
  LTexture map2;
  LTexture map3;
  map1.load_from_file("client/rendering/assets/all_images/Decor/dragon.png", gRenderer);
  map2.load_from_file("client/rendering/assets/all_images/Decor/dragon.png", gRenderer);
  map3.load_from_file("client/rendering/assets/all_images/Decor/dragon.png", gRenderer);
  mapButtons.emplace_back(gRenderer, &map1);
  mapButtons.emplace_back(gRenderer, &map2);
  mapButtons.emplace_back(gRenderer, &map3);
  mapButtons[0].setPosition(MAP_BUTTON_1_X, MAP_BUTTON_1_Y);
  mapButtons[1].setPosition(MAP_BUTTON_2_X, MAP_BUTTON_2_Y);
  mapButtons[2].setPosition(MAP_BUTTON_3_X, MAP_BUTTON_3_Y);
}

void Menu::load_media() {
    wallpaper.load_from_file("client/rendering/assets/all_images/Decor/background.png", gRenderer);

    //car buttons
    auto callback = [&](std::string clickedId){
        for (auto &b : carButtons){
            if (b.id == clickedId){
                b.changeColor(255,255,255,-1);
            } else {
                b.changeColor(80,80,80,-1);
            }
        }
    };
    carButtons.emplace_back(gRenderer,
                            textureLoader.load_texture("cars/blue_car.png", gRenderer));
    carButtons.emplace_back(gRenderer,
                            textureLoader.load_texture("cars/black_car.png", gRenderer));
    carButtons.emplace_back(gRenderer,
                            textureLoader.load_texture("cars/red_car.png", gRenderer));
    carButtons.emplace_back(gRenderer,
                            textureLoader.load_texture("cars/white_car.png", gRenderer));
    connectButton = std::make_shared<ConnectButton>(gRenderer,
                            textureLoader.load_texture("buttons/connect.png", gRenderer));
    for (auto &b : carButtons){
        b.addCallbackFunction(callback);
        b.changeColor(80,80,80,-1);
    }
}