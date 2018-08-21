#include "CoContextEpoll.h"
#include <iostream>
#include <unistd.h>
#include <string.h>

#include <queue>

using namespace coroutine;


void EchoServer(void *args) {
  EpollArgs_t *tt = (EpollArgs_t*)args;

  CoContextSocket_t *socket = tt->first->CreateSocket(tt->second);

  char line[1024] = { 0 };

  const char* welcome = "Input quit to stop\n";
  printf("start %d\n", tt->second);

  CoContextSend(*socket, welcome, strlen(welcome), 0);

  for (;;) {
    memset(line, 0, sizeof(line));
    CoContextRecv(*socket, line, sizeof(line), 0);

    if (0 == strncasecmp(line, "quit", 4)) {
      break;
    }

    CoContextSend(*socket, line, strlen(line), 0);
  }

  printf("end %d\n", tt->second);

  CoContextClose(*socket);
  free(socket);
  free(tt);
}


void EchoAccept(void *args) {
  EpollArgs_t *tt = (EpollArgs_t*) args;
  CoContextSocket_t *acceptor= tt->first->CreateSocket(tt->second);

  for (;;) {
    struct sockaddr_in addr;
    socklen_t socklen = sizeof(addr);
    int fd = CoContextAccept(*acceptor, (struct sockaddr*)&addr, &socklen);

    printf("accept %d\n", fd);

    if (fd >= 0) {
      EpollArgs_t *ct = (EpollArgs_t*) calloc(1, sizeof(EpollArgs_t));
      ct->first = tt->first;
      ct->second = fd;

      tt->first->AddTask(EchoServer, ct);
    }
  }

  CoContextClose(*acceptor);
  free(acceptor);
  free(tt);
}

void Test(int count) {
  int listenfd = -1;
  char *ip = "127.0.0.1";
  int port = 9999;

  struct sockaddr_in in_addr;
  bzero(&in_addr, sizeof(struct sockaddr_in));

  in_addr.sin_family = AF_INET;
  in_addr.sin_addr.s_addr = inet_addr(ip);
  in_addr.sin_port = htons(port);

  if ( (listenfd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1 ) {
      perror("socket");
  }
  if ( bind(listenfd, (struct sockaddr*)&in_addr, sizeof(in_addr)) == -1 ) {
    perror("bind");
  }
  if (listen(listenfd, 10) == -1) {
    perror("listen");
  }

  EpollScheduler scheduler(64*1024, count+1);

  {
    EpollArgs_t *args = (EpollArgs_t*) calloc(1, sizeof(EpollArgs_t));
    args->first = &scheduler;
    args->second = listenfd;

    scheduler.AddTask(EchoAccept, args);
  }
  scheduler.Run();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <count>\n", argv[0]);
    return -1;
  }
  Test(atoi(argv[1]));

  return 0;
}
