#include "CoContext.h"

namespace coroutine {

CoContextCreateFunc_t CoContext::context_create_func_ = nullptr;

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
