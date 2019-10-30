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

class GamesManager : public BaseThread{
    Socket skt; //Server's socket
    std::list<GameThread*> games;
    void _killGames(bool all);
    bool _addPlayerToArena(Socket& client, std::string arenaName);
public:
    GamesManager(std::string port);
    virtual void _run() override;
    void creatGames();
    ~GamesManager();
};


#endif //MICROMACHINES_GAMESMANAGER_H
