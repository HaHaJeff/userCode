#pragma once

#include <stdlib.h>
#include <vector>
#include <functional>
#include "CoContext.h"

namespace coroutine {

  //coroutine运行时环境，用于保存coroutine上下问
  //使用vector对coroutine上下文件进行保存，如果vector中有coroutine运行完毕，还可以复用该vector的slot
  class CoContextRuntime {
    public:
      CoContextRuntime(size_t stack_size, const bool need_stack_protect);
      ~CoContextRuntime();

      int Create(CoFunc_t func, void *args);
      int GetCurrentCoroutine();
      bool Yield();
      bool Resume(size_t index);
      bool IsAllDone();
      int GetUnfinishedItemCount() const;

      void CoContextDoneCallback();

    private:
      //coroutine运行时上下文
      struct ContextItem {
        ContextItem() {
          context = nullptr;
          next_done_item = -1;
        }
        CoContext *context;
        int next_done_item;
        int status;
      };

      //first_done_item和ContextItem_中的next_done_item形成了空闲ContextItem的下标索引链表
      //使用first_done_item和ContextItem_中的next_done_item构成栈Stack
      size_t stack_size_;                         //coroutine的stack大小
      std::vector<ContextItem> context_list_;     //保存coroutine的运行时上下文
      int first_done_item_;
      int current_coroutine_;
      int unfinished_item_count_;
      bool need_stack_protect_;
  };

}
