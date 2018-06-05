#pragma once

#include <unistd.h>
#include <ucontext.h>
#include <functional>
#include <assert.h>

#include "CoUtil.h"
#include "CoContext.h"

namespace coroutine {
  class CoContextSys : public CoContext {
    public:
      CoContextSys(size_t stack_size, CoFunc_t func, void *args, CoDoneCallback_t callback, const bool need_stack_protect);
      ~CoContextSys();

      static CoContext *DoCreate(size_t stack_size, CoFunc_t func, void *args, CoDoneCallback_t callback, const bool need_stack_protect);

      void Make(CoFunc_t func, void *args) override;
      bool Resume() override;
      bool Yield() override;

      ucontext_t *GetMainContext();

    private:
      static void CoFuncWrapper(uint32_t low32, uint32_t high32);

      ucontext_t        context_;    //协程上下文
      CoFunc_t          func_;       //协成的执行体
      void              *args_;      //执行体参数
      CoStackMemory     stack_;      //协程的栈
      CoDoneCallback_t  callback_;   //协程执行完之后的回调函数
  };
}
