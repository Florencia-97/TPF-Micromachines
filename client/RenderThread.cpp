

#include "RenderThread.h"

void RenderThread::_run(){
    while (this->isAlive()){
        renderGame(current_frame);
        this->current_frame = (current_frame+1) % frames_per_second;
    }//TODO REMOVE

    while (this->isAlive()) {
        if (state == GAME_STATE){
            renderGame(current_frame);
        } else if (!in_menu.load()){ //if not in menu then in lobby
            renderLobby(current_frame);
        } else if (in_menu.load()){
            renderMenu(current_frame);
        }
        //todo check time and sleep
        this->current_frame = (current_frame+1) % frames_per_second;
    }
}

void RenderThread::renderMenu(int frame_id) {
    //menu.updateButtons();
    //std::string buttonClicked = menu.checkButtons();
    //menu.render();
    sleep(1/60);
}

void RenderThread::renderGame(int frame_id){
    InfoBlock inf;//get map state
    if (renderQueue->empty()){
        //if no states to load use last
        inf = previous_state;
    }else {
        while (!renderQueue->empty()){
            inf = renderQueue->front();
            renderQueue->pop();
            //get the very last event
        }
    }

    if (!inf.exists("game_end")) {
        gameRenderer->render(); //(inf); //TODO UPDATE STATE
        sleep(1/60); //todo variable time on sleep
    } else {
        state = -1;
        in_menu.store(true);
    }
}

void RenderThread::renderLobby(int frame_id) {
    InfoBlock inf;//get map state
    if (!renderQueue->empty()){
        inf = renderQueue->front();
        renderQueue->pop();
        if (inf.exists("game")){
            previous_state = inf;
            state = GAME_STATE;
        }
    }
    //TODO menu.render(frame_id);
    sleep(1/60);
}

RenderThread::RenderThread(GameRenderer &gr, std::queue<InfoBlock>& rq) {
    current_frame = 0;
    frames_per_second = 60;
    gameRenderer = &gr;
    state = -1;
    in_menu.store(true);
    renderQueue = &rq;
}

void RenderThread::proceedToLobby(bool is_leader) {
    if (is_leader){
        //lobby.setLeadership(); //display map options
    }
    in_menu.store(false);
}
