#include "ThreadPool.h"

int main()
{
  ThreadPool pool;

  for (int i = 0; i < 100; i++)
    pool.AddTask([i]{
          std::cout << "hello " << i << std::endl;
        });

}
