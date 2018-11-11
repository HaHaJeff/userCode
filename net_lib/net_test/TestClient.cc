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


TEST(TestBase, TestClient) {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  Socket s(fd);
  Ip4Addr ip4("127.0.0.1", 9999);
  s.BindAddress(ip4);
  const struct sockaddr* addr = sockaddr_cast(&ip4.GetAddr());
  int fd = connect(fd, &addr, sizeof(struct sockaddr));

  struct pollfd pfd;
  pfd.fd = fd;
  pfd.events = POLLOUT | POLLERR;

  int r = poll(&pfd, 1, 0);

  if (r == 1 && pfd.revents == POLLOUT) {
    printf("connect");
  }
}


int main()
{
  RunAllTests();
}
