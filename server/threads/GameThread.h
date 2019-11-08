

#ifndef MICROMACHINES_GAMETHREAD_H
#define MICROMACHINES_GAMETHREAD_H

#include "../Game/GameWorld.h"
#include "../../common/infostream/Socket.h"
#include "../../common/conc/BaseThread.h"
#include "PlayerThread.h"
#include <string>
#include <queue>
#include <list>
#include <random>
#include <config/Configuration.h>
#include <mods/PluginLibrary.h>

class GameThread : public BaseThread {
    Socket sktOwner;
    InfoBlock ownerInfo;
    Configuration& configs;
    PluginLibrary pluginLibrary;
    void _run() override;
    void _killPlayers(bool all);
    std::string _runLobby();
    void _runGame();
    void _sendStartMsg(std::string raceId);
    void _sendAll(InfoBlock& ib);
    void _createCars();

    //POS returns true if there is at least 1 player still connected
    bool _anyPlayersAlive();

public:
    std::string gameName;
    bool lobby_mode;
    std::list<PlayerThread> plr_threads;

    GameWorld game;

    //POS spawns a Game in lobby_mode = true;
    //lobby owner can switch to lobby_mode = false by starting the game
    GameThread(Socket &lobby_owner, InfoBlock& ib, Configuration& configs);

    //PRE lobby_mode must be true
    //POS adds player to the lobby
    void addPLayer(Socket &plr_socket, InfoBlock& playerInfo);

    ~GameThread();
};


#endif //MICROMACHINES_GAMETHREAD_H
