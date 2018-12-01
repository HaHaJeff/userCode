#ifndef BLOOMFILTER_TEST_H
#define BLOOMFILTER_TEST_H


int runAllTest();

bool registerTest(const char* base, const char* name, void(*func)());

#define TCONCAT(a, b) TCONCAT1(a, b)
#define TCONTAT1(a, b) a##b


//自动生成代码
#define TEST(base, name)                                     \
class TCONCAT(_Test_, name) : public base {                  \
  public:                                                    \
    void Run();                                              \
    static void RunIt() {                                    \
      TCONCAT(_Test_, name) t;                               \
      t.Run();                                               \
    }                                                        \
};                                                           \
bool TCONCAT(_Test_ignored_, name) =                         \
  registerTest(#base, #name, &TCONCAT(_Test_, name)::RunIt); \
void TCONCAT(_Test_, name)::run()

class TestBase {};

#endif
