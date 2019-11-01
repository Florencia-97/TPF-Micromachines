#include "GamesManagerThread.h"
#include "../../config/constants.h"

GamesManagerThread::GamesManagerThread(std::string port){
    this->skt = Socket();
    this->skt.server(port);
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
        if (!client.isValid()) break;
        std::cout  << "Client accepted\n";
        InfoBlock ib;
        if (!Protocol::recvMsg( &client, ib )){
            std::cout << "Error receiving msg\n";
            continue;
        }
        std::string arenaName = ib.get<std::string>(ARENA_GAME);
        std::cout << arenaName << std::endl;

        // If players arena is not here, just go ahead and create one
        if (!_addPlayerToArena(client, arenaName)){
            // TODO: is game id really necessary after having a game name
            std::cout << "Game created\n";
            GameThread* game = new GameThread(1, client, ib);
            game->gameName = arenaName;
            this->games.push_back(game);
            game->run();
        }
        _killGames(false);
    }
    _killGames(true);
    close();
}


void GamesManagerThread::close(){
    if (!this->isAlive()) return;
    skt.closeSd();
    BaseThread::close();
}

GamesManagerThread::~GamesManagerThread(){
    _killGames(true);
    this->close();
}