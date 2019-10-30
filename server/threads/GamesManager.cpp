#include "GamesManager.h"
#include "../../common/infostream/Protocol.h"
#include "../../config/constants.h"

GamesManager::GamesManager(std::string port){
    this->skt = Socket();
    this->skt.server(port);
}

void GamesManager::_killGames(bool all){
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

bool GamesManager::_addPlayerToArena(Socket& client, std::string arenaName){
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


void GamesManager::_run(){
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

GamesManager::~GamesManager(){
    _killGames(true);
}