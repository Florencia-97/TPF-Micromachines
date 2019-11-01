#include "../../common/infostream/Protocol.h"
#include "../../config/constants.h"

#include "GameThread.h"

GameThread::GameThread(int id, Socket &lobby_owner, InfoBlock& ib)
: game_id(id), lobby_mode(true), sktOwner(std::move(lobby_owner)){
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
int GameThread::_runLobby() {
    InfoBlock firstIb = _createFirstCommunication(CONNECTED_TO_GAME_YES, OWNER_YES);
    Protocol::sendMsg(&this->sktOwner, firstIb);

    // Now i wait for the number of race
    InfoBlock ib;
    Protocol::recvMsg(&this->sktOwner, ib);
    int mapNumber = ib.get<int>(RACE_ID);
    // TODO : check if what was sended is okay! it should be because we control it
    return mapNumber;
}

void GameThread::_killPlayers(bool all){
    auto it = this->plr_threads.begin();
    while (it != this->plr_threads.end()){
        if (all || !(it)->isAlive() ){
            if ((it)->isAlive()) (it)->close();
            it = this->plr_threads.erase(it);
        } else {
            ++it;
        }
    }
}

void GameThread::addPLayer(Socket &plr_socket) {
    // Adds new players to the game
    InfoBlock ib;
    if (!this->lobby_mode){
        ib = _createFirstCommunication(CONNECTED_TO_GAME_NO, OWNER_NO);
    } else{
        this->plr_threads.emplace_back(plr_socket); //Not running yet!
        ib = _createFirstCommunication(CONNECTED_TO_GAME_YES, OWNER_NO);
    }
    Protocol::recvMsg(&plr_socket, ib);
}

void GameThread::_awakePlayersInLobby(){
    auto it = this->plr_threads.begin();
    while (it != this->plr_threads.end()) {
        // TODO: check if he is still connected, he could have left for good.
        (it)->run();
        ++it;
    }
}

void GameThread::_runGame() {
    this->_awakePlayersInLobby();
    std::cout << "Games activated\n";
    auto it = this->plr_threads.begin();
    while (this->isAlive()) {
        for (int i = 0 ; i < this->plr_threads.size(); i++){
            int j = rand() % plr_threads.size(); // Rand between 0 and size of plr_threads
            auto itj = std::next(plr_threads.begin(), j);
            if (!itj->eventQ.empty()){ // No race condition herem we are te only ones removing
                InfoBlock ib = itj->eventQ.front();
                itj->eventQ.pop();
                // TODO : process event in physic world
            }
        }
        // TODO : send the event.
        _killPlayers(false);
    }
}

void GameThread::_run() {

    // Lobby mode
    std::cout << "Running a new game!\n";
    int mapNumber = _runLobby();
    std::cout << "Race chosen: " << mapNumber << std::endl;
    // TODO load box2D world with the mapNumber given
    this->lobby_mode = false; // Atomic?
    this->plr_threads.emplace_front(this->sktOwner);

    // Not in lobby mode anymore !
    if (this->isAlive()) {
        std::cout << "Running race!\n";
        _runGame();
    }
    _killPlayers(true);
}

GameThread::~GameThread(){
    _killPlayers(true);
}
