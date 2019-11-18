#include <string>
#include <iostream>
#include "Server.h"

// ./Server port
int main (int argc, char** argv) {
    if (argc != 2) throw std::runtime_error("No port was specified! use ./Server [PORT]\n");
    try {
        Server server;
        std::string port = argv[1];
        return server.play(port);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Exception unknown occurred\n";
        return 1;
    }
}