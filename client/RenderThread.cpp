

#include "RenderThread.h"

void RenderThread::_run(){
    while (this->isAlive()) {
        if (state == GAME_STATE){
            renderGame(current_frame);
        } else if (!in_menu.load()){ //if not in menu then in lobby
            renderLobby(current_frame);
        } else if (in_menu.load()){
            renderMenu(current_frame);
        }
        //todo check time and sleep
        this->current_frame = (current_frame+1) % FPS;
    }
}

void RenderThread::renderMenu(int frame_id) {
  menu.render_first_menu();
    sleep(1/60);
  menu.init_as_leader();
  //menu.init_as_follower();
}

void RenderThread::renderGame(int frame_id){
    InfoBlock inf;
    if (renderQueue->isEmpty()){
        //if no states to load use last
        inf = previous_game_state;
    }else {
        while (!renderQueue->isEmpty()){
            inf = renderQueue->pop();
            //get the very last event
        }
    }

    if (!inf.exists("game_end")) {
        gameRenderer.render(inf); //TODO UPDATE STATE
        sleep(1/60); //todo variable time on sleep
    } else {
        state = -1;
        in_menu.store(true);
    }
}

void RenderThread::renderLobby(int frame_id) {

    if (!renderQueue->isEmpty()){
        auto inf = renderQueue->pop();
        if (inf.exists(RACE_ID)){
            auto ri = inf.getString(RACE_ID);
            previous_game_state = inf;
            state = GAME_STATE;
            auto a = inf.srcString();
            gameRenderer.init(starter.get_global_renderer(), inf);
        }
    }
  //lobby.render_first_menu();
    sleep(1/60);
}

RenderThread::RenderThread(SafeQueue<InfoBlock>& rq) : starter(SCREEN_WIDTH, SCREEN_HEIGHT) {
    current_frame = 0;
    state = -1;
    in_menu.store(true);
    renderQueue = &rq;

    starter.init();
    menu.init(starter.get_global_renderer());
}

void RenderThread::proceedToLobby(bool is_leader) {
    if (is_leader){
        //lobby.setLeadership(); //display map options
    }
    in_menu.store(false);
}

RenderThread::~RenderThread(){
    starter.close();
}