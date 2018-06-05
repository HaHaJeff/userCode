#pragma once

#include <unistd.h>
#include <functional>

namespace coroutine {

class CoContext;

typedef std::function< void(void *) > CoFunc_t;
typedef std::function< void() > CoDoneCallback_t;
typedef std::function< CoContext*(size_t, CoFunc_t, void *, CoDoneCallback_t, const bool) > CoContextCreateFunc_t;

//将CoContext变成一个抽象类的好处：提供接口，而不提供具体实现，将具体实现与具体特定系统
//绑定，从而使得程序可移植
class CoContext {
  public:
    CoContext() {  }
    virtual ~CoContext() {  }

    //设置成静态函数的好处：一个统一的借口，通过SetContextCreateFunc
    //可以设置具体的执行func，在CoRuntime可以完美体现
    static CoContext *Create(size_t stack_size, CoFunc_t func,
        void *args, CoDoneCallback_t callback, const bool need_stack_protect);

    //
    static void SetContextCreateFunc(CoContextCreateFunc_t context_create_func);
    static CoContextCreateFunc_t GetContextCreateFunc();

    virtual void Make(CoFunc_t func, void *args) = 0;
    virtual bool Resume() = 0;
    virtual bool Yield()  = 0;

  private:
    static CoContextCreateFunc_t context_create_func_;
};
}
