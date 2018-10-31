#include <iostream>
#include <poll.h>
#include "buffer.h"
#include "eventloop.h"
#include "log.h"
#include "timer.h"
#include "timestamp.h"
#include "channel.h"
#include "net_test.h"


TEST(TestBase, TimeStamp) {
  TimeStamp t(TimeStamp::Now());
  std::cout << t.ToString() << std::endl;
  std::cout << t.ToFormattedString() << std::endl;
}

TEST(TestBase, Channel) {
  Channel ch(nullptr, 0);
  ch.SetREvents(POLLNVAL);
  ch.HandleEvent();
}

TEST(TestBase, Buffer) {
  Buffer buf;
  char b[1024] = "hellow, world";
  buf.Append(b, 1024);

  buf.Consume(7);

  std::cout << buf.GetData() << std::endl;
}

TEST(TestBase, EventLoop) {
  Logger& log = Logger::GetLogger();
  log.SetFileName("event.log");
  EventLoop loop;

  int i = 0;
  while (i < 1) {
    loop.RunAfter(2.0, [i]
        {
          std::cout << "RunAfter: " << i << std::endl;
        }
        );
    i+=1;
  }

  loop.Loop();
}


int main()
{
  RunAllTests();
}
