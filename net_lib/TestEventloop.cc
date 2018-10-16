#include "eventloop.h"
#include "log.h"
#include "timer.h"

#include <iostream>

int main()
{
    Logger& log = Logger::GetLogger();
    log.SetFileName("event.log");
    EventLoop loop;

    loop.RunAfter(1.0, [=]{std::cout << "RunAfter" << std::endl;});
    loop.Loop();    
}