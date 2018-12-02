#include "bloomfilter.h"
#include "bloomtest.h"
#include <iostream>
#include <unistd.h>

const int key_nums = 10000;
const double false_positive = 0.1f;

TEST(TestBase, GenerateKey)
{
  for (int base = 1; base < 10; base++) {
    BloomFilter<Key> b(key_nums*base, false_positive);
    // generate keys
    for (int i = 0; i <= key_nums*base; i++) {
      b.insert(i);
    }
  }
}

#ifdef OPT
TEST(TestBase, GenerateKeyOpt)
{
  for (int base = 1; base < 10; base++) {
    BloomFilter<Key> b(key_nums*base, false_positive);
    // generate keys
    for (int i = 0; i <= key_nums*base; i++) {
      b.insertOpt(i);
    }
  }
}
#endif

TEST(TestBase, KeyMatch)
{
  // test
  for (int base = 1; base < 10; base++) {
    BloomFilter<Key> b(key_nums*base, false_positive);
    int matched = 0;
    // generate keys
    for (int i = 0; i <= key_nums*base; i++) {
      b.insert(i);
    }
    for (int i = 0; i < 10000; i++) {
      if(b.keyMayMatch(Key(i+1000000000))) {
        matched += 1;
      }
    }
    b.printSelf();
    std::cout << "real false positive rate " << matched * 1.0f/10000 << std::endl;
  }
}

#ifdef OPT
TEST(TestBase, KeyMatchOpt)
{
  // test
  for (int base = 1; base < 10; base++) {
    int matched = 0;
    BloomFilter<Key> b(key_nums*base, false_positive);
    // generate keys
    for (int i = 0; i <= key_nums*base; i++) {
      b.insertOpt(i);
    }
    for (int i = 0; i < 10000; i++) {
      if(b.keyMayMatchOpt(Key(i+1000000000))) {
        matched += 1;
      }
    }
    b.printSelf();
    std::cout << "real false positive rate " << matched * 1.0f/10000 << std::endl;
  }
}
#endif

int main()
{
  pid_t pid = getpid();
  std::cout << "pid: " << pid << std::endl;
  sleep(20);
  runAllTests();
}
