

#ifndef MICROMACHINES_GAMETHREAD_H
#define MICROMACHINES_GAMETHREAD_H

#include "../Game/GameWorld.h"
#include "../../common/Socket.h"
#include "../../common/BaseThread.h"
#include "PlayerThread.h"
#include <queue>
#include <vector>
#include <random>

class GameThread : public BaseThread {
    void _run() override;

    void _runLobby();

    void _runGame();

    //POS lobby_mode = false and game starts
    void startGame();

public:
    bool lobby_mode;
    int game_id;
    std::vector<PlayerThread> plr_threads;
    std::queue<Socket> player_connection_queue;

    GameWorld game;

    //POS spawns a Game in lobby_mode = true;
    //lobby owner can switch to lobby_mode = false by starting the game
    GameThread(int id, Socket &lobby_owner);

    //PRE lobby_mode must be true
    //POS adds player to the lobby
    void addPLayer(Socket &plr_socket);

};


#endif //MICROMACHINES_GAMETHREAD_H
