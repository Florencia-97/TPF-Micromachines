#include "GamesManagerThread.h"
#include "../../common/infostream/Protocol.h"
#include "../../config/constants.h"

GamesManagerThread::GamesManagerThread(std::string port){
    this->skt = Socket();
    this->skt.server(port);
    std::cout << "Server's socket now working!\n";
}

void GamesManagerThread::_killGames(bool all){
    auto it = this->games.begin();
    while (it != this->games.end()){
        if (all || !(*it)->isAlive() ){
            if ((*it)->isAlive()) (*it)->close();
            (*it)->join();
            delete(*it);
            it = this->games.erase(it);
        } else {
            ++it;
        }
    }
}

bool GamesManagerThread::_addPlayerToArena(Socket& client, std::string arenaName){
    auto it = this->games.begin();
    while (it != this->games.end()){
        if(!(*it)->isAlive()) continue;
        if ((*it)->gameName == arenaName){
            (*it)->addPLayer(client);
            return true;
        }
        ++it;
    }
    return false;
}


void GamesManagerThread::_run(){
    while( this->isAlive() ){
        Socket client = this->skt.acceptClient();
        InfoBlock ib;
        if (!Protocol::recvMsg( &skt, ib )){
            continue;
        }
        std::string arenaName = ib.get<std::string>(ARENA_GAME);

        // If players arena is not here, just go ahead and create one
        if (!_addPlayerToArena(client, arenaName)){
            // TODO: is game id really neccesary after having a game name
            GameThread* game = new GameThread(1, client, ib);
            this->games.push_back(game);
            game->run();
        }
        _killGames(false);
    }
    _killGames(true);
}


void GamesManagerThread::close(){
    if (!this->isAlive()) return;
    skt.closeSd();
    // This closes atomic alive ! Needed if i want to redifine close of base thread
    BaseThread::close();
}

GamesManagerThread::~GamesManagerThread(){
    this->close();
    _killGames(true);
}