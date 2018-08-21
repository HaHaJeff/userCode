#include "CoContextUtil.h"
#include <sys/mman.h>
#include <unistd.h>
#include <assert.h>

namespace coroutine {
  CoStackMemory::CoStackMemory(const size_t stack_size, const bool need_protect) :
    raw_stack_(nullptr), stack_(nullptr), need_protect_(need_protect) {
      int page_size = getpagesize();

      //对齐到page_size
      stack_size_ = ROUND(stack_size, page_size-1);

      //如果需要对stakc进行保护，则采取多映射2page的方案，类似于linux内核在飞连续内存区域的管理
      //在线性内存映射与vmalloc区之间增加8MB进行隔离，在每个vmalloc区之间增加4KB进行隔离，我在这
      //里增加page_size进行隔离,前后都需要增加page，所以增加2*page
      raw_stack_ = mmap(NULL, stack_size_ + page_size * (need_protect ? 2 : 0),
          PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
      assert(raw_stack_ != nullptr);
      //mprotect(addr, len, PROT) 保护[addr, addr+len-1]
      assert(!need_protect || (mprotect(raw_stack_, page_size, PROT_NONE) == 0 &&
            mprotect((void*)((char*)raw_stack_+stack_size_+page_size), page_size, PROT_NONE) == 0));
      stack_ = (void*)((char*)raw_stack_ + page_size * (need_protect ? 1 : 0));
    }

  CoStackMemory::~CoStackMemory() {
    int page_size = getpagesize();

    assert(!need_protect_ || (mprotect(raw_stack_, page_size, PROT_NONE) == 0 &&
          mprotect((void*)((char*)raw_stack_+stack_size_+page_size), page_size, PROT_NONE) == 0));
    assert(munmap(raw_stack_, stack_size_ + page_size * (need_protect_ ? 2 : 0)) == 0);
  }

  void *CoStackMemory::Top() {
    return stack_;
  }

  size_t CoStackMemory::Size() {
    return stack_size_;
  }
}
