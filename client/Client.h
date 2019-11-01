
#ifndef MICROMACHINES_CLIENT_H
#define MICROMACHINES_CLIENT_H

#include "communication/EventSender.h"
#include "communication/Receiver.h"
#include "communication/UserInput.h"
#include "rendering/TextureLoader.h"
#include "rendering/GameRenderer.h"
#include "GameMap.h"
#include "RenderThread.h"
#include "../config/constants.h"

class Client {
    Socket skt;
    SafeQueue<InfoBlock> keyboard_e_queue;
    SafeQueue<InfoBlock> mouse_e_queue;

    SafeQueue<InfoBlock> receiver_queue;
    SafeQueue<InfoBlock> sender_queue;

    //attemps to connect to client
    bool attempConnection();

    //true if connected, false if not
    bool connectionCheck();

    InfoBlock connection_state;

public:
    int play();
};


#endif //MICROMACHINES_CLIENT_H
