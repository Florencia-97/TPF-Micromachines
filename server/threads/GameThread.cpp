#include "../../common/infostream/Protocol.h"
#include "../../config/constants.h"

#include "GameThread.h"

GameThread::GameThread(int id, Socket &lobby_owner, InfoBlock& ib)
: game_id(id), lobby_mode(true), sktOwner(std::move(lobby_owner)){
}

void GameThread::_killPlayers(bool all){
    try{
        auto it = this->plr_threads.begin();
        while (it != this->plr_threads.end()){
            if (all || !(it)->isAlive() ){
                if ((it)->isAlive()) (it)->close();
                it = this->plr_threads.erase(it);
            } else {
                ++it;
            }
        }
    } catch(...){
        std::cout << "Something is going wrong here\n";
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
    Protocol::sendMsg(&this->sktOwner, firstIb);

    // Now i wait for the number of race
    InfoBlock ib;
    if (!Protocol::recvMsg(&this->sktOwner, ib)){
        std::cout << "Error when receiving race id\n";
        _killPlayers(true);
        close();
    }
    int mapNumber = ib.get<int>(RACE_ID);
    // TODO : check if what was sended is okay! it should be because we control it
    return mapNumber;
}

void GameThread::addPLayer(Socket &plr_socket) {
    // Adds new players to the game
    InfoBlock ib;
    //Refactor, this can be done a bit shorter i think
    ib = _createFirstCommunication( lobby_mode? CONNECTED_TO_GAME_YES : CONNECTED_TO_GAME_NO , OWNER_NO);
    std::cout << "Sending first msg to a new client\n";
    //Protocol::sendMsg(&plr_socket, ib);
    if ( Protocol::sendMsg(&plr_socket, ib) && lobby_mode ) {
        //Race condition?
        this->plr_threads.emplace_back(plr_socket);
        this->plr_threads.back().run();
    }
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
    //this->_awakePlayersInLobby();
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
        _runGame();
    }
    _killPlayers(true);
}

GameThread::~GameThread(){
    _killPlayers(true);
    close();
}
