#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include "CoContextRuntime.h"
#include "CoContextSys.h"

enum {
  COROUTINE_RUNNING,
  COROUTINE_SUSPEND,
  COROUTINE_DONE
};

namespace coroutine {
  CoContextRuntime::CoContextRuntime(size_t stack_size, const bool need_stack_protect)
    : stack_size_(stack_size), first_done_item_(-1), current_coroutine_(-1), unfinished_item_count_(0) {
      //Runtime构造函数已经确定底层系统，通过设置CoContext的create_func_，在以后调用CoContext::Create
      //时候接口统一
      if (CoContext::GetContextCreateFunc() == nullptr) {
        CoContext::SetContextCreateFunc(CoContextSys::DoCreate);
      }
    }

  CoContextRuntime::~CoContextRuntime() {
    for (auto &context_item : context_list_) {
      delete(context_item.context);
    }
  }

  int CoContextRuntime::Create(CoFunc_t func, void *args) {
    if (nullptr == func) {
      return -2;
    }
    int index = -1;
    //如果context_list_中有完成的ContextItem，则复用该Item
    //对应的index为first_done_item_，first_done_item会在coroutine的CoDoneCallback_t中设置
    if (first_done_item_ >= 0) {
    //利用first_done_item_和next_done_item可以完成所有空闲context的复用
      index = first_done_item_;
      first_done_item_ = context_list_[index].next_done_item;   //first_done_item_ = -1
      context_list_[index].context->Make(func, args);
    } else {
      index = context_list_.size();
      //这样做的好处是：在Runtime构造函数开始执行时，就已经确定了当前的系统，而不需要在这里特殊指定
      //CoContextSys::DoCreate()，从编程技巧上使得接口在不同运行时平台上得到了统一；
      auto new_context = CoContext::Create(stack_size_, func, args,
          std::bind(&CoContextRuntime::CoContextDoneCallback, this), need_stack_protect_);
      assert(new_context != nullptr);
      ContextItem context_item;
      context_item.context = new_context;
      context_list_.push_back(context_item);
    }

    context_list_[index].next_done_item = -1;
    context_list_[index].status = COROUTINE_SUSPEND;
    unfinished_item_count_++;
    return index;
  }

  void CoContextRuntime::CoContextDoneCallback() {
    if (-1 != current_coroutine_) {
      //这里与Create形成呼应，将已经完成的coroutine的ContextItem置位
      //设置next_done_item为first_done_item_;
      //设置first_done_item_为current_coroutine_;
      ContextItem &context_item = context_list_[current_coroutine_];
      context_item.next_done_item = first_done_item_;
      context_item.status = COROUTINE_DONE;
      first_done_item_ = current_coroutine_;
      unfinished_item_count_--;
      current_coroutine_ = -1;
    }
  }

  bool CoContextRuntime::Resume(size_t index) {
    if (index >= context_list_.size()) {
      return false;
    }

    // FIXME: auto &
    // auto context_item = context_list_[index]
    auto &context_item = context_list_[index];

    if (context_item.status == COROUTINE_SUSPEND) {
      current_coroutine_ = index;
      context_item.status = COROUTINE_RUNNING;
      context_item.context->Resume();
      return true;
    }

    return false;
  }

  bool CoContextRuntime::Yield() {
    if (-1 != current_coroutine_) {
      // FIXME: auto &
      // auto context_item = context_list_[index]
      auto &context_item = context_list_[current_coroutine_];
      current_coroutine_ = -1;
      context_item.status = COROUTINE_SUSPEND;
      context_item.context->Yield();
    }

    return true;
  }

  int CoContextRuntime::GetCurrentCoroutine() {
    return current_coroutine_;
  }

  bool CoContextRuntime::IsAllDone() {
    return unfinished_item_count_ == 0;
  }

  int CoContextRuntime::GetUnfinishedItemCount() const {
    return unfinished_item_count_;
  }

}
