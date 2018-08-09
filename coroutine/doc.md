## Coroutine
### 定义
协程是一种用户态的轻量级线程，协程的调度完全由用户控制。协程拥有自己的寄存器上下文和栈。协程调度切换时，将寄存器上下文和栈保存到其他地方，在切回来的时候，恢复先前保存的寄存器上下围和栈，直接操作栈则基本没有内核切换的开销，可以不加锁的访问全局变量，所以上下文的切换非常快。

### 为什么需要进程？
对于单核CPU，串行跑程序没有问题，但是一块跑就会出现问题。例如一个求解方程的程序正在运行，突然一个其他的程序插了进来，我的中间状态怎么办？所以在一个cpu里面的并发都需要处理上下文切换的问题。进程就是这样抽象出来的一个概念，搭配虚拟内存、进程表之类的东西，用来管理独立的程序运行、切换。后来一台电脑上有了好几个cpu，就出现了所谓的并行。

**因为程序的使用涉及大量的计算资源配置，把这活随意的交给用户程序，非常容易让整个系统分分钟被搞跪，资源分配也很难做到相对的公平。所有核心的操作需要陷入内核，切换到操作系统，让老大帮你来做。**

###为什么需要线程？
有时候碰着IO访问，阻塞了后面的计算。空着也是空着，老大就直接把CPU切换到其他进程，让人家先用着。当然了除了IO阻塞，还有时间阻塞等等。但是如果进程多了，那么切换的开销就会很大，因为一切换进程得反复进入内核，置换掉一大堆状态。后来出现了线程的概念，大致意思就是，这个地方阻塞了，但我还有其他地方的逻辑流可以计算，这些逻辑流是共享一个地址空间的，不用特别麻烦的切换页表、刷新TLB。

###为什么需要协程？
如果连时钟阻塞、线程切换这些功能都不需要了，自己在进程里面写一个逻辑流调度的东西。那么我们既可以利用并发优势，又可以避免反复系统调用，还有进程切换造成的开销，分分钟给你上几千个逻辑流不费力。这就是用户态线程。

**实现一个用户态线程有两个必须要处理的问题：1. 碰着阻塞式IO会导致整个进程被挂起；2. 由于缺乏时钟阻塞，进程需要自己拥有调度线程的能力。如果一种实现使得每个线程需要自己通过某个方法，主动交出控制权。那么我们就称这种用户态线程为协作式的，即是协程。**

##CoContext的实现
使用ucontext_t类型完成协程上下文的制作
- Makecontext完成上下文的制作
- swapcontext完成切换
- getcontext得到当前的活动上下文
- setcontext(ucp)将ucp设置为当前的上下文。

### CoContext类
抽象类，
- Virtual void Make(CoFunc_t func, void* args) = 0;
- Virtual bool Resume() = 0;
- Virtual bool Yield() = 0;
上述三个函数将有子类定制。不同操作系统可能需要不同的方法实现；

```
static CoContext *Create(size_t stack_size, CoFunc_t func, void* args, CoDoneCallback_t callback, const bool need_stack_protect)
{ 
	context_create_func_(stack_size, func, args, callback, need_stack_protect);
}
static void SetContextCreateFunc(CoContextCreateFunc_t context_create_func)
{
	context_create_func_ = context_create_func;
}
static CoContextCreateFunc_t GetContextCreateFunc()
{
	return context_create_func_;
}
```

### CoContextSys类
**public CoContext**
该类需要完成协程栈的制作
```
//作为CoContext的context_func_t函数执行体
static CoContext* DoCreate(size_t stack_size, CoFunc_t func, void* args, CoDoneCallback_t callback, const bool need_stack_protect);
```

###CoContextRuntime


