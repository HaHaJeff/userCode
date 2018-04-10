#include "us_socket.h"

int main(int args, char** argv) {
    if (args != 3) {
        fprintf(stderr, "%s\n", "TestSocketServer <host> <port>");
        exit(-1);
    }
    char* host = argv[1];
    int port = atoi(argv[2]);

    int listen_fd = TCPListen(host, port);

    while (1) {
        struct sockaddr_in conn_addr;
        socklen_t len = sizeof(struct sockaddr_in);
        sleep(5);
        int conn_fd = Accept(listen_fd, &conn_addr, &len);

        char* ip = SockAddrToString(&conn_addr);
        int ret = send(conn_fd, ip, strlen(ip) + 1, 0);
        if (-1 == ret) {
            DEBUG_INFO;
            ERR_EXIT("send");
        }
        if (recv(conn_fd, ip, 5, 0) == 0) {
            DEBUG_INFO;
            ERR_EXIT("recv");
        }
        printf("conn_addr: %s\n", ip);
        free(ip);
        ip = NULL;
    }

    return 0;
}
