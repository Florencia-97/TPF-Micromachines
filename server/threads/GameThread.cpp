#include "../../common/infostream/Protocol.h"
#include "../../config/constants.h"

#include "GameThread.h"

GameThread::GameThread(Socket &lobby_owner, InfoBlock& ib)
    : lobby_mode(true), sktOwner(std::move(lobby_owner)),
    gameName(ib.getString(ARENA_GAME)) {
    this->ownerInfo = ib;
}

void GameThread::_killPlayers(bool all){
    auto it = this->plr_threads.begin();
    while (it != this->plr_threads.end()){
        if (all || !(it)->isAlive()){
            if ((it)->isAlive()) (it)->close();
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
int GameThread::_runLobby() {
    InfoBlock firstIb = _createFirstCommunication(CONNECTED_TO_GAME_YES, OWNER_YES);
    if (!Protocol::sendMsg(&this->sktOwner, firstIb)){
        std::cout << "Error when sending status to player\n";
        _killPlayers(true);
        close();
    }
    // Now i wait for the id of the race
    InfoBlock ib;
    if (!Protocol::recvMsg(&this->sktOwner, ib)){
        std::cout << "Error when receiving race id\n";
        _killPlayers(true);
        close();
    }
    return ib.get<int>(RACE_ID);
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

void GameThread::_sendAll(InfoBlock ib) {
    auto it = this->plr_threads.begin();
    while (it != this->plr_threads.end()){
        (it)->sender.to_send.push(ib); // Shoudn't check if client is alive here
    }
}

void GameThread::_runGame() {
    auto it = this->plr_threads.begin();
    while (this->isAlive()) {
        for (int i = 0 ; i < this->plr_threads.size(); i++){
            int j = rand() % plr_threads.size(); // Rand between 0 and size of plr_threads
            auto itj = std::next(plr_threads.begin(), j);
            if (!itj->eventQ.empty()){ // No race condition here we are te only ones removing
                InfoBlock ib = itj->eventQ.front();
                itj->eventQ.pop();
                std::cout << ib.srcString() << std::endl;
                // TODO : process event in physic world
            }
        }
        _killPlayers(false);
        // TODO: create a real infoblock with the new world
//        This is just an example!
//        InfoBlock worldActualization = Box2d.sumUp();
//        _sendAll(worldActualization);
    }
    // TODO: when putting q in server its not leaving here (Flor fixs it)
    std::cout << "Leaving here auch" << std::endl;
}

void GameThread::_run() {
    std::cout << "Running a new game!\n";
    int mapNumber = _runLobby();
    std::cout << "Race chosen is: " << mapNumber << std::endl;
    // TODO load box2D world with the mapNumber given
    this->lobby_mode = false; // Atomic?
    this->plr_threads.emplace_front(this->sktOwner, this->ownerInfo);
    this->plr_threads.front().run();
    std::cout << "Running!\n";
    // Not in lobby mode anymore !
    if (this->isAlive()) {
        _runGame();
    }
    _killPlayers(true);
}

GameThread::~GameThread(){
    _killPlayers(true);
    close();
}
