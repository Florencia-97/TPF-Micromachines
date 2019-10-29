#ifndef MICROMACHINES_GAMESMANAGER_H
#define MICROMACHINES_GAMESMANAGER_H

#include <string>
#include <list>
#include "../../common/infostream/Socket.h"
#include "threads/PlayerThread.h"
#include "threads/GameThread.h"

/*
 * Creats the socket of the server
 * Accepts  client and creates
 */

class GamesManager {
    Socket skt; //Server's socket
    std::list<GameThread*> games;
    void killGames();
public:
    GamesManager(std::string port);
    void creatGames();
    ~GamesManager();
};


#endif //MICROMACHINES_GAMESMANAGER_H
