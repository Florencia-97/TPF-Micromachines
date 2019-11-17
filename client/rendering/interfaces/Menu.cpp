#include <iostream>
#include "Menu.h"
#include "../../../config/constants.h"
#include "ConnectButton.h"
#include "TextLabel.h"

void Menu::init(SDL_Renderer *sdl_renderer, std::queue<SDL_Event> *gQueue, std::queue<SDL_Event> *textQueue,
                std::condition_variable *attempConnectionCV, std::queue<std::string> *sq) {
    this->text_queue = textQueue;
    this->mouse_queue = gQueue;
    this->sound_queue = sq;
    this->gRenderer = sdl_renderer;
    this->game_ready_cv = attempConnectionCV;
    map_selected = "\n";
    car_selected = "RED_CAR";
    ready = false;
    ai_on = false;
}

void Menu::displayNotification(std::string msg){
    notification.stageTextChange(msg);
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
    if (!open_games.empty()) return;
    SDL_Color gold{255, 189, 27, 0xFF};
    SDL_Color white{255, 255, 255, 0xFF};
    label_choose_car.init("CLICK A CAR TO SELECT", SCREEN_WIDTH / 2, 200, 28, gold, gRenderer);
    label_choose_car.init_intermitent_anim(FPS*2/3);
    textbox_lobby_name.init("START TYPING THE NAME OF YOUR SESSION", SCREEN_WIDTH / 2, 450, 30, gold, gRenderer);
    notification.init(" ", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 150, 35, white, gRenderer);
    flavor_text.init("fiuba 2019    all rights reserved",
                     SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30, 25, white, gRenderer);
    active_buttons = &carButtons;

    for (int i = 0; i<6; i++) {
        open_games.emplace_back();
        open_games.back().init(" ",
             450 + 400 * (i % 2), 580 + 75 * (int) (i / 2), 25, white, gRenderer);
    }


}

void Menu::_updateOpenGames(){
    if (!open_games_update.empty()){
        int size = open_games_update.front().get<int>("SIZE");
        int i = 0;
        for (auto &label : open_games){
            std::string text;
            if (i < size) {
                std::string key = "g"+std::to_string(i);
                text = open_games_update.front().getString(key);
            } else {
                text = "empty";
            }
            label.stageTextChange(std::to_string(i+1) + "          " + text);
            i++;
        }
        open_games_update.pop();
    }
}

bool Menu::processEventsMouse() {
    while (!mouse_queue->empty()) {
        auto event = &mouse_queue->front();
        if (event->type == SDL_QUIT) return true;
        for (auto &button : *active_buttons) {
            if (button.handleEvent(event, sound_queue)) {
                while (!mouse_queue->empty()) mouse_queue->pop();
                return false;
            }
        }
        if (connectButton->handleEvent(event, sound_queue)) {
            while (!mouse_queue->empty()) mouse_queue->pop();
            return false;
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

void Menu::render_first_menu(float screenWidth, float screenHeight) {
    wallpaper.render_with_size(0, 0, 0, gRenderer, SCREEN_HEIGHT, SCREEN_WIDTH, true);
    for (auto &button : carButtons) {
      button.render(screenWidth, screenHeight);
    }
    label_choose_car.render(screenWidth, screenHeight);
    textbox_lobby_name.render(screenWidth, screenHeight);
    flavor_text.render(screenWidth, screenHeight);
    notification.render(screenWidth, screenHeight);
    connectButton->render(screenWidth, screenHeight);

    _updateOpenGames();
    for (auto& label : open_games){
        label.render(screenWidth, screenHeight);
    }
}

void Menu::start_lobby() {
    active_buttons = &mapButtons;
}

void Menu::dummy_init_as_leader(int screenWidth, int screenHeight) {
    this->notification.stageTextChange("Choose your map");
    wallpaper.render_with_size(0, 0, 0, gRenderer, SCREEN_HEIGHT, SCREEN_WIDTH, true);
    for (auto &button : mapButtons) {
        button.render(screenWidth, screenHeight);
    }
    connectButton->render(screenWidth, screenHeight);
    notification.render(screenWidth, screenHeight);
}


void Menu::init_as_follower() {
    wallpaper.load_from_file("client/rendering/assets/all_images/Decor/waiting.png", gRenderer);
    wallpaper.render_with_size(0, 0, 0, gRenderer, 0, 0, true);
}

void Menu::set_buttons_positions() {
    carButtons[0].setPosition(BLUE_CAR_BUTTON_X, BLUE_CAR_BUTTON_Y);
    carButtons[1].setPosition(BLACK_CAR_BUTTON_X, BLACK_CAR_BUTTON_Y);
    carButtons[2].setPosition(RED_CAR_BUTTON_X, RED_CAR_BUTTON_Y);
    carButtons[3].setPosition(WHITE_CAR_BUTTON_X, WHITE_CAR_BUTTON_Y);
    connectButton->setPosition(PLAY_BUTTON_X, PLAY_BUTTON_Y);
}

void Menu::set_buttons_as_leader() {
    mapButtons.emplace_back("map_1",
                            gRenderer,
                            textureLoader.load_texture("all_images/Decor/dragon.png", gRenderer));
    mapButtons.emplace_back("map_2",
                            gRenderer,
                            textureLoader.load_texture("all_images/Decor/dragon.png", gRenderer));
    mapButtons.emplace_back("map_3",
                            gRenderer, textureLoader.load_texture("all_images/Decor/dragon.png", gRenderer));
    mapButtons.emplace_back("map_4",
                            gRenderer, textureLoader.load_texture("all_images/Decor/dragon.png", gRenderer));

    auto callbackMap = [&](const std::string &clickedId) {
      for (auto &button : mapButtons) {
          std::cout << clickedId<< button.id  << (button.id == clickedId) << std::endl;
          if (button.id == clickedId) {
              button.changeColor(255, 255, 255, -1);
              map_selected = button.id;
          } else {
              button.changeColor(80, 80, 80, -1);
          }
      }
    };
    for (auto &button : mapButtons) {
        button.addCallbackFunction(callbackMap);
        button.changeColor(80, 80, 80, -1);
        button.soundWhenPressed = SOUND_CAR_GEAR;
    }

    mapButtons[0].setPosition(BLUE_CAR_BUTTON_X, BLUE_CAR_BUTTON_Y);
    mapButtons[1].setPosition(BLACK_CAR_BUTTON_X, BLUE_CAR_BUTTON_Y);
    mapButtons[2].setPosition(WHITE_CAR_BUTTON_X, BLUE_CAR_BUTTON_Y);
    mapButtons[3].setPosition(RED_CAR_BUTTON_X, RED_CAR_BUTTON_Y);
}

void Menu::load_media() {
    wallpaper.load_from_file("client/rendering/assets/all_images/Decor/background.png", gRenderer);

    auto callback_start_game = [&](const std::string &clickedId) {
        map_selected = "race_1";
        ready = true;
        connectButton->changeColor(80, 80, 80, FPS*3);
        this->game_ready_cv->notify_all();
    };
    //car buttons
    auto callback = [&](const std::string &clickedId) {
        std::cout<<clickedId<<std::endl;
      for (auto &button : carButtons) {
          if (button.id == clickedId) {
              button.changeColor(255, 255, 255, -1);
              car_selected = button.id;
            } else {
              button.changeColor(80, 80, 80, -1);
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
        button.soundWhenPressed = SOUND_CAR_GEAR;
    }
    this->set_buttons_as_leader();

    auto ai_callback = [&](const std::string &clickedId) {
        ai_on = !ai_on;
        if (ai_on) {
            connectButton->changeColor(80, 80, 80, -1);
        } else {
            connectButton->changeColor(255, 255, 255, -1);
        }
    };
}
bool Menu::map_is_selected() {
    return this->mapIsSelected;
}
