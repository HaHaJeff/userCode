#include "timerqueue.h"
#include "eventloop.h"
#include "timer.h"
#include <iostream>
int main()
{
    EventLoop* loop = new EventLoop();
    TimerQueue queue(loop);
    Timer *timer = new Timer([=]{std::cout << "Timer" << std::endl;}, TimeStamp(TimeStamp::Now()), 0.0);
    queue.AddTimerInLoop(timer);
    queue.HandleRead();

}