#include "Client.h"

// ./Client service port
int main(int argc, char *args[]) {
    if (argc != 3) throw std::runtime_error("Error! use ./Client [HOST] [PORT]");
    try {
        std::string service = args[1];
        std::string port = args[2];
        Client client(service, port);
        return client.play();
    } catch (...) {
        std::cout << "Exception unknown occurred\n";
        return 1;
    }
}
