#pragma once
#include <cstddef>

//typedef struct CoContextSocket CoContextSocket_t;

typedef struct CoContextSocket {
    size_t timer_id;
} CoContextSocket_t;

void CoContextSocketSetTimerID(CoContextSocket_t &socket, size_t timer_id);
