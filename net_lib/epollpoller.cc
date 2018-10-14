#include <sys/epoll.h>
#include <assert.h>
#include <poll.h>
#include <unistd.h>

#include "log.h"
#include "epollpoller.h"

EpollPoller::EpollPoller(EventLoop* loop)
    : Poller(loop),
      epollfd_(epoll_create1(EPOLL_CLOEXEC)),
      events_(kInitEventListSize)
{
    FATALIF(epollfd_ < 0, "EPollPoller::EpollPoller");
}

EpollPoller::~EpollPoller() {
    close(epollfd_);
}

TimeStamp EpollPoller::Poll(int timeoutMs, ChannelList* activeChannels) {
    TRACE("fd total count %d", channels_.size());

    int numEvents = epoll_wait(epollfd_, &*(events_.begin()), static_cast<int>(events_.size()), timeoutMs);
    TimeStamp now(TimeStamp::Now());

    if (numEvents > 0) {
        TRACE("%d events happend", numEvents);
        FillActiveChannels(numEvents, activeChannels);

        //如果发现一次epoll_wait返回的数值与当前events_可以容纳的事件数目相等，
        //说明此时网络事件比较活跃，扩容
        if (static_cast<size_t>(numEvents) == events_.size()) {
            events_.resize(events_.size()*2);
        }
    } else if (numEvents == 0) {
        TRACE("nothing happend");
    } else {
        FATALIF(errno != EINTR, "Epoller::Poll()");
    }

    return now;
}

