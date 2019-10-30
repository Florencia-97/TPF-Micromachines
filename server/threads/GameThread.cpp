#include "../../common/infostream/Protocol.h"
#include "../../config/constants.h"

#include "GameThread.h"

GameThread::GameThread(int id, Socket &lobby_owner, InfoBlock& ib)
: game_id(id), lobby_mode(true), sktOwner(std::move(lobby_owner)){
}

int GameThread::_runLobby() {
    InfoBlock ib;
    Protocol::recvMsg(&this->sktOwner, ib);
    int mapNumber = ib.get<int>(NUMBER_RACE);
    // TODO : check if what was sended is okay!
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

void GameThread::startGame() {

}

void GameThread::addPLayer(Socket &plr_socket) {
    // Adds new players to the game
    InfoBlock ib;
    if (!this->lobby_mode){
        ib[CONNECTED_TO_GAME] = CONNECTED_TO_GAME_NO;
        return ;
    } else{
        this->plr_threads.emplace_back(plr_socket);
        this->plr_threads.back().run(); // should it run after the lobby is set?
        ib[CONNECTED_TO_GAME] = CONNECTED_TO_GAME_YES;
    }
    Protocol::recvMsg(&plr_socket, ib);
}

void GameThread::_runGame() {
    std::list<PlayerThread>::iterator it = this->plr_threads.begin();
    while (!this->isAlive()) {
        for (int i = 0 ; i < this->plr_threads.size(); i++){
            int j = rand() % plr_threads.size(); // Rand between 0 and size of plr_threads
            auto itj = std::next(plr_threads.begin(), j);
            InfoBlock ib = itj->eventQ.front();
            itj->eventQ.pop();
            // TODO : process event in physic world
        }
        // TODO : send the event.
        _killPlayers(false);
    }
}

void GameThread::_run() {

    // Lobby mode
    int mapNumber = _runLobby();
    // TODO load box2D world with the mapNumber given
    this->lobby_mode = false;
    this->plr_threads.emplace_front(this->sktOwner);
    this->plr_threads.front().run();

    // Not in lobby mode anymore !
    if (!this->isAlive()) {
        _runGame();
    }
    _killPlayers(true);
}

GameThread::~GameThread(){
    _killPlayers(true);
}
