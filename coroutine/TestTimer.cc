#include "CoContextEpoll.h"
#include "Timer.h"

using namespace coroutine;
int main()
{
  Timer timer;
  CoContextSocket *socket = NewCoContextSocket();
  timer.AddTimer(0, socket);

  timer.RemoveTimer(1);
}
