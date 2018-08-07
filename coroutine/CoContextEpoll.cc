#include "CoContextEpoll.h"

#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>

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

  void EpollNotifier::Notify() {
    ssize_t write_len = write(pipe_fds_[1], (void *)"a", 1);
  }

  enum EpollREventStatus {
    EpollREvent_Timeout = 0,
    EpollREvent_Error = -1,
    EpollREvent_Close = -2,
  };

  EpollScheduler::EpollScheduler(size_t stack_size, int max_task, const bool need_stack_protect) :
    runtime_(stack_size, need_stack_protect), epoll_wake_up_(this) {
      max_task_ = max_task_ + 1;

      epoll_fd = epoll_create(max_task_);

      if (epoll_fd_ < 0) {
      }

      closed_ = false;
      run_forever_ = false;

      active_socket_func = nullptr;
      handler_accepted_fd_func = nullptr;
      handler_new_request_func = nullptr;

      epoll_wait_events_ = 0;
      epoll_wait_events_per_second_ = 0;
      epoll_wait_events_last_cal_time_ = Timer::GetSteadyClockMS();
    }

  EpollScheduler::~EpollScheduler() {
    close(epoll_fd_);
  }

  //单例，不需要考虑多线程安全问题
  EpollScheduler* EpollScheduler::Instance() {
    static EpollScheduler obj(64, 1024, 300);
    return &obj;
  }

  bool EpollScheduler::IsTaskFull() {
    return (runtime_.GetUnfinishedItemCount() + (int)to_list_.size()) >= max_task_;
  }

  void EpollScheduler::AddTask(CoFunc_t func, void *args) {
    todo_list_.push_back(std::make_pair(func, args));
  }

  void EpollScheduler::SetActiveSocketFunc(CoContextActiveSocket_t active_socket_func) {
    active_socket_func_ = active_socket_func;
  }

  void EpollScheduler::SetHandlerAcceptedFdFunc(CoContextHandlerAcceptedFdFunc_t handler_accepted_fd_func) {
    handler_accepted_fd_func_ = handler_accepted_fd_func;
  }

  void EpollScheduler::SetHandlerNewRequestFunc(CoContextHandlerNewRequest_t handler_new_request_func) {
    handler_new_request_func_ = handler_new_request_func;
  }

  bool EpollScheduler::YieldTask() {
    return runtime_.Yield();
  }

  int EpollScheduler::GetCurrentCoroutine() {
    return runtime_.GetCurrentCoroutine();
  }

  CoContextSocket_t* EpollScheduler::CreateSocket(const int fd, const int socket_timeout_ms,
      const int connect_timeout_ms, const bool no_delay = true) {
    int tmp = flag ? 1 : 0;

    fcntl(fd, F_SETFL, O_NONBLOCK);

    no_delay ? setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char*)&tmp, sizeof(tmp));

    socket->scheduler = this;
    socket->epoll_fd = epoll_fd_;
    socket->event.data.ptr = socket;

    socket->socket = fd;
    socket->connect_timeout_ms = connect_timeout_ms;
    socket->socket_timeout_ms =socket_timeout_ms;

    socket->waited_events = 0;
    socket->args = nullptr;

    return socket;
  }

  void EpollScheduler::ConsumeTodoList() {
    while(!todo_list_.empty()) {
      auto &it = todo_list_.front();
      int id = runtime_.Create(it.first, it.second);
      runtime_.Resume(id);

      todo_list_.pop();
    }
  }

  void EpollScheduler::Close() {
    closed_ = true;
  }

  void EpollScheduler::NotifyEpoll() {
    if (epoll_wait_events_per_second_ < 2000) {
      epoll_wake_up_.Notify();
    }
  }

  void EpollScheduler::ResumeAll(int flag) {
    std::vector<CoContextSocket_t*> exist_socket_list = timer_.GetSocketList();
    for (auto &socket : exist_socket_list) {
      socket->waited_events = flag;
      runtime_.Resume(socket->coroutine_id);
    }
  }

  void EpollScheduler::RunForever() {
    run_forever_ = true;
    epoll_wake_up_.Run();
    Run();
  }

  void EpollScheduler::StatEpollwaitEvents(const int event_count) {
    epoll_wait_events_ += event_count;
    auto now_time = Timer::GetSteadyClockMS();
    if (now_time > epoll_wait_events_last_cal_time_ + 1000) {
      epoll_wait_events_per_second_ = epoll_wait_events_;
      epoll_wait_events_ = 0;
      epoll_wait_events_last_cal_time_ = now_time;
    }
  }

  bool EpollScheduler::Run() {
    //必要之举，例如在epoll_wait之前需要要将lisentfd加入到epollfd
    ConsumeTodoList();

    struct epoll_event *events = (struct epoll_event*) calloc(max_task_, sizeof(struct epoll_event));

    int next_timeout = timer_.GetNextTimeout();

    for (; (run_forever_) || (!runtime_.IsAllDone());) {
      int nfds = epoll_wait(epoll_fd_, events, max_task_, 4);

      if (nfds != -1) {
        for (int i = 0; i < nfds; i++) {
          CoContextSocket_t *socket = (CoContextSocket_t*) events[i].data.ptr;
          socket->waited_events = events[i].events;

          runtime_.Resume(socket->coroutine_id);
        }

        if (active_socket_func_ != nullptr) {
          CoContextSocket_t *socket = nullptr;
          while ((socket = active_socket_func_()) != nullptr) {
            runtime_.Resume(socket->coroutine_id);
          }
        }

        if (handler_accepted_fd_func_ != nullptr) {
          handler_new_request_func_();
        }

        if (handler_new_request_func_ != nullptr) {
          handler_accpeted_fd_func_();
        }

        if (closed_) {
          ResumeAll(EpollREvent_Close);
          break;
        }

        //调度由于这一轮epoll_wait唤醒的协程添加的任务
        ConsumeTodoList();
        DealwithTimeout(next_timeout);
      } else if (errno != EINTR) {
        ResumeAll(EpollREvent_Error);
        break;
      }

      StatEpollwaitEvents(nfds);
    }

    free(events);

    return true;
  }

  void EpollScheduler::AddTimer(CoContextSocket_t *socket, const int timeout_ms) {
    RemoveTimer(socket->timer_id);

    if (timeout_ms == -1) {
      timer_.AddTimer(std::numeric_limits<uint64_t>::max(), socket);
    } else {
      timer_.AddTimer(Timer::GetSteadyClockMS() + timerout_ms, socket);
    }
  }

  void EpollScheduler::RemoveTimer(const size_t timer_id) {
    if (timer_id > 0) {
      timer_.RemoveTimer(timer_id);
    }
  }

  void EpollScheduler::DealwithTimeout(int &next_timeout) {
    while (true) {
      next_timeout = timer_.GetNextTimeout();

      if (0 != next_timeout) {
        break;
      }

      CoContextSocket_t *socket = timer_.PopTimeout();
      socket->waited_events = EpollREvent_Timeout;
      runtime_.Resume(socket->coroutine_id);
    }
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
