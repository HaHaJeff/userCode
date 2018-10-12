#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>
#include <memory>
#include <stdint.h>

#include "util.h"
#include "log.h"

class EventLoop;

// chanenel不拥有fd
class Channel : public Noncopyable {
public:
    typedef std::function<void()> EventCallback;

    Channel(EventLoop* loop, int fd);
    ~Channel();

    void SetReadCallback(const EventCallback& cb) { readCallback_ = cb;}
    void SetWriteCallback(const EventCallback& cb) { writeCallback_ = cb;}
    void SetCloseCallback(const EventCallback& cb) { closeCallback_ = cb;}
    void SetErrorCallback(const EventCallback& cb) { errorCallback_ = cb;}
    void SetReadCallback(EventCallback&& cb) { readCallback_ = std::move(cb);}
    void SetWriteCallback(EventCallback&& cb) { writeCallback_ = std::move(cb);}
    void SetCloseCallback(EventCallback&& cb) { closeCallback_ = std::move(cb);}
    void SetErrorCallback(EventCallback&& cb) { errorCallback_ = std::move(cb);}
    
    void EnableRead() { events_ |= kReadEvent; Update(); }
    void DisableRead() { events_ &= ~kReadEvent; Update(); }
    void EnableWrite() { events_ |= kWriteEvent; Update(); }
    void DisableWrite() { events_ &= ~kWriteEvent; Update(); }
    void DisableAll() { events_ = kNoneEvent; Update(); }
    bool IsWriting() const { return events_ & kWriteEvent; }
    bool IsReading() const { return events_ & kReadEvent; }
    bool IsNoneEvent() const { return events_ == kNoneEvent; }

    short GetEvents() const { return events_; }
    int GetFd() const { return fd_; }
    int64_t GetId() const { return id_; }
    short GetREvents() const { return revents_; }
    //loop_ will call this function
    void SetREvents(short revents) { revents_ = revents; }

    EventLoop* GetOwnerLoop() const { return loop_; }

    void HandleEvent();
    void Remove();

    // DEBUG
    std::string REventsToString() const;
    std::string EventsToString() const;

private:
    std::string EventsToString(int fd, short ev) const;
    void Update();

private:
    EventLoop* loop_;
    short events_;
    short revents_;
    const int fd_;
    int64_t id_;
    bool addedToThisLoop_;

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;
};

#endif