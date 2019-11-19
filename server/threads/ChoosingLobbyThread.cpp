

#include "ChoosingLobbyThread.h"

ChoosingLobbyThread::ChoosingLobbyThread(std::list<GameThread> &games, Configuration &c, Socket &plrskt)
: plr(std::move(plrskt)) {
    this->configs = &c;
    this->games = &games;
}

bool ChoosingLobbyThread::_addPlayerToArena(Socket& client, InfoBlock& ib){
    auto it = this->games->begin();
    while (it != this->games->end()){
        if ((it)->isAlive() && (it)->gameName == ib.getString(ARENA_GAME)){
             if (!(it)->addPLayer(client, ib)) throw GameAlreadyStarted();;
             return true;
        }
        ++it;
    }
    return false;
}

void ChoosingLobbyThread::_run() {
    bool connected = false;
    while (!connected) {
        InfoBlock ib;
        if (!Protocol::recvMsg(&plr, ib)) {
            std::cout << "Error receiving msg\n";
            plr.closeSd();
            close();
            return;
        }
        std::string arenaName = ib.get<std::string>(ARENA_GAME);
        std::cout << arenaName << std::endl;

        // If players arena is not here, just go ahead and create one
        try {
            if (!_addPlayerToArena(plr, ib)) {
                this->games->emplace_back(plr, ib, *this->configs);
                this->games->back().run();
                connected = true;
            } else { connected = true; }
        } catch (GameAlreadyStarted& e){}
    }
    close();
}
