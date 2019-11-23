#ifndef MICROMACHINES_GAMESMANAGERTHREAD_H
#define MICROMACHINES_GAMESMANAGERTHREAD_H

#include <string>
#include <list>
#include <config/Configuration.h>
#include "../../common/infostream/Socket.h"
#include "threads/PlayerThread.h"
#include "threads/GameThread.h"
#include "ChoosingLobbyThread.h"

/*
 * Creats the socket of the server
 * Accepts  client and creates
 */

class GamesManagerThread : public BaseThread{
    Configuration configs;
    Socket skt; //Server's socket
    std::list<GameThread> games;
    std::list<ChoosingLobbyThread> choosing;
    void _killThreads(bool all);
    void _run() override;

public:
    explicit GamesManagerThread(std::string port);
    void close() override;

    bool _sendOpenGames(Socket &client);
};


#endif //MICROMACHINES_GAMESMANAGERTHREAD_H
