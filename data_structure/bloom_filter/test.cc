#include "bloomfilter.h"
#include <iostream>


int main()
{
  BloomFilter<Key> bloom(100, 0.1);
  for (int i = 0; i < 100; i++) {
    bloom.insert(i);
  }

  std::cout << "1 exists? "<<bloom.keyMayMatch(1) << std::endl;
  std::cout << "102 exists? "<<bloom.keyMayMatch(1020) << std::endl;
}
