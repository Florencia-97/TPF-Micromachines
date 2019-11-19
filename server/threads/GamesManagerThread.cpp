#include "GamesManagerThread.h"
#include "../../config/constants.h"

GamesManagerThread::GamesManagerThread(std::string port)
    : configs() {
    this->skt = Socket();
    this->skt.server(port);
}

void GamesManagerThread::_killThreads(bool all){
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

    auto it2 = this->choosing.begin();
    while (it2 != this->choosing.end()){
        if (all || !(it2)->isAlive()){
            if ((it2)->isAlive()) (it2)->close();
            (it2)->join();
            it2 = this->choosing.erase(it2);
        } else {
            ++it2;
        }
    }
}


bool GamesManagerThread::_sendOpenGames(Socket& client){
    InfoBlock games;
    std::list<std::string> openGames;
    for (auto &game : this->games){
        if (game.lobby_mode && game.isAlive()){
            openGames.push_back(game.gameName);
        }
    }
    games["SIZE"] = openGames.size();
    int cont = 0;
    for (auto &name : openGames){
        games["g"+std::to_string(cont)] = name;
        cont++;
    }
    return Protocol::sendMsg(&client, games);
}

void GamesManagerThread::_run(){
    while( this->isAlive() ){
        std::cout << "Waiting for a client\n";
        Socket client = this->skt.acceptClient();
        if (!this->skt.isValid()) break;
        std::cout  << "Client accepted\n";

        _sendOpenGames(client);
        choosing.emplace_back(games, configs, client);
        choosing.back().run();

        _killThreads(false);
    }
    _killThreads(true);
    close();
}


void GamesManagerThread::close(){
    if (!this->isAlive()) return;
    skt.closeSd();
    _killThreads(true);
    BaseThread::close();
}

GamesManagerThread::~GamesManagerThread(){
    _killThreads(true); // Should not go here
    this->close();
}