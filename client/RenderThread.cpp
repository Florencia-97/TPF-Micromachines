

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
    menu.render();
    sleep(1/60);
}

void RenderThread::renderGame(int frame_id){
    InfoBlock inf;//get map state
    if (renderQueue->empty()){
        //if no states to load use last
        inf = previous_game_state;
    }else {
        while (!renderQueue->empty()){
            inf = renderQueue->front();
            renderQueue->pop();
            //get the very last event
        }
    }

    if (!inf.exists("game_end")) {
        gameRenderer.render(); //(inf); //TODO UPDATE STATE
        sleep(1/60); //todo variable time on sleep
    } else {
        state = -1;
        in_menu.store(true);
    }
}

void RenderThread::renderLobby(int frame_id) {
    InfoBlock inf("{game: started}", false);//get map state
    renderQueue->push(inf);
    if (!renderQueue->empty()){
        inf = renderQueue->front();
        renderQueue->pop();
        if (inf.exists("game")){
            previous_game_state = inf;
            state = GAME_STATE;

            //problem, how to iterate over yaml [0] = [car_name, x: 0, y: 0, r: 0, hp: 100]? etc?
            //maybe make it a subyaml TODO
            InfoBlock info("{map_name: race_1.yaml, my_car_id: 0, 0: dot.bmp}",false);
            gameRenderer.init(starter.get_global_renderer(), info);
        }
    }
    //lobby.render();
    sleep(1/60);
}

RenderThread::RenderThread(std::queue<InfoBlock>& rq) : starter(SCREEN_WIDTH, SCREEN_HEIGHT) {
    current_frame = 0;
    state = -1;
    in_menu.store(false);//todo start as true
    renderQueue = &rq;

    starter.init();
    //TODO BUSCAR button.png para descomentar TODO TODO TODO TODO TODO TODO TODO
    //menu.init(starter.get_global_renderer()); TODO FALTA PONER button.png para descomentar esta parte
    //una vez descomentado verificar con debug y un breakpoint si menu se inicializa bien (no quedan NULL)
    // yo despues organizo el thread para que .render() esto
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