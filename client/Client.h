
#ifndef MICROMACHINES_CLIENT_H
#define MICROMACHINES_CLIENT_H

#include "communication/EventSender.h"
#include "communication/Receiver.h"
#include "communication/UserInput.h"
#include "rendering/TextureLoader.h"
#include "rendering/GameRenderer.h"
#include "GameMap.h"
#include "GameLoop.h"
#include "../config/constants.h"

class serverNotRunning : public std::exception {
    virtual const char* what() const throw() {
        return "Server was disconnected, maybe try running it first!\n";
    }
};

class Client {
    //todo check passing of gRenderer
    Socket skt;
    SafeQueue<InfoBlock> keyboard_e_queue;
    std::queue<SDL_Event> mouse_queue;
    std::queue<SDL_Event> text_queue;
    std::queue<std::string> sound_queue;
    std::queue<InfoBlock> receiver_queue;
    std::queue<InfoBlock> fake_player_queue;
    std::condition_variable ready_to_connect;
    GameLoop gameLoop;
    UserInput userInput;
    Receiver receiver;
    EventSender sender;
    std::string port;
    std::string service;

    //attemps to connect to client
    bool attempConnection();

    //true if connected, false if not
    bool connectionCheck();

    InfoBlock connection_state;

public:
    Client(std::string& s, std::string& p);

    int play();

    void release();

    bool waitForConnection();

    void waitGameEnd();

    void waitReadyButton();

    void waitMapButton();

    bool connectToServer();
};


#endif //MICROMACHINES_CLIENT_H
