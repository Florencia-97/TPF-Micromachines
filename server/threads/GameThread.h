

#ifndef MICROMACHINES_GAMETHREAD_H
#define MICROMACHINES_GAMETHREAD_H

#include "../Game/GameWorld.h"
#include "../../common/infostream/Socket.h"
#include "../../common/conc/BaseThread.h"
#include "../../common/Stopwatch.h"
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
    PluginLibrary* pluginLibrary;
    std::string _runLobby();

    // Override BaseThread class
    void _run() override;

    // Removes all player from game
    // if all is false, it removes only the ones that are dead
    void _killPlayers(bool all);

    // Runs game with the players that are in at moment given
    void _runGame();

    // Send first msg of game to player
    // Including race, id and car type
    void _sendStartMsg(std::string raceId);

    // Sends the given infoBlock to all players
    void _sendAll(InfoBlock &ib);

    //Creates a car for every player in the box2d world
    void _createCars();

    //POS returns true if there is at least 1 player still connected
    bool _anyPlayersAlive();

    // Removes event from every player queue. It does it in a random way,
    // so the game is fair
    void _processPlayerActions();

    // Send position table to all the players that remain in game
    void _announceWinners();

    // Loads infoBlock with the position of players in race
    void _loadWinners(InfoBlock &b);

public:
    std::string gameName;
    bool lobby_mode;
    std::list<PlayerThread> plr_threads;
    GameWorld game;

    //POS spawns a Game in lobby_mode = true;
    //lobby owner can switch to lobby_mode = false by starting the game
    GameThread(Socket &lobby_owner, InfoBlock& ib, Configuration& configs);

    //PRE lobby_mode must be true
    // Adds a new player to the game while lobby is on
    //POS adds player to the lobby
    bool addPLayer(Socket &plr_socket, InfoBlock& playerInfo);

    ~GameThread();
};


#endif //MICROMACHINES_GAMETHREAD_H
