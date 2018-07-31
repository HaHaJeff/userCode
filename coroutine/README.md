各个文件的概览：
## CoContext.h 
- 提供一个统一的接口

## CoContextSys.h
- 具体操作系统对应的协程context，使用swapcontext,getcontext,makecontext完成协程上下文的切换与定义

## CoUtil.h
- 定义协程的stack，在堆上进行分配，用于保存协程的现场；
- 目前stack可选是否开启保护模式，采用mprotect进行保护，默认采用4mb gap进行填充保护区；

## CoContextRuntime.h
- 提供协程的统一调度接口，采用vector对协程进行保存；
- 对已经运行完毕的协程，不删除其空间，通过对空闲协程以类似链表的方式组织起来，可以完成协程的复用；
- 在RunTime类初始化时完成底层Context create函数的确定，在实现中采用CoContextSys::DoCreate作为CoContext::Create函数的回调函数，DoCreate以及Create是静态函数。

## Timer.h
- 使用小根堆完成时间node的管理;
- 使用vector作为底层存储容器，因为vector提供了O(1)的时间复杂度完成随机访问。

## TODO
- 对协程的具体调度，如通过IO多路复用模型管理协程，phxrpc是通过"poll"完成协程的切换，如对read操作，fd为非阻塞，在没有数据到来前，将其加入到epoll中
统一管理，于此同时完成协程的切换；(为什么一定要是非阻塞文件描述符？ **如果是阻塞文件描述符，则操作将会一直阻塞**)
