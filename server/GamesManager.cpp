#include "GamesManager.h"

GamesManager::GamesManager(std::string port){
    this->skt = Socket();
    this->skt.server(port);
}

void GamesManager::killGames(){
    auto it = this->games.begin();
    while (it != this->games.end()){
        if((*it)->isAlive() == false){
            //(*it)->stop();
            (*it)->join();
            delete(*it);
            it = this->games.erase(it);
        } else {
            ++it;
        }
    }
}


void GamesManager::creatGames(){
    // Accepts client
    // Creates a game that contains an id
    // Accepts 3 more clients and starts game.
    // TODO : n games and clients connect to the game id they want
    Socket client = this->skt.acceptClient();
    GameThread* game = new GameThread(1, client);
    for (int i = 0; i < 3; i++){
        Socket nPlayer = this->skt.acceptClient();
        game->addPLayer(nPlayer);
    }
    this->games.push_back(game);
    game->run();
    killGames();
}

GamesManager::~GamesManager(){}