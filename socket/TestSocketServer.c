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
        int conn_fd = accept(listen_fd, (struct sockaddr*)&conn_addr, &len);
        printf("conn_addr: %s\n", SockAddrToString(&conn_addr));
    }

    return 0;
}
