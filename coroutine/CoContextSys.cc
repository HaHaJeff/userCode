#include "CoContextSys.h"

//讲CoContextSys对象保存在ucontext_t中，在makecontext中传递一个回调函数，参数为两个int类型
//而在64bit系统中，需要讲CoContextSys的地址分为两个intptr_t类型传入，在回调函数中将其复原
namespace coroutine {
  CoContextSys::CoContextSys(size_t stack_size, CoFunc_t func, void *args, CoDoneCallback_t callback, const bool need_stack_protect)
    : func_(func), args_(args), stack_(stack_size, need_stack_protect), callback_(callback) {
      Make(func, args);
  }

  CoContextSys::~CoContextSys() {
  }

  CoContext *CoContextSys::DoCreate(size_t stack_size, CoFunc_t func, void *args, CoDoneCallback_t callback, const bool need_stack_protect) {
    return new CoContextSys(stack_size, func, args, callback, need_stack_protect);
  }

  void CoContextSys::Make(CoFunc_t func, void *args) {
    func_ = func;
    args_ = args;
    getcontext(&context_);
    //设置context
    context_.uc_stack.ss_sp = stack_.Top();
    context_.uc_stack.ss_size = stack_.Size();
    context_.uc_stack.ss_flags = 0;
    //uc_link表示当coroutine结束的时候，应该resume的coroutine
    context_.uc_link = GetMainContext();

    //将this指针转换为uintptr_t
    uintptr_t ptr = (uintptr_t)this;
    makecontext(&context_, (void (*)(void))CoContextSys::CoFuncWrapper, 2, (uint32_t)ptr,
        (uint32_t)(ptr>>32));
  }

  bool CoContextSys::Resume() {
    swapcontext(GetMainContext(), &context_);
    return true;
  }

  bool CoContextSys::Yield() {
    swapcontext(&context_, GetMainContext());
    return true;
  }

  ucontext_t *CoContextSys::GetMainContext() {
    //
    static __thread ucontext_t main_context;
    return &main_context;
  }

  void CoContextSys::CoFuncWrapper(uint32_t low32, uint32_t high32) {
    uintptr_t ptr = (uintptr_t)low32 | ((uintptr_t)high32 << 32);
    CoContextSys *uc = (CoContextSys *)ptr;
    uc->func_(uc->args_);
    if (uc->callback_ != nullptr) {
      uc->callback_();
    }
  }
}
