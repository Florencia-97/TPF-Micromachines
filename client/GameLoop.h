

#ifndef MICROMACHINES_GAMELOOP_H
#define MICROMACHINES_GAMELOOP_H

#include "../common/conc/BaseThread.h"
#include "../common/SafeQueue.h"
#include "../common/Stopwatch.h"
#include "../common/infostream/InfoBlock.h"
#include "rendering/interfaces/Menu.h"
#include "rendering/GameRenderer.h"
#include "sound_sys/SoundSystem.h"
#include <SDL2/SDL.h>
#include <queue>
#include <atomic>

#define LOBBY_STATE 1
#define GAME_STATE 2

class GameLoop : public BaseThread {
    SDLStarter starter;
    SoundSystem soundSystem;
    int current_frame;
    int state; //thread state
    std::atomic<bool> in_menu;
    InfoBlock previous_game_state;
    std::condition_variable* ready_to_play;
    GameMap map;
    GameRenderer gameRenderer;

    void _runProgram();

    void _run() override;

    void runMenu(int frame_id);

    void runGame(int frame_id);

    void runLobby(int frame_id);

public:
    Menu menu;

    std::condition_variable cv;
    bool exit;
    std::queue<InfoBlock>* renderQueue;
    std::queue<std::string>* soundQueue;

  GameLoop(std::queue<InfoBlock> &rq,
           std::queue<SDL_Event> &textQueue,
           std::queue<SDL_Event> &mouseQueue,
           std::condition_variable &ready,
           std::queue<std::string> &sq);

    void proceedToLobby(bool is_leader);

    ~GameLoop();
};


#endif //MICROMACHINES_GAMELOOP_H
