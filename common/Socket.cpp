#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>

#include <string>
#include "Socket.h"

#define MAX_CLIENTES 10

Socket::Socket(): fd(-1) {}

Socket::Socket(int fd): fd(fd) {}

Socket::Socket(Socket&& other){
    this->fd = other.fd;
    other.fd = -1;
}

Socket& Socket::operator=(Socket&& other){
    if (this != &other){
        this->fd = other.fd;
        other.fd = -1;
    }
    return *this;
}

void Socket:: _set_addr_info(int flag, struct addrinfo *answ){
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = flag; 
    *answ = hints;
}

int Socket::_bind(struct addrinfo* ptr){
    int r = bind(this->fd, ptr->ai_addr, ptr->ai_addrlen);
    if (r == -1) {
        this->closeSd();
    }
    return r == 0 ? 0 : 1;
}

int Socket::_listen(int cant){
    int r = listen(this->fd, cant);
    if (r == -1) {
      this->closeSd();
    }
    return r == 0 ? 0 : 1;
}

int Socket::_socket_re_dir(){
    int val = 1;
    int s = setsockopt(this->fd , SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (s == -1) {
        this->closeSd();
        return 1;
    }
    return 0;
}

int Socket::_connect(struct addrinfo* ptr){
    int s = connect(this->fd, ptr->ai_addr, ptr->ai_addrlen);
    if (s == -1) {
        this->closeSd();
    }
    return s;
}

int Socket::client(std::string hostname, std::string service){
    bool connect = false;
    struct addrinfo *result, *ptr;
    struct addrinfo hints;
    this->_set_addr_info(0, &hints);           
    int s = getaddrinfo(hostname.c_str(), service.c_str(), &hints, &result);
    if (s != 0) return 1;
    for (ptr = result; ptr != NULL && connect == false; ptr = ptr->ai_next){
        this->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (this->fd != -1) {
            s = this->_connect(ptr);
            connect = (s == 0);
        }
    }
    freeaddrinfo(result);
    return connect ? 0 : 1; 
}

int Socket::server(std::string service){
    bool connect = false;
    struct addrinfo *result, *ptr;
    int s, r;
    struct addrinfo hints;
    this->_set_addr_info(AI_PASSIVE, &hints);   
    s = getaddrinfo(NULL, service.c_str(), &hints, &result);
    if (s != 0) return 1;
    for (ptr = result; ptr != NULL && connect == false; ptr = ptr->ai_next) {
        this->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (this->fd != -1) {
            r = this->_socket_re_dir();
            s = r == 0 ? this->_bind(ptr) : 1;
            connect = (s == 0);
        }
    }
    freeaddrinfo(result);
    return  connect == false? 1 : this->_listen(MAX_CLIENTES);
}

int Socket::receive(void* buffer, size_t size){
    size_t received = 0;
    int s = 0;
    bool is_the_socket_valid = true;
    char* buf = (char*) buffer;
    while (received < size && is_the_socket_valid) {
        s = recv(this->fd, &buf[received], size-received, 0);
        if (s == 0 || s == -1) {
            is_the_socket_valid = false;
        } else {
            received += s;
        }
    }
    buffer = buf;
    if (s == 0 || s < 0) throw socketDesconectado();
    return is_the_socket_valid == true ? 0 : 1;
}

int Socket::sendMsg(const void* buffer, size_t len){
    int s = 0;
    size_t bytes_sent = 0;
    bool valid = true, close = false;
    char* buf = (char*) buffer;
    while (bytes_sent < len && valid && close == false) {
        s = send(this->fd , &buf[bytes_sent], len - bytes_sent, MSG_NOSIGNAL);
        if (s == -1) {
            valid = false;
        } else if (s == 0) {
            close = true;
        } else {
            bytes_sent += s;
        }
    }
    if (s == 0 || s < 0) throw socketDesconectado();
    return bytes_sent;
}

Socket Socket::acceptClient(){
    int aceptado = accept(this->fd, nullptr, nullptr);
    return std::move(Socket(aceptado));
}

bool Socket::isValid(){
    return this->fd != -1;
}

void Socket::closeSd(){
    if (this->fd != -1){
        shutdown(this->fd, SHUT_RDWR);
        close(this->fd);
    }
}

Socket::~Socket(){
    this->closeSd();
}
