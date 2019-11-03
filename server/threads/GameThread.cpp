#include "../../common/infostream/Protocol.h"
#include "../../config/constants.h"

#include "GameThread.h"

GameThread::GameThread(Socket &lobby_owner, InfoBlock& ib, Configuration& configs)
    : lobby_mode(true), sktOwner(std::move(lobby_owner)), gameName(ib.getString(ARENA_GAME)) {
    this->ownerInfo = ib;
    this->configs = configs;
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
        if (all || !(it)->isAlive()){
            if ((it)->isAlive()) (it)->close();
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
        std::cout << "Error when sending status to player\n"<< HERE;
        _killPlayers(true);
        close();
        return "";
    }
    // Now i wait for the id of the race
    InfoBlock ib;
    if (!Protocol::recvMsg(&this->sktOwner, ib) ||
        !ib.exists(RACE_ID)){
        std::cout << "Error when receiving race id\n"<< HERE;
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
        this->plr_threads.back().run();
    }
}

void GameThread::_createCars(){
    auto it = this->plr_threads.begin();
    while (it != this->plr_threads.end()){
//        std::string carType = it->car_type;
        std::string carType = "BLUE_CAR"; // Here goes the real player choice
        InfoBlock ib = this->configs.getDataFromCar(carType);
        this->game.createCar(ib);
        ++it;
    }
}

void GameThread::_sendAll(InfoBlock& ib) {
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
        (it)->sender.to_send.push(ib);
        cont++;
        it++;
    }
    auto i = ib.srcString();
    int b=1;
}

void GameThread::_runGame() {
    auto it = this->plr_threads.begin();
    while (this->isAlive()) {

        int j = rand() % plr_threads.size(); // Rand between 0 and size of plr_threads
        for (int i = 0 ; i < this->plr_threads.size(); i++){
            auto itj = std::next(plr_threads.begin(), j);
            if (!itj->eventQ.empty()){ // No race condition here we are te only ones removing
                InfoBlock event = itj->eventQ.front();
                itj->eventQ.pop();
                this->game.processEvent(event);
            }
            j = (++j)%plr_threads.size();
        }

        if (_anyPlayersAlive()){
            this->game.Step(1/80.0);
            InfoBlock worldActualization = this->game.status();
            auto a = worldActualization.srcString();
            _sendAll(worldActualization);
            sleep(1);//todo remove
        } else {
            close();
        }
    }
    std::cout << "Leaving game" << std::endl;
}

void GameThread::_run() {
    std::cout << "Running a new game!\n";
    std::string mapName = _runLobby();
    if (this->isAlive()) {
        std::cout << "Race chosen is: " << mapName << std::endl;
        this->lobby_mode = false; // Atomic?
        this->plr_threads.emplace_front(this->sktOwner, this->ownerInfo);
        this->plr_threads.front().run();
        // TODO: Clean queues
        _createCars();
        this->game.loadWorld(mapName);
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
