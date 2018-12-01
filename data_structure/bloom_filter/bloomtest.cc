#include <vector>
#include <string>
#include "bloomtest.h"

struct Test {
  const char* base;
  const char* name;
  void (*func)();
};

std::vector<Test>* getVectorTest() {
  static std::vector<Test> tests;
  return &tests;
}

bool RegisterTest(const char* base, const char* name, void(*func)()) {
  std::vector<Test>* tests = getVectorTest();

  Test t;
  t.base = base;
  t.name = name;
  t.func = func;
  tests->push_back(t);
  return true;
}

int runAllTests() {
  std::vector<Test>* tests = getVectorTest();

  if (tests->size() != 0) {
    for (auto elem : *tests) {
      fprintf(stderr, "==== Test %s.%s\n", elem.base, elem.name);
      elem.func();
    }
  }
  return 0;
}

