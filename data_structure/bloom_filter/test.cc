#include "bloomfilter.h"
#include "bloomtest.h"
#include <iostream>

TEST(TestBase, BloomFilter)
{
  BloomFilter<int> b(100, 0.1);
  std::cout << "TestBase" << std::endl;
}

int main()
{
}
