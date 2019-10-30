

#ifndef MICROMACHINES_RENDERTHREAD_H
#define MICROMACHINES_RENDERTHREAD_H

#include "../common/conc/BaseThread.h"
#include "../common/SafeQueue.h"
#include "../common/infostream/InfoBlock.h"
#include "rendering/GameRenderer.h"
#include <SDL2/SDL.h>
#include <queue>
#include <atomic>

#define LOBBY_STATE 1
#define GAME_STATE 2

class RenderThread : public BaseThread {
    int current_frame;
    int frames_per_second;
    int state;
    std::atomic<bool> in_menu;
    InfoBlock previous_state;

    void _run() override;

    void renderMenu(int frame_id);

    void renderGame(int frame_id);

    void renderLobby(int frame_id);

    GameRenderer* gameRenderer;

public:
    std::queue<InfoBlock>* renderQueue;

    explicit RenderThread(GameRenderer &gr, std::queue<InfoBlock>& rq );

    void proceedToLobby(bool is_leader);
};


#endif //MICROMACHINES_RENDERTHREAD_H
