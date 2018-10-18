#include "eventloop.h"
#include "log.h"
#include "timer.h"

#include <iostream>

int main()
{
    Logger& log = Logger::GetLogger();
    log.SetFileName("event.log");
    EventLoop loop;

    int i = 0;
    while (i < 100) {
        loop.RunAfter(1.0, [i]
            {
            std::cout << "RunAfter: "  << i << std::endl;
            }
            );
        i+=1;
    } 

    loop.Loop();    
}
