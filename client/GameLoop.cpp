

#include "GameLoop.h"

void GameLoop::_runProgram(){
    this->_checkVideoRecording();
    SDL_SetRenderTarget(starter.get_global_renderer(), NULL);
    SDL_RenderClear(starter.get_global_renderer());
    if (state == GAME_STATE) {
        runGame(frame_dif);
    } else if (!in_menu.load()) {
        runLobby(frame_dif);
    } else if (in_menu.load()){
        runMenu(frame_dif);
    }
    if (this->recording) {
        // TODO: THIS MUST CHANGE, how to render all window again without this?
        // the thing is that now it renders images over video texture
        // so, i must render things all over again
        SDL_RenderClear(starter.get_global_renderer());
        if (state == GAME_STATE) {
            runGame(frame_dif);
        } else if (!in_menu.load()) {
            runLobby(frame_dif);
        } else if (in_menu.load()){
            runMenu(frame_dif);
        }
    }
    SDL_RenderPresent(starter.get_global_renderer());
    soundSystem.play(state == GAME_STATE);
}

void GameLoop::_checkVideoRecording(){

}

void GameLoop::_run(){
    Stopwatch c;
    float timestep_goal = 1.0/FPS;
    float timesleep = timestep_goal;

    while (this->isAlive()) {
        _runProgram();
        this->sleep(timesleep);
        float t_elapsed = c.diff();
        timesleep = std::max(0.0f, timestep_goal - std::fmod(t_elapsed, timestep_goal));
        c.reset();
        frame_dif = std::ceil(t_elapsed/timestep_goal);
        this->current_frame = (current_frame+ frame_dif)%FPS;
    }
    close();
}

void GameLoop::runMenu(int frame_id) {
  menu.process_events_mouse();
  menu.process_events_keyboard();
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
	  menu.display_notification("Open   Games");
        state = -1;
        in_menu.store(true);
        client_ping->notify_all();
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
  menu.process_events_mouse();
  menu.process_events_keyboard();
    starter.get_screen_dimensions(&screenWidth, &screenHeight);
  if (leader) menu.render_as_leader(screenWidth, screenHeight);
  else menu.render_as_follower(screenWidth, screenHeight);

}

void GameLoop::proceedToLobby(bool is_leader) {
    SDL_StopTextInput();
    leader = is_leader;
  menu.start_lobby_buttons();
    if (is_leader){
	  menu.display_notification("Choose a map for the game");
    } else {
	  menu.display_notification("Waiting for the host  to  start  the game");
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
                   std::queue<InfoBlock>& fpq,
                   std::queue<std::string> &vq)
                   : starter(SCREEN_WIDTH,SCREEN_HEIGHT),
                     soundSystem(&sq), recording(false){
    current_frame = 0;
    frame_dif = 1;
    state = -1;
    in_menu.store(true);
    renderQueue = &rq;
    soundQueue = &sq;
    videoQueue = &vq;
    fakePlayerQueue = &fpq;
    starter.init();
    soundSystem.init();
    menu.init(starter.get_global_renderer(), &mouseQueue, &queue, &r, &sq);
  menu.set_main_menu_mode();
    client_ping = &r;
}
