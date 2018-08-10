#pragma once

#include <memory>
namespace coroutine {

#define ROUND(x, round) ((x) + ((round)-1)) & ~((round)-1)

  class CoStackMemory {
    public:
      CoStackMemory(const size_t stack_size, const bool need_protect = true);
      ~CoStackMemory();

      void *Top();
      size_t Size();

    private:
      void *raw_stack_;
      void *stack_;
      size_t stack_size_;
      int need_protect_;
    private:
      CoStackMemory(const CoStackMemory& par) {}
      void operator=(const CoStackMemory& par) {}
  };
}
