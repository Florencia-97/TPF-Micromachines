#include "GamesManagerThread.h"
#include "../../config/constants.h"

GamesManagerThread::GamesManagerThread(std::string port)
    : configs() {
    this->skt = Socket();
    this->skt.server(port);
}

void GamesManagerThread::_killGames(bool all){
    auto it = this->games.begin();
    while (it != this->games.end()){
        if (all || !(it)->isAlive()){
            if ((it)->isAlive()) (it)->close();
            (it)->join();
            it = this->games.erase(it);
        } else {
            ++it;
        }
    }
}

bool GamesManagerThread::_addPlayerToArena(Socket& client, InfoBlock& ib){
    auto it = this->games.begin();
    while (it != this->games.end()){
    if ((it)->isAlive() && (it)->gameName == ib.getString(ARENA_GAME)){
            (it)->addPLayer(client, ib);
            return true;
        }
        ++it;
    }
    return false;
}


void GamesManagerThread::_run(){
    while( this->isAlive() ){
        std::cout << "Waiting for a client\n";
        Socket client = this->skt.acceptClient();
        if (!this->skt.isValid()) break;
        std::cout  << "Client accepted\n";
        InfoBlock ib;
        if (!Protocol::recvMsg( &client, ib )){
            std::cout << "Error receiving msg\n";
            continue;
        }
        std::string arenaName = ib.get<std::string>(ARENA_GAME);
        std::cout << arenaName << std::endl;

        // If players arena is not here, just go ahead and create one
        if (!_addPlayerToArena(client, ib)){
            //todo leave it in the heap, or maybe not!
            this->games.emplace_back(client, ib, this->configs);
            this->games.back().run();
        }
        _killGames(false);
    }
    _killGames(true);
    close();
}


void GamesManagerThread::close(){
    if (!this->isAlive()) return;
    skt.closeSd();
    _killGames(true);
    BaseThread::close();
}

GamesManagerThread::~GamesManagerThread(){
    _killGames(true); // Should not go here
    this->close();
}