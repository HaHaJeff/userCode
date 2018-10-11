#include "channel.h"
#include <poll.h>

int main() {
    Channel ch(nullptr, 0);
    ch.SetREvents(POLLNVAL);
    ch.HandleEvent();
}