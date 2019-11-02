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
    bool _addPlayerToArena(Socket& client, InfoBlock& ib);
    void _run() override;
public:
    explicit GamesManagerThread(std::string port);
    void close() override;
    ~GamesManagerThread();
};


#endif //MICROMACHINES_GAMESMANAGERTHREAD_H
