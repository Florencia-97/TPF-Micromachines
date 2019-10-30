

#ifndef MICROMACHINES_GAMETHREAD_H
#define MICROMACHINES_GAMETHREAD_H

#include "../Game/GameWorld.h"
#include "../../common/infostream/Socket.h"
#include "../../common/conc/BaseThread.h"
#include "PlayerThread.h"
#include <queue>
#include <list>
#include <random>

class GameThread : public BaseThread {
    void _run() override;
    void _killPlayers(bool all);
    int _runLobby();
    void _runGame();
    Socket sktOwner;
    void startGame();

public:
    std::string gameName;
    bool lobby_mode;
    int game_id;
    std::list<PlayerThread> plr_threads;

    GameWorld game;

    //POS spawns a Game in lobby_mode = true;
    //lobby owner can switch to lobby_mode = false by starting the game
    GameThread(int id, Socket &lobby_owner, InfoBlock& ib);

    //PRE lobby_mode must be true
    //POS adds player to the lobby
    void addPLayer(Socket &plr_socket);

    ~GameThread();

};


#endif //MICROMACHINES_GAMETHREAD_H
