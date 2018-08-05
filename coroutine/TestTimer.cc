#include "CoContextEpoll.h"
#include "Timer.h"

int main()
{
  Timer timer;
  CoContextSocket_t *socket = new CoContextSocket_t;
  timer.AddTimer(0, socket);

  timer.RemoveTimer(1);
}
