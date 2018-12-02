#include "bloomfilter.h"
#include "bloomtest.h"
#include <iostream>
#include <unistd.h>

const int key_nums = 10000000;
const double false_positive = 0.1f;

TEST(TestBase, BloomFilter)
{

  sleep(15);
  for (int base = 1; base < 10; base++) {

    BloomFilter<Key> b(key_nums*base, false_positive);
    // generate keys
    for (int i = 0; i <= key_nums*base; i++) {
      b.insert(i);
    }

    // test
    int matched = 0;
    for (int i = 0; i < 10000; i++) {
      if(b.keyMayMatch(Key(i+1000000000))) {
        matched += 1;
      }
    }
    b.printSelf();
    std::cout << "real false positive rate " << matched * 1.0f/10000 << std::endl;
  }


}

int main()
{
  runAllTests();
}
