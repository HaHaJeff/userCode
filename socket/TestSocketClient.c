#include "us_socket.h"

int main(int argc, char** argv) {
    
    if (argc != 3) {
        fprintf(stderr, "%s\n", "TestSocketClient: <host> <port>");
        exit(-1);
    }

    char* host = argv[1];
    int port = atoi(argv[2]);

    int sock_fd = TCPConnect(host, port); 


    while (1) {}

    return 0;
}
