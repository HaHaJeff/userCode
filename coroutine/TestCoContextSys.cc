#include "CoContextSys.h"
#include <iostream>
#include <stdio.h>

using namespace coroutine;

void TestFunc1(void *);
void TestFunc2(void *);

CoContextSys ctx1(64 * 1024, &TestFunc1, nullptr, nullptr, true);
CoContextSys ctx2(64 * 1024, &TestFunc2, nullptr, nullptr, true);

int test_count = 0;

void TestFunc1(void *args) {
  for (int i = 0; i < test_count; i++) {
    std::cout << "TestFunc1 Yield" << std::endl;
    ctx1.Yield();
    std::cout << "TestFunc1 Resume" << std::endl;
  }
}

void TestFunc2(void* args) {
  for (int i = 0; i < test_count; i++) {
    std::cout << "TestFunc2 Yield" << std::endl;
    ctx2.Yield();
    std::cout << "TestFunc2 Resume" << std::endl;
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("%s <test times>\n", argv[0]);
    return -2;
  }

  test_count = atoi(argv[1]);
  int test_count_2 = (test_count+1)*2;
  int test_count_3 = (test_count+1);

  for (int i = 0; i < test_count_2; i++) {
    if (i < test_count_3) {
      ctx1.Resume();
    } else {
      ctx2.Resume();
    }
  }
  return 0;
}
