

#ifndef MICROMACHINES_RENDERTHREAD_H
#define MICROMACHINES_RENDERTHREAD_H

#include "../common/conc/BaseThread.h"
#include "../common/SafeQueue.h"
#include "../common/infostream/InfoBlock.h"
#include "rendering/interfaces/Menu.h"
#include "rendering/GameRenderer.h"
#include <SDL2/SDL.h>
#include <queue>
#include <atomic>

#define LOBBY_STATE 1
#define GAME_STATE 2
#define FPS 60

class RenderThread : public BaseThread {
    SDLStarter starter;
    int current_frame;
    int state; //thread state
    std::atomic<bool> in_menu;
    InfoBlock previous_game_state; //game state

    GameMap map;
    GameRenderer gameRenderer;
    Menu menu;

    void _run() override;

    void renderMenu(int frame_id);

    void renderGame(int frame_id);

    void renderLobby(int frame_id);

public:
    SafeQueue<InfoBlock>* renderQueue;

    explicit RenderThread(SafeQueue<InfoBlock>& rq );

    void proceedToLobby(bool is_leader);

    ~RenderThread();
};


#endif //MICROMACHINES_RENDERTHREAD_H
