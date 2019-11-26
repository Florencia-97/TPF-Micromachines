#include <threads/GamesManagerThread.h>

#include <iostream>
#include "Server.h"


int Server::play(std::string& port) {
    std::cout << "Server running!\n";
    GamesManagerThread gamesManager(port);
    gamesManager.run();
    std::cout << "Game Manager running!\n";
    std::string input;
    // Server closes with a simple q
    while (input.compare("q") != 0) getline(std::cin, input);
    std::cout << "Server is closing, please wait up to a few seconds\n";
    gamesManager.close();
    gamesManager.join();
    std::cout << "Goodbye, and thanks for playing our game\n";
}