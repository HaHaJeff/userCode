#include "CoContextEpoll.h"
#include <cstdlib>
typedef struct CoContextSocket {
    size_t timer_id;
} CoContextSocket_t;

void CoContextSocketSetTimerID(CoContextSocket_t &socket, size_t timer_id) {
    socket.timer_id = timer_id;
}

//memory should free by user
CoContextSocket_t* NewCoContextSocket() {
  //allocate an array, and set memory to zero
  CoContextSocket_t *socket = (CoContextSocket_t*)calloc(1, sizeof(CoContextSocket_t));
  return socket;
}
