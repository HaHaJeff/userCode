
# 参照muduo和handy
### channel
channel作为poller调度的基本单位，是网络编程中必不可少的一环。负责注册与相应IO事件。handy和muduo在该方面都有自己的实现，两者的实现方式类似，都是将EventBase(handy+PollerBase，EventLoop-muduo)作为channel成员变量，在channel构造的时候直接将this添加到EventBase(EventLoop中)
**在handy中，channel析构自动关闭其负责的fd；在muduo中，channel不负责fd的关闭，而是由更高层的TcpConnect等负责,TcpConect通过设置回调从而在EventLoopi(EventPoller)中自动调用该函数，从而将fd关闭,需要自己调用TcpConnect提供的关闭函数**

### Poller
Poller是IO multiplexing的封装，负责管理channel的活动,需要一个容器管理channel**libevent将poller作为基类，后端分别对应不同平台实现同的多路复用结构**

### EventLoop
封装事件循环，也是事件分派的中心。使用Poller作为IO Multiplexing

- util

一些基础功能，例如时间相关，以及字符串转换成int
