
#include "Client.h"
#include "../common/infostream/Protocol.h"

bool Client::connectionCheck(){
    return (connection_state.exists(CONNECTED_TO_GAME) &&
            connection_state.getString(CONNECTED_TO_GAME) == CONNECTED_TO_GAME_YES);
}

bool Client::attempConnection() {
    skt.client(SERVICE, PORT);
    if (!skt.isValid()) throw  serverNotRunning();
    connection_state[ARENA_GAME] = "insert funny meme";
    connection_state[CAR_TYPE] = "car_name";
    if (!Protocol::sendMsg(&skt, connection_state)) throw  serverNotRunning();
    if (!Protocol::recvMsg(&skt, connection_state)) throw  serverNotRunning();
    return connectionCheck();
}


int Client::play() {
    RenderThread renderThread(this->receiver_queue);
    UserInput userInput(&keyboard_e_queue, &mouse_e_queue);

    renderThread.run();
    userInput.run();
    try {
        while (!connectionCheck() && !attempConnection()){
            sleep(1/20); //todo remove
        }
    } catch (const std::exception& e){
        // TODO: fix seg fault, i believe there is something closing wronng.
        std::cout << e.what() << std::endl;
        skt.closeSd();
        userInput.close();
        renderThread.close();
        userInput.join();
        renderThread.join();
        return 1;
    }
    bool is_leader = connection_state.getString(OWNER) == OWNER_YES;
    renderThread.proceedToLobby(is_leader);

    Receiver receiver(skt, &receiver_queue);
    EventSender sender(skt, &keyboard_e_queue);
    receiver.run();
    sender.run();

    if (skt.isValid()) {
        if (is_leader) {
            sleep(1);
            InfoBlock ib;
            ib[RACE_ID] = "race_1";
            keyboard_e_queue.push(ib);
        }
        sleep(20);
    }

    skt.closeSd();
    userInput.close();
    sender.close();
    receiver.close();
    renderThread.close();
    receiver.join();
    sender.join();
    userInput.join();
    renderThread.join();

    return 0;
}
