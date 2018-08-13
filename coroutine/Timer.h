#pragma once

#include <cinttypes>
#include <cstdlib>
#include <vector>
#include <cstdint>

namespace coroutine {

typedef struct CoContextSocket CoContextSocket_t;

class Timer {
public:
    Timer();
    ~Timer();

    void AddTimer(uint64_t abs_time, CoContextSocket_t *socket);
    void RemoveTimer(const size_t timer_id);
    CoContextSocket_t* PopTimeout();
    const int GetNextTimeout() const;
    const bool IsEmpty();
    static const uint64_t GetTimestampMS();
    static const uint64_t GetSteadyClockMS();
    static void MsSleep(const int time_ms);
    std::vector<CoContextSocket_t *> GetSocketList();

private:
    void heap_up(const size_t end_idx);
    void heap_down(const size_t begin_idx);

    struct TimerObj {
        TimerObj(uint64_t abs_time, CoContextSocket_t *socket)
            : abs_time_(abs_time), socket_(socket) {

            }
        uint64_t abs_time_;
        CoContextSocket_t *socket_;

        bool operator <(const TimerObj& obj) const {
            return abs_time_ < obj.abs_time_;
        }

        bool operator ==(const TimerObj& obj) const {
            return abs_time_ == obj.abs_time_;
        }
    };
    std::vector<TimerObj> timer_heap_;
};

}
