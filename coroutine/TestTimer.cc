#include "CoContextEpoll.h"
#include "Timer.h"

int main()
{
  Timer timer;
  CoContextSocket_t *socket = NewCoContextSocket();
  timer.AddTimer(0, socket);

  timer.RemoveTimer(1);
}
