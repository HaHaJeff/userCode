#include "CoContextEpoll.h"
#include <iostream>
#include <strings.h>
#include <string.h>
#include <assert.h>

using namespace std;
using namespace coroutine;

void EchoClient(void *args) {
  const char* ip = "127.0.0.1";
  int port = 9999;

  EpollArgs_t *tt= (EpollArgs_t*)args;

  int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TP);

  CoContextSocket_t *socket = tt->first->CreateSocket(fd);

  std::cout << "start " << fd << std::endl;

  struct sockaddr_in in_addr;
  bzero(&in_addr, sizeof(struct sockaddr_in));

  in_addr.sin_family = AF_INET;
  in_addr.sin_addr.s_addr = inet_addr(ip);
  in_addr.sin_port = htons(port);

  CoContextSetConnectTimeout(*socket, 1000);


  int ret = CoContextConnect(*socket, (struct sockaddr*)&in_addr, sizeof(in_addr));
  if (ret != 0) {
    CoContextClose(*socket);
    free(socket);
    free(tt);

    return;
  }

  char line[1024] = { 0 };
  CoContextRecv(*socket, line, sizeof(line), 0);

  for (int i = 0; i < 10; i++) {
    snprintf(line, sizeof(line), "%d\n", i);
    CoContextSend(*socket, line, strlen(line), 0);

    memset(line, 0, sizeof(line));
    CoContextRecv(*socket, line, sizeof(line), 0);

    assert(i == atoi(line));
  }


  CoContextSend(*socket, "quit\n", 5, 0);

  std::cout << "end " << fd << std::endl;

  CoContextClose(*socket);

  free(socket);
  free(args);
}

void Test(int count) {
  EpollScheduler scheduler(64*1024, count);

  for (int i = 0; i < count; i++) {
    EpollArgs_t* args = (EpollArgs_t*)calloc(1, sizeof(EpollArgs_t));
    args->first = &scheduler;

    scheduler.AddTask(EchoClient, args);
  }

  scheduler.Run();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <count>\n", argv[0]);
    return -1;
  }

  Test(atoi(argv[1]));
}
