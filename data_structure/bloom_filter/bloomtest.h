#ifndef BLOOMFILTER_TEST_H
#define BLOOMFILTER_TEST_H

int runAllTests();

bool registerTest(const char* base, const char* name, void(*func)());

//为什么这么写？
//如果不通过宏定义调用宏定义，那么被调用的宏定义将不会被展开
#define TCONCAT(a, b) TCONCAT1(a, b)
#define TCONCAT1(a, b) a##b

//自动生成代码
#define TEST(base, name)                                     \
class TCONCAT(_Test_, name) : public base {                  \
  public:                                                    \
    void run();                                              \
    static void RunIt() {                                    \
      TCONCAT(_Test_, name) t;                               \
      t.run();                                               \
    }                                                        \
};                                                           \
bool TCONCAT(_Test_ignored_, name) =                         \
  registerTest(#base, #name, &TCONCAT(_Test_, name)::runIt); \
void TCONCAT(_Test_, name)::run()

class TestBase {};

#endif
