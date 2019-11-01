#ifndef MICROMACHINES_GAMESMANAGERTHREAD_H
#define MICROMACHINES_GAMESMANAGERTHREAD_H

#include <string>
#include <list>
#include "../../common/infostream/Socket.h"
#include "threads/PlayerThread.h"
#include "threads/GameThread.h"

/*
 * Creats the socket of the server
 * Accepts  client and creates
 */

class GamesManagerThread : public BaseThread{
    Socket skt; //Server's socket
    std::list<GameThread*> games;
    void _killGames(bool all);
    bool _addPlayerToArena(Socket& client, std::string arenaName);
    void _run() override;
public:
    GamesManagerThread(std::string port);
    void creatGames();
    void close() override;
    ~GamesManagerThread();
};


#endif //MICROMACHINES_GAMESMANAGERTHREAD_H
