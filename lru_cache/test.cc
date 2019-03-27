#include "lru_cache.h"

int main()
{

  cache::LRUCache<int, int> cache(3);
  cache.Put(1,1);
  cache.Put(2,2);
  cache.Put(3,3);
  cache.Print();
  cache.Put(4,4);
  cache.Print();
  cache.Get(2);
  cache.Print();
  cache.Put(5, 5 );
  cache.Print();
  
}
