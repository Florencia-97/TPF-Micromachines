
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
    Socket skt;
    SafeQueue<InfoBlock> keyboard_e_queue;
    SafeQueue<InfoBlock> mouse_e_queue;
  std::queue<SDL_Event> mouse_queue;
    std::queue<SDL_Event> text_queue;
    std::queue<InfoBlock> receiver_queue;
    std::condition_variable ready_to_connect;
    GameLoop gameLoop;
    UserInput userInput;
    Receiver receiver;
    EventSender sender;


    //attemps to connect to client
    bool attempConnection();

    //true if connected, false if not
    bool connectionCheck();

    InfoBlock connection_state;

public:
    Client();

    int play();

    void release();

    bool waitForConnection();
};


#endif //MICROMACHINES_CLIENT_H
