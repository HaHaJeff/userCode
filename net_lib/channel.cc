#include <poll.h>
#include <atomic>

#include "channel.h"

// POLLPRI: urgent data to read
const int Channel::kNoneEvent = 0;
const int Channel::kWriteEvent = POLLOUT;
const int Channel::kReadEvent = POLLIN | POLLPRI;

Channel::Channel(EventLoop* loop, int fd) 
    : loop_(loop),
      fd_(fd),
      events_(0),
      id_(-1)
{
    static std::atomic<int64_t> id(0);
    id_ = ++id;
}


void Channel::HandleEvent() {
}

void Channel::Update() {
}

void Channel::Remove() {

}