#include <iostream>
#include <poll.h>
#include "socket.h"
#include "net.h"
#include "buffer.h"
#include "eventloop.h"
#include "log.h"
#include "timer.h"
#include "timestamp.h"
#include "channel.h"
#include "processinfo.h"
#include "net_test.h"
#include "timerqueue.h"


int func() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  Net::SetNonBlock(fd);
  Socket s(fd);
  Ip4Addr ip4("127.0.0.1", 9999);
  const struct sockaddr* addr = sockaddr_cast(&ip4.GetAddr());
  int connfd = connect(fd, addr, sizeof(struct sockaddr));
  if (connfd == -1) {
      printf("-1\n");
  }

  struct pollfd pfd;
  pfd.fd = fd;
  pfd.events = POLLOUT | POLLERR;

  //connect完成之后文件描述父可写
  int r = poll(&pfd, 1, 0);

  if (r == 1 && pfd.revents == POLLOUT) {
    printf("connect\n");
  }
}

int main()
{
    func();
}
