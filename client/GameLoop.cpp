

#include "GameLoop.h"

void GameLoop::_runProgram(){
    SDL_RenderClear(starter.get_global_renderer());
    if (state == GAME_STATE) {
      runGame(current_frame);
    } else if (!in_menu.load()) {
        runLobby(current_frame);
    } else if (in_menu.load()){
        runMenu(current_frame);
    }
    soundSystem.play(state == GAME_STATE);
    SDL_RenderPresent(starter.get_global_renderer());
    //videoRecorder.record(starter.get_global_renderer());
}

void GameLoop::_run(){
    Stopwatch c;
    float timestep_goal = 1.0/FPS;
    float timestep = timestep_goal;

    while (this->isAlive()) {
        _runProgram();
        this->sleep(timestep);
        float t_elapsed = c.diff();
        timestep = std::max(0.0f,timestep_goal - t_elapsed);
        c.reset();
        this->current_frame = (current_frame+ std::max(1,(int)(FPS*t_elapsed))) % FPS;
    }
    close();
}

void GameLoop::runMenu(int frame_id) {
    menu.processEventsMouse();
    menu.processEventsKeyboard();
    starter.get_screen_dimensions(&screenWidth, &screenHeight);
    menu.render_first_menu(screenWidth, screenHeight);
}

void GameLoop::runGame(int frame_id){
    InfoBlock* gameState;
    if (renderQueue->empty()){
        //if no states to load use last
        gameState = &previous_game_state;
    } else {
        while (renderQueue->size()>1){
            renderQueue->pop();
            //get the very last event
        }
        if (renderQueue->front().exists(RACE_RESULTS)){
            gameState = &previous_game_state;
            gameRenderer.initLeaderboard(renderQueue->front());
        } else gameState = &renderQueue->front();
    }

    if (!gameState->exists(GAME_END)) {
        int height;
        int width;
        //fakePlayerQueue->push(*gameState);
        starter.get_screen_dimensions(&width, &height);
        gameRenderer.render(*gameState, frame_id, width, height);
        previous_game_state = *gameState;

    } else {
        menu.displayNotification("Open   Games");
        state = -1;
        in_menu.store(true);
        ready_to_play->notify_all();
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
    menu.processEventsMouse();
    menu.processEventsKeyboard();
    starter.get_screen_dimensions(&screenWidth, &screenHeight);
    if (leader) menu.renderAsLeader(screenWidth, screenHeight);
    else menu.renderAsFollower(screenWidth, screenHeight);

}

void GameLoop::proceedToLobby(bool is_leader) {
    SDL_StopTextInput();
    leader = is_leader;
    if (is_leader){
        menu.start_lobby();
        menu.displayNotification("Choose a map for the game");
    } else {
        menu.displayNotification("Waiting for the host to start the game");
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
                   std::condition_variable &r,
                   std::queue<std::string> &sq,
                   std::queue<InfoBlock>& fpq)
                   : starter(SCREEN_WIDTH,SCREEN_HEIGHT),
                     soundSystem(&sq){
    current_frame = 0;
    state = -1;
    in_menu.store(true);
    renderQueue = &rq;
    soundQueue = &sq;
    fakePlayerQueue = &fpq;
    starter.init();
    soundSystem.init();
    menu.init(starter.get_global_renderer(), &mouseQueue, &queue, &r, &sq);
    menu.setMainMenuMode();
    ready_to_play = &r;
    //videoRecorder.init(starter.get_global_renderer());
}
