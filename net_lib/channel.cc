#include <poll.h>
#include <atomic>
#include <assert.h>

#include "channel.h"
#include "eventloop.h"

// POLLPRI: urgent data to read
// POLLNVAL: invalid request, fd not open
// POLLERR: error condition
// POLLRDHUP:  stream socket peer connection close, or shutdown writing of half connection
// POLLHUP: fd is valid, however, a device disconnect
const int Channel::kNoneEvent = 0;
const int Channel::kWriteEvent = POLLOUT;
const int Channel::kReadEvent = POLLIN | POLLPRI;

Channel::Channel(EventLoop* loop, int fd) 
    : loop_(loop),
      fd_(fd),
      events_(0),
      revents_(0),
      id_(-1),
      addedToThisLoop_(false)
{
    static std::atomic<int64_t> id(0);
    id_ = ++id;
}


Channel::~Channel() {
    assert(!addedToThisLoop_);
}

// response event change from loop_
// EventLoop will change the channel's revents_
void Channel::HandleEvent() {
   TRACE(REventsToString().c_str());
   // handle POLLHUP event
   if ((revents_ & POLLHUP) && !(revents_ & POLLIN)) {
       WARN("channel id =%d, fd = %d, Channel::HandleEvent() POLLHUP", id_, fd_);
       if (closeCallback_) closeCallback_();
   }
   if (revents_ & POLLNVAL) {
       WARN("channel id = %d, fd = %d, Channel::HandleEvent() POLLNVAL", id_, fd_);
   }
   if (revents_ & (POLLERR | POLLNVAL)) {
       if (errorCallback_) errorCallback_();
   }
   if (revents_ & (POLLIN | POLLPRI | POLLRDHUP)) {
       if (readCallback_) readCallback_();
   }
   if (revents_ & POLLOUT) {
       if (writeCallback_) writeCallback_();
   }
}

void Channel::Update() {
    addedToThisLoop_ = true;
    loop_->UpdateChannel(this);
}

// before call this function, should call Disable
void Channel::Remove() {
    assert(IsNoneEvent());
    addedToThisLoop_ = false;
    loop_->UpdateChannel(this);
}

std::string Channel::REventsToString() const {
    return EventsToString(fd_, revents_);
}

std::string Channel::EventsToString()  const {
    return EventsToString(fd_, events_);
}

std::string Channel::EventsToString(int fd, short ev) const {
    std::string result = Util::Format("channel id = %d, fd = %d", id_, fd);
    if (ev & POLLIN) result += "IN ";
    if (ev & POLLPRI) result += "PRI ";  // urgent data
    if (ev & POLLOUT) result += "OUT ";
    if (ev & POLLHUP) result += "HUP";
    if (ev & POLLRDHUP) result += "RDHUP";
    if (ev & POLLERR) result += "ERR";
    if (ev & POLLNVAL) result += "NVAL";
    return result;
}