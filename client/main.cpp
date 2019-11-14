#include "Client.h"

// ./Client service port
int main(int argc, char *args[]) {
    try {
        if (argc != 3) throw std::runtime_error("error! use ./Client [HOST] [PORT]\n");;
        std::string service = args[1];
        std::string port = args[2];
        Client client(service, port);
        return client.play();
    } catch (...) {
        std::cout << "Exception unknown occurred\n";
        return 1;
    }
}
