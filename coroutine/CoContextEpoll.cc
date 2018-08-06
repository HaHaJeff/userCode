#include "CoContextEpoll.h"

#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

namespace coroutine
{
typedef struct CoContextSocket
{
    EpollScheduler *scheduler;
    int coroutine_id;

    int epoll_fd;

    int socket;
    int connect_timeout_ms;
    int socket_timeout_ms;

    int waited_events;
    size_t timer_id;
    struct epoll_event event;
    void *args;
} CoContextSocket_t;

EpollNotify::EpollNotify(EpollScheduler *scheduler) : scheduler_(scheduler)
{
    pipe_fds_[0] = pipe_fds_[1] = -1;
}

EpollNotify::~EpollNotify()
{
    if (pipe_fds_[0] != -1)
    {
        close(pipe_fds_[0]);
    }
    if (pipe_fds_[1] != -1)
    {
        close(pipe_fds_[1]);
    }
}

//将Func作为一个协程运行
void EpollNotifier::Run()
{
    fcntl(pipe_fds_[1], F_SETFL, O_NONBLOCK);
    scheduler_->AddTask(std::bind(&EpollNotifier::Func, this), nullptr)
}

void EpollNotifier::Func()
{
    CoContextSocket_t *socket{scheduler_->CreateSocket(pipe_fds_[0], -1, -1, false)};
    char tmp[2] = {0};
    while (true)
    {
        if (CoContextRead(*socket, tmp, 1, 0) < 0)
        {
            break;
        }
    }
    free(socket);
}

void CoContextSocketSetTimerID(CoContextSocket_t &socket, size_t timer_id)
{
    socket.timer_id = timer_id;
}

//memory should free by user
CoContextSocket_t *NewCoContextSocket()
{
    //allocate an array, and set memory to zero
    CoContextSocket_t *socket = (CoContextSocket_t *)calloc(1, sizeof(CoContextSocket_t));
    return socket;
}
} // namespace coroutine
