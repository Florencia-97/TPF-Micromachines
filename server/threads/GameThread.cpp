

#include "GameThread.h"



void GameThread::_run() {
    //_runLobby();

    if (!this->isClosed()) {
        //_runGame();
    }
}


GameThread::GameThread(int id, Socket &lobby_owner) {
    this->game_id = id;
    this->lobby_mode = true;

}


void GameThread::startGame() {

}

void GameThread::addPLayer(Socket &plr_socket) {
    this->player_connection_queue.emplace(std::move(plr_socket));
}

void GameThread::_runLobby() {
    while (!this->isClosed() && lobby_mode){
        while (!player_connection_queue.empty()){
            Socket player_socket = std::move(player_connection_queue.front());
            player_connection_queue.pop();
            if (player_socket.isValid()) {
                //plr_threads.emplace_back(std::move(player_socket))
            }
            //verify for disconnected sockets in player_vector
            //check_for_game_start
        }
    }
}

void GameThread::_runGame() {
    while (!this->isClosed()) {
        int size = plr_threads.size() - 1;
        int j = rand() % (size + 1 ); //rand between 0 and size
        for (int i=0; i< size; i++){
          //  if (!plr_threads[j].event_q.empty()){
                //get and process event from queue
          //      j = (j + 1)%size;
        //    }
        }
    }
}
