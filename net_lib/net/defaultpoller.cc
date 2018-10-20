#include "poller.h"
#include "epollpoller.h"

Poller* Poller::NewDefaultPoller(EventLoop* loop) {
    return new EpollPoller(loop);
}