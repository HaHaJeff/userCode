#include "daemon.h"
#include <iostream>

int main()
{
    std::string pidfile("daemon");
    int ret = Daemon::DaemonStart(pidfile.c_str());
    while(1);
}
