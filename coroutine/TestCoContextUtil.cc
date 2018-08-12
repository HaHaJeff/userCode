#include "CoContextUtil.h"
#include <iostream>
using namespace coroutine;

int main() {

  CoStackMemory stack(7*1024);

  std::cout << "stack top: " << stack.Top() << std::endl;
  std::cout << "stack size: " << stack.Size() << std::endl;
}
