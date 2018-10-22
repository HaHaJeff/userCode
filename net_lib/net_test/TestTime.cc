#include <iostream>
#include <poll.h>
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

int main()
{
  RunAllTests();
}
