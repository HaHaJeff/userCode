#include "CoContextRuntime.h"
#include <iostream>

using namespace std;
using namespace coroutine;

void TestFunc1(void *);
void TestFunc2(void *);


void TestFunc1(void *args) {
  for(int i = 0; i < 10; i++) {
    std::cout << "TestFunc1" << std::endl;
    std::cout << i << std::endl;
  }
}

void TestFunc2(void *args) {
  for(int i = 0; i < 10; i++) {
    std::cout << "TestFunc2" << std::endl;
    std::cout << i << std::endl;
  }
}

int main() {
  CoContextRuntime runtime(64 * 1024, true);
  runtime.Create(&TestFunc1, nullptr);
  runtime.Create(&TestFunc2, nullptr);

  runtime.Resume(0);
  runtime.Resume(1);

  std::cout << "runtime is all done ? " << runtime.IsAllDone() << std::endl;
}
