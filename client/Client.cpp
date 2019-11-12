
#include "Client.h"
#include "../common/infostream/Protocol.h"

bool Client::connectionCheck(){
    return (connection_state.exists(CONNECTED_TO_GAME) &&
            connection_state.getString(CONNECTED_TO_GAME) == CONNECTED_TO_GAME_YES);
}

void Client::waitGameEnd(){
    std::mutex m;
    std::unique_lock<std::mutex> l(m);
    while (!gameLoop.in_menu.load() && !userInput.exit) {
        ready_to_connect.wait(l);
    }
    receiver.close();
    sender.close();
    receiver.join();
    sender.join();
}

void Client::waitReadyButton() {
    gameLoop.menu.ready = false;
    std::mutex m;
    std::unique_lock<std::mutex> l(m);
    while (!gameLoop.menu.ready && !userInput.exit) {
        ready_to_connect.wait(l);
    }
}

bool Client::attempConnection() {
    skt.client(this->service, this->port);
    if (!skt.isValid()) throw  serverNotRunning();
    connection_state[ARENA_GAME] = gameLoop.menu.map_selected;
    connection_state[CAR_TYPE] = gameLoop.menu.car_selected;
    if (!Protocol::sendMsg(&skt, connection_state)) throw  serverNotRunning();
    if (!Protocol::recvMsg(&skt, connection_state)) throw  serverNotRunning();
    return connectionCheck();
}

bool Client::waitForConnection(){
    bool connection_successful = false;
    while (!userInput.exit && !connection_successful) {
        waitReadyButton();
        if (!userInput.exit) {
            try { connection_successful = attempConnection();}
            catch (serverNotRunning &e) {
                gameLoop.menu.displayNotification("server is not running!");
            }
        }
    }
}

int Client::play() {
    gameLoop.run();
    userInput.run();

    while (!userInput.exit){
        try {
            waitForConnection();
        } catch (const std::exception& e){
            std::cout << e.what() << std::endl;
            release();
            return 1;
        }
        if (skt.isValid() && !userInput.exit) {
            bool is_leader = connection_state.getString(OWNER) == OWNER_YES;
            gameLoop.proceedToLobby(is_leader);
            gameLoop.menu.displayNotification("connected   proceeding   to   game!");
            if (is_leader) {
                //todo waitReadyButton()
                sleep(5);
                InfoBlock ib;
                ib[RACE_ID] = gameLoop.menu.map_selected;
                keyboard_e_queue.push(ib);
            }

            if (!receiver.isRunning()) {
                receiver.run();
                sender.run();
            }
            waitGameEnd();
        }

    }

    release();
    return 0;
}

Client::Client(std::string& s, std::string& p) : gameLoop(this->receiver_queue, text_queue, mouse_queue, ready_to_connect, sound_queue),
                   userInput(&keyboard_e_queue, &mouse_queue, &text_queue, &sound_queue, &ready_to_connect),
                   receiver(skt, &receiver_queue), sender(skt, &keyboard_e_queue)
{
    this->service = s;
    this->port = p;
}

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
