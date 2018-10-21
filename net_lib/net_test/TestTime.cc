#include <iostream>
#include "timestamp.h"
#include "net_test.h"

TEST(TestBase, TimeStamp) {
  TimeStamp t(TimeStamp::Now());
  std::cout << t.ToString() << std::endl;
  std::cout << t.ToFormattedString() << std::endl;
}

int main()
{
  RunAllTests();
}
