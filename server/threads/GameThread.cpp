#include "../../common/infostream/Protocol.h"
#include "../../config/constants.h"

#include "GameThread.h"

GameThread::GameThread(Socket &lobby_owner, InfoBlock& ib, Configuration& configs)
    : lobby_mode(true), sktOwner(std::move(lobby_owner)), gameName(ib.getString(ARENA_GAME)),
    configs(configs), pluginLibrary("plugins"){
    this->ownerInfo = ib;
}

bool GameThread::_anyPlayersAlive(){
   for (auto &p : this->plr_threads){
        if (p.isAlive()){
            return true;
        }
    }
    return false;
}

void GameThread::_killPlayers(bool all){
    auto it = this->plr_threads.begin();
    while (it != this->plr_threads.end()){
        if (all || (it)->isAlive()){
            if ((it)->isAlive()) {
                (it)->close();
            }
            it->join();
            it = this->plr_threads.erase(it);
        } else {
            ++it;
        }
    }
}

InfoBlock _createFirstCommunication(std::string connected, std::string owner){
    InfoBlock ib;
    ib[CONNECTED_TO_GAME] = connected;
    ib[OWNER] = owner;
    return ib;
}

/*
 * Lobby mode is for game owner!
 * We let him know he is the first!
*/
std::string GameThread::_runLobby() {
    InfoBlock firstIb = _createFirstCommunication(CONNECTED_TO_GAME_YES, OWNER_YES);
    if (!Protocol::sendMsg(&this->sktOwner, firstIb)){
        std::cout << "Error when sending status to player\n"<< HERE << std::endl;
        _killPlayers(true);
        close();
        return "";
    }

    InfoBlock ib;
    if (!Protocol::recvMsg(&this->sktOwner, ib) || !ib.exists(RACE_ID)){
        std::cout << "Error when receiving race id in: " << ib.srcString() << HERE << std::endl;
        _killPlayers(true);
        close();
        return "";
    }
    return ib.get<std::string>(RACE_ID);
}

void GameThread::addPLayer(Socket &plr_socket, InfoBlock& playerInfo) {
    // Adds a new player to the game while lobby is on
    InfoBlock ib;
    ib = _createFirstCommunication( lobby_mode? CONNECTED_TO_GAME_YES : CONNECTED_TO_GAME_NO , OWNER_NO);
    if ( Protocol::sendMsg(&plr_socket, ib) && lobby_mode ) {
        this->plr_threads.emplace_back(plr_socket, playerInfo);
        this->plr_threads.back().car_type = playerInfo.getString(CAR_TYPE);
        this->plr_threads.back().run();
    }
}

void GameThread::_createCars(){
    auto it = this->plr_threads.begin();
    while (it != this->plr_threads.end()){
        std::string carType = (!it->car_type.empty()) ? it->car_type : "RED_CAR";
        InfoBlock ib = this->configs.getDataFromCar(carType);
        this->game.createCar(ib);
        ++it;
    }
}

void GameThread::_sendAll(InfoBlock &ib) {
    auto it = this->plr_threads.begin();
    while (it != this->plr_threads.end()){
        (it)->sender.to_send.push(ib);
        ++it;
    }
}

void GameThread::_sendStartMsg(std::string raceId){
    int cont = 0;
    InfoBlock ib = this->game.status();
    ib[RACE_ID] = raceId;
    auto it = this->plr_threads.begin();
    while (it != this->plr_threads.end()){
        ib[MY_ID] = cont;
        it->id = cont;
        std::string carType = (!it->car_type.empty()) ? it->car_type : "RED_CAR";
        ib[CAR_TYPE + std::to_string(cont)] = carType;
        (it)->sender.to_send.getInternalQueue()->emplace(ib.srcString(),false);
        cont++;
        it++;
    }
}

void GameThread::_announceWinners() {
    std::list<int> plrs;
    for (auto &p : plr_threads){
        plrs.push_back(p.id);
    }

    plrs.sort([&](int &p1, int &p2){
        return (game.getCar(p1).getLaps() > game.getCar(p2).getLaps());
    });
    InfoBlock gameEndStatus;
    gameEndStatus[GAME_END] = 1;
    std::string suffix[3] = {"st","nd","rd"};
    short n = 0;
    for (auto &pid : plrs){
        std::string pos = std::to_string(n+1) + ((n > 2) ? "th" : suffix[n]);
        gameEndStatus["p"+std::to_string(pid)] = pos;
        n++;
    }
    _sendAll(gameEndStatus);
    this->sleep(5);
}


void GameThread::_processPlayerActions(){
    int j = rand()%plr_threads.size(); // Rand between 0 and size of plr_threads
    for (int i = 0 ; i < this->plr_threads.size(); i++){
        auto itj = std::next(plr_threads.begin(), j);
        if (!itj->eventQ.empty()){ // No race condition here we are te only ones removing
            InfoBlock event = itj->eventQ.front();
            itj->eventQ.pop();
            this->game.processEvent(j, event);
        }
        j = (++j)%plr_threads.size();
    }
}

void GameThread::_runGame() {
    Stopwatch c;
    float timestep_goal = 1.0/80;
    float timestep = timestep_goal;
    float time_left = GAME_DURATION_S;

    while (this->isAlive()) {
        _processPlayerActions();
        if (_anyPlayersAlive() && time_left > 0){

            this->game.Step(timestep_goal);
            auto gameStatus = this->game.status();
            gameStatus[TIME_LEFT] = (int)time_left;
            _sendAll(gameStatus);
            this->sleep(timestep);

        } else {
            if (time_left <= 0) _announceWinners();
            close();
        }
        auto time_elapsed = c.diff();
        c.reset();
        timestep = std::max(0.0f,timestep_goal- time_elapsed);
        time_left -= timestep_goal;
    }

    std::cout << "Game end" << std::endl;
}

void GameThread::_run() {
    std::cout << "Running a new game!\n";
    std::string mapName = _runLobby();
    if (this->isAlive()) {
        std::cout << "Race chosen is: " << mapName << std::endl;
        this->lobby_mode = false; // Atomic?
        this->plr_threads.emplace_front(this->sktOwner, this->ownerInfo);
        this->plr_threads.front().car_type = ownerInfo.getString(CAR_TYPE);
        this->plr_threads.front().run();
        // TODO: Clean queues: idea, send an event that breaks lobby mode?
        this->game.loadWorld(mapName);
        _createCars();
        _sendStartMsg(mapName);
        _runGame();
    }
    _killPlayers(true);
    close();
}

GameThread::~GameThread(){
    _killPlayers(true);
    close();
}
