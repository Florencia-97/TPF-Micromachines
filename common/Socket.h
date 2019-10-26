#ifndef _SOCKET_
#define _SOCKET_

#include <string>

class socketDisconnected : public std::exception {
    virtual const char* what() const throw() {
        return "Socket was disconnected\n";
    }
};

class Socket {
    int fd;
    int _bind(struct addrinfo* ptr);
    int _listen(int cant);
    int _connect(struct addrinfo* ptr);
    void _set_hints(int flag);
    int _create();
    int _socket_re_dir();
    void _set_addr_info(int flag, struct addrinfo *hint);

    public:
    Socket();
    Socket(int fd);

    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    Socket(Socket&& other);
    Socket& operator=(Socket&& other);

    int receive(void* buf, size_t size);
    int sendMsg(const void* buffer, size_t len);
    Socket acceptClient();
    void closeSd();
    int client(std::string hostname, std::string service);
    int server(std::string service);
    bool isValid();
    ~Socket();
};


#endif