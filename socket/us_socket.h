#ifndef __US__SOCKET_H
#define __US_SOCKET_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <assert.h>

#define MAX_BACKLOG 5 

#define DEBUG_INFO \
    do { \
        fprintf(stderr, "File:%s\tLine:%d\n", __FILE__, __LINE__); \
    }while(0)

#define ERR_EXIT(message) \
    do { \
        perror(message);\
        exit(EXIT_FAILURE);\
     }while(0)



int Inet_pton4() {
}

int Inet_pton6() {

}

int Inet_ntop4() {

}

int Inet_ntop6() {

}

char* SockAddrToString(const struct sockaddr_in* addr) {
    char host[32] = {};
    int port = 0;

    inet_ntop(AF_INET, &addr->sin_addr, host, sizeof(struct sockaddr));
    port = ntohl(addr->sin_port);

    char ip[50] = {};
    
    strcat(ip, "ip:");
    strcat(ip, host);

    return ip;
}

inline struct sockaddr_in6 SockAddr6(const char* host, int port) {
    struct sockaddr_in6 addr;

    if (1 != inet_pton(AF_INET6, host, &addr.sin6_addr)) {
        DEBUG_INFO;
        ERR_EXIT("SockAddr6 inet_pton");
    }

    addr.sin6_port = htons(port);
    addr.sin6_family = AF_INET6;
    return addr;
}

inline struct sockaddr_in SockAddr4(const char* host, int port) {
    struct sockaddr_in addr;

    if (-1 == inet_pton(AF_INET, host, &addr.sin_addr)) {
        DEBUG_INFO;
        ERR_EXIT("SockAddr4 inet_pton");
    }

    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;

    return addr;
}

int Socket(int af, int type) {
    int sock_fd = socket(af, type, 0);

    if (-1 == sock_fd){
        DEBUG_INFO;
        ERR_EXIT("Socket");
    }

    return sock_fd;
}

int Bind(int sock_fd, struct sockaddr_in* addr, socklen_t len) {
    int ret = bind(sock_fd, (struct sockaddr*)addr, len);

    if (-1 == ret) {
        DEBUG_INFO;
        ERR_EXIT("Bind"); 
    }

    return ret;
}

int Connect(int sock_fd, const struct sockaddr_in* addr, socklen_t len) {
    int ret = connect(sock_fd, (const struct sockaddr*)addr, len);

    if (-1 == ret) {
        DEBUG_INFO;
        ERR_EXIT("Connect");
    }

    return ret;
}

int Listen(int sock_fd, int baklog) {
    int ret = listen(sock_fd, baklog);

    if (-1 == ret) {
        DEBUG_INFO;
        ERR_EXIT("Listen");
    }

    return ret;
}

int Accept(int sock_fd, struct sockaddr_in* addr, socklen_t* len) {
    int ret = accept(sock_fd, (struct sockaddr*)addr, len);

    if (-1 == ret) {
        DEBUG_INFO;
        ERR_EXIT("Accept");
    }

    return ret;
}

int TCPListen(const char* host, int port) {
    int sock_fd = 0;
    struct sockaddr_in addr;

    socklen_t sock_len = sizeof(struct sockaddr);
    sock_fd = Socket(AF_INET, SOCK_STREAM);
    addr = SockAddr4(host, port);
    
    Bind(sock_fd, &addr, sock_len);

    Listen(sock_fd, MAX_BACKLOG);

    return sock_fd;
}

int TCPConnect(const char* host, int port) {
    int sock_fd = 0;
    struct sockaddr_in addr;

    socklen_t sock_len = sizeof(struct sockaddr);
    sock_fd = Socket(AF_INET, SOCK_STREAM);
    addr = SockAddr4(host, port);

    //Bind(sock_fd, &addr, sock_len); 

    Connect(sock_fd, &addr, sock_len);

    return sock_fd;
}

#endif
