#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include <functional>
class Channel;
class EventLoop {
public:
    typedef std::function<void()> Functor;
    void UpdateChannel(Channel* ch) {}
    void RemoveChannel(Channel* ch) {}
    void AddChannel(Channel* ch) {}
    void RunInLoop(const Functor& func) { }
    void RunInrLoop(Functor&& func) { }
    bool AssertInLoopThread() {}
};

#endif