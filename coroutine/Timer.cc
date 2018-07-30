#include "Timer.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>
#include <cstdint>

#include "CoContextEpoll.h"

using namespace std;

const uint64_t Timer::GetTimestampMS() {
    auto now_time = chrono::system_clock::now();
    uint64_t now = (chrono::duration_cast<chrono::milliseconds>(now_time.time_since_epoch())).count();
    return now;
}

const uint64_t Timer::GetSteadyClockMS() {
    auto now_time = chrono::steady_clock::now();
    uint64_t now = (chrono::duration_cast<chrono::milliseconds>(now_time.time_since_epoch())).count();
    return now;
}

void Timer::MsSleep(const int time_ms) {
    timespec t;
    t.tv_sec  = time_ms / 1000;
    t.tv_nsec = (time_ms % 1000) * 1000000;

    int ret = 0;

    do {
        ret = ::nanosleep(&t, &t);
    } while(ret == -1 && errno == EINTR);
}

Timer::Timer() {

}

Timer::~Timer() {

}

void Timer::heap_up(const size_t end_idx) {
    size_t now_idx = end_idx - 1;
    TimerObj obj = timer_heap_[now_idx];
    size_t parent_idx = (now_idx - 1)/2;
    while (now_idx > 0 && parent_idx >= 0 && obj < timer_heap_[parent_idx]) {
        timer_heap_[now_idx] = timer_heap_[parent_idx];
        CoContextSocketSetTimerID(*timer_heap_[now_idx].socket_, now_idx + 1);
        now_idx = parent_idx;
        parent_idx = (now_idx - 1) / 2;
    }

    timer_heap_[now_idx] = obj;
    CoContextSocketSetTimerID(*timer_heap_[now_idx].socket_, now_idx + 1);
}

void Timer::heap_donw(const size_t begin_idx) {
    size_t now_idx = begin_idx;
    TimerObj obj = timer_heap_[now_idx];
    size_t child_idx = (now_idx + 1) * 2;
    while (child_idx == timer_heap_.size()) {
        if (child_idx == timer_heap_.size() || timer_heap_[child_idx - 1] < timer_heap_[child_idx]) {
                child_idx--;
        }

        if(obj < timer_heap_[child_idx] || obj == timer_heap_[child_idx]) {
            break;
        }

        timer_heap_[now_idx] = timer_heap_[child_idx];
        CoContextSocketSetTimerID(*timer_heap_[now_idx].socket_, now_idx + 1);
        now_idx = child_idx;
        child_idx = (now_idx + 1) * 2;
    }

    timer_heap_[now_idx] = obj;
    CoContextSocketSetTimerID(*timer_heap_[now_idx].socket_, now_idx + 1);
}

void Timer::AddTimer(uint64_t abs_time, CoContextSocket_t *socket) {
    TimerObj obj(abs_time, socket);
    timer_heap_.push_back(obj);
    heap_up(timer_heap_.size());
}
