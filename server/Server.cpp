#include <threads/GamesManagerThread.h>

#include <iostream>
#include "Server.h"


int Server::play(std::string& port) {
    std::cout << "Server running!\n";
    // TODO: check if port is right
    GamesManagerThread gamesManager(port);
    gamesManager.run();
    std::cout << "Game Manager running!\n";
    std::string input;
    // Server closes with a simple q
    while (input.compare("q") != 0) getline(std::cin, input);
    gamesManager.close();
    gamesManager.join();
}