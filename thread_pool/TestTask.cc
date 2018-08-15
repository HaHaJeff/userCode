//#include "Task.h"
#include <iostream>
#include <utility>
#include <type_traits>
#include <functional>

template <class F, class ...Args>
auto Call(F&& f, Args&&... args) ->typename std::result_of<F(Args...)>::type
{
  auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
  auto res = task();
  return res;
}


int main()
{
  Call([]{
      std::cout << "hello" << std::endl;
      return 1*1;
      });
}
