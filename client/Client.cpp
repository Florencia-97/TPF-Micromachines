
#include "Client.h"
#include "../common/infostream/Protocol.h"

bool Client::connectionCheck(){
    return (connection_state.exists(CONNECTED_TO_GAME) &&
            connection_state.getString(CONNECTED_TO_GAME) == CONNECTED_TO_GAME_YES);
}


bool Client::attempConnection() {
    skt.client(SERVICE, PORT);
    if (!skt.isValid()) throw  serverNotRunning();
    connection_state[ARENA_GAME] = gameLoop.menu.map_selected;
    connection_state[CAR_TYPE] = gameLoop.menu.car_selected;
    if (!Protocol::sendMsg(&skt, connection_state)) throw  serverNotRunning();
    if (!Protocol::recvMsg(&skt, connection_state)) throw  serverNotRunning();
    return connectionCheck();
}

bool Client::waitForConnection(){
    bool connection_successful = false;
    while (!gameLoop.exit && !connection_successful) {
        gameLoop.menu.map_selected = "\n";
        std::mutex m;
        std::unique_lock<std::mutex> l(m);
        while (gameLoop.menu.map_selected == "\n" && !gameLoop.exit) {
            ready_to_connect.wait(l);
        }
        connection_successful = attempConnection();
    }
}

int Client::play() {
    gameLoop.run();
    userInput.run();

    try {
        waitForConnection();
    } catch (const std::exception& e){
        std::cout << e.what() << std::endl;
        release();
        return 1;
    }
    bool is_leader = connection_state.getString(OWNER) == OWNER_YES;
    gameLoop.proceedToLobby(is_leader);

    if (skt.isValid() && gameLoop.menu.map_selected != "\n" && !gameLoop.exit) {
        if (is_leader) {
            sleep(5);
            InfoBlock ib;
            ib[RACE_ID] = gameLoop.menu.map_selected;
            keyboard_e_queue.push(ib);
        }

        if (!receiver.isRunning()) {
            receiver.run();
            sender.run();
        }
        
      sleep(500);
    }

    release();
    return 0;
}

Client::Client() : gameLoop(this->receiver_queue, text_queue, mouse_queue, ready_to_connect, sound_queue),
                   userInput(&keyboard_e_queue, &mouse_e_queue, &mouse_queue, &text_queue, &sound_queue),
                   receiver(skt, &receiver_queue), sender(skt, &keyboard_e_queue)
{}

void Client::release(){
    skt.closeSd();
    userInput.close();
    sender.close();
    receiver.close();
    gameLoop.close();
    receiver.join();
    sender.join();
    userInput.join();
    gameLoop.join();
}