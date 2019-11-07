

#include "GameLoop.h"

void GameLoop::_run(){
    while (this->isAlive()) {
        if (state == GAME_STATE){
            runGame(current_frame);
        } else if (!in_menu.load()){ //if not in menu then in lobby
            runLobby(current_frame);
        } else if (in_menu.load()){
            runMenu(current_frame);
        }
        //todo check time and sleep
        this->current_frame = (current_frame+1) % FPS;
    }
}

void GameLoop::runMenu(int frame_id) {
  Button_answer answer(false, "");
  menu.processEventsMouse(answer);
  menu.processEventsKeyboard();

  if (answer.get_state() && start_game_name == "\n" && !exit) {// we are ready to try and connect!
        start_game_name = "race_1";
//        InfoBlock ib;
//        ib[CAR_TYPE] = name-of-the-car;
//        keyboard_e_queue.push(ib);
    //todo enviar answer.texture_name
    SDL_StopTextInput();
        ready_to_play->notify_all();
    }
    menu.render_first_menu();
    sleep(1/60);
}

void GameLoop::runGame(int frame_id){
    InfoBlock* gameState;
    if (renderQueue->empty()){
        //if no states to load use last
        gameState = &previous_game_state;
    }else {
        while (renderQueue->size()>1){
            renderQueue->pop();
            //get the very last event
        }
        gameState = &renderQueue->front();
    }

    if (!gameState->exists("game_end")) {
        gameRenderer.render(*gameState);
        sleep(1/60); //todo variable time on sleep
        previous_game_state = *gameState;
    } else {
        state = -1;
        in_menu.store(true);
    }
}

void GameLoop::runLobby(int frame_id) {

    if (!renderQueue->empty()){
        InfoBlock* gameState = &renderQueue->front();
        if (gameState->exists(RACE_ID)){
            auto ri = gameState->getString(RACE_ID);
            previous_game_state = *gameState;
            state = GAME_STATE;
            gameRenderer.init(starter.get_global_renderer(), *gameState);
        }
        renderQueue->pop();
    }
  menu.render_first_menu();//todo render lobby instead
    sleep(1/60);
}

void GameLoop::proceedToLobby(bool is_leader) {
    if (is_leader){
        //lobby.setLeadership(); //display map options
    }
    std::cout<<"im in lobby now"<<std::endl;
    in_menu.store(false);
}

GameLoop::~GameLoop(){
    starter.close();
}

GameLoop::GameLoop(std::queue<InfoBlock> &rq,
                   std::queue<SDL_Event> &queue,
                   std::queue<SDL_Event> &mouseQueue,
                   std::condition_variable &r) :
                            starter(SCREEN_WIDTH,SCREEN_HEIGHT) {
  current_frame = 0;
  state = -1;
  in_menu.store(true);
  renderQueue = &rq;
  starter.init();
  menu.init(starter.get_global_renderer(), &mouseQueue, &queue);
  exit = false;
  ready_to_play = &r;
  start_game_name = "\n";
}
