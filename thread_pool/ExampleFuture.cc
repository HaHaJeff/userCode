#include "ThreadPoolFuture.h"

int Pow(int x, int y) {
  return x * x + y * y;
}

int main()
{
  ThreadPool pool;

  auto res = pool.AddTask(std::bind(Pow, 2, 3));

  std::cout << res.get() << std::endl;

}
