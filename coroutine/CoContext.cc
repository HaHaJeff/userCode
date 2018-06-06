#include "CoContext.h"

namespace coroutine {

CoContextCreateFunc_t CoContext::context_create_func_ = nullptr;

// 使用静态函数完成create_func_的设置，从而是的在CoContextRuntime类中可以完成具体DoCreate的绑定，相对
// 继承来说，此方法更好；
CoContext *CoContext::Create(size_t stack_size, CoFunc_t func,
    void *args, CoDoneCallback_t callback, const bool need_stack_protect) {
  if (context_create_func_ != nullptr) {
    return context_create_func_(stack_size, func, args, callback, need_stack_protect);
  }

  return nullptr;
}

void CoContext::SetContextCreateFunc(CoContextCreateFunc_t context_create_func) {
  context_create_func_ = context_create_func;
}

CoContextCreateFunc_t CoContext::GetContextCreateFunc() {
  return context_create_func_;
}

}
