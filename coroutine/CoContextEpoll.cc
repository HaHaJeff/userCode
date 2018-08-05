#include "CoContextEpoll.h"

/*
typedef struct CoContextSocket {
    size_t timer_id;
} CoContextSocket_t;
*/
void CoContextSocketSetTimerID(CoContextSocket_t &socket, size_t timer_id) {
    socket.timer_id = timer_id;
}
