#include "Client.h"

// ./Client service port
int main(int argc, char *args[]) {
    try {
        if (argc != 3) return 1;
        std::string service = args[1];
        std::string port = args[2];
        Client client(service, port);
        return client.play();
    } catch (...) {
        std::cout << "Exception unknown occurred";
        return 1;
    }
}
