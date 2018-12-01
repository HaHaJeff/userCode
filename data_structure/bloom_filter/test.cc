#include "bloomfilter.h"
#include "bloomtest.h"
#include <iostream>

const int key_nums = 10000;
const double false_positive = 0.1f;

TEST(TestBase, BloomFilter)
{
  BloomFilter<Key> b(key_nums, false_positive);
  for (int i = 0; i <= key_nums; i++) {
    b.insert(i);
  }

  int matched = 0;
  for (int i = 0; i < 10000; i++) {
    if(b.keyMayMatch(i+10000000)) {
      matched += 1;
    }
  }
  std::cout << "key_nums = " << key_nums << " expted false positive rate = " << false_positive << " read false positive rate " << matched * 1/10000 << std::endl;
}

int main()
{
  runAllTests();
}
