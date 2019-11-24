

#ifndef MICROMACHINES_CHOOSINGLOBBYTHREAD_H
#define MICROMACHINES_CHOOSINGLOBBYTHREAD_H

#include "../../common/infostream/Socket.h"
#include "../../common/conc/BaseThread.h"
#include "threads/GameThread.h"
#include <config/Configuration.h>
#include "threads/PlayerThread.h"
#include "../../common/infostream/Protocol.h"
#include "../../config/constants.h"

class GameAlreadyStarted : public std::exception {
    virtual const char* what() const throw() {
        return "game already started\n";
    }
};

class ChoosingLobbyThread : public BaseThread {
    std::list<GameThread>* games;
    Configuration *configs;

    void _run() override;

    bool _addPlayerToArena(Socket &client, InfoBlock &ib);

public:
    Socket plr;

    ChoosingLobbyThread(std::list<GameThread>& games, Configuration &c, Socket& plr);
};


#endif //MICROMACHINES_CHOOSINGLOBBYTHREAD_H
