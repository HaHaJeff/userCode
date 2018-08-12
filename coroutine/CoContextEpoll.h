#pragma once

#include <cstddef>
#include <queue>
#include <utility>
#include <arpa/inet.h>

#include "CoContextRuntime.h"

#include "Timer.h"

namespace coroutine
{

  struct CoContextSocket;

  class EpollScheduler;

  typedef std::pair<EpollScheduler *, int> EpollArgs_t;
  typedef std::function<CoContextSocket *()> CoContextActiveSocket_t;
  typedef std::function<void()> CoContextHandlerAcceptedFdFunc_t;
  typedef std::function<void()> CoContextHandlerNewRequest_t;


  //EpollScheduler run forever, EpollNotify is used to close EpollScheduler
  //通过pipe_fd机制来结束Run的while(true)
  class EpollNotifier final
  {
    public:
      EpollNotifier(EpollScheduler *scheduler);
      ~EpollNotifier();

      void Run();
      void Func();
      void Notify();

    private:
      EpollScheduler *scheduler_{nullptr};
      int pipe_fds_[2];
  };

  class EpollScheduler final
  {
    public:
      EpollScheduler(size_t stack_size, int max_task, const bool need_stack_protect = true);
      ~EpollScheduler();

      static EpollScheduler *Instance();

      bool IsTaskFull();

      void AddTask(CoFunc_t func, void *args);

      CoContextSocket *CreateSocket(const int fd, const int socket_timeout_ms = 5000, const int connect_timeout_ms = 200, const bool no_delay = true);

      void SetActiveSocketFunc(CoContextActiveSocket_t active_socket_func);
      void SetHandlerAcceptedFdFunc(CoContextHandlerAcceptedFdFunc_t handler_accepted_fd_func);
      void SetHandlerNewRequestFunc(CoContextHandlerNewRequest_t handler_new_request_func);

      bool YieldTask();
      bool Run();
      void RunForever();
      void Close();
      void NotifyEpoll();

      int GetCurrentCoroutine();

      void AddTimer(CoContextSocket *socket, const int timeout_ms);
      void RemoveTimer(const size_t timer_id);
      void DealwithTimeout(int &next_timeout);

    private:
      typedef std::queue<std::pair<CoFunc_t, void *>> TaskQueue_t;

      void ConsumeTodoList();
      void ResumeAll(int flag);
      void StatEpollwaitEvents(const int event_count);

      CoContextRuntime runtime_;
      int max_task_;
      TaskQueue_t todo_list_;
      int epoll_fd_;

      Timer timer_;
      bool closed_{false};
      bool run_forever_{false};

      CoContextActiveSocket_t active_socket_func_;
      CoContextHandlerAcceptedFdFunc_t handler_accepted_fd_func_;
      CoContextHandlerNewRequest_t handler_new_request_func_;

      int epoll_wait_events_;
      int epoll_wait_events_per_second_;
      uint64_t epoll_wait_events_last_cal_time_;

      EpollNotifier epoll_wake_up_;
  };

  int CoContextPoll(CoContextSocket &socket, int events, int *revents, const int timeout_ms);

  int CoContextConnect(CoContextSocket &socket, const struct sockaddr *addr, socklen_t *addrlen);

  int CoContextAccept(CoContextSocket &socket, struct sockaddr *addr, socklen_t *addrlen);

  ssize_t CoContextRecv(CoContextSocket &socket, void *buf, size_t len, const int flags);

  ssize_t CoContextRead(CoContextSocket &socket, void *buf, size_t len, const int flags);

  ssize_t CoContextSend(CoContextSocket &socket, const void *buf, size_t len, const int flags);

  int CoContextClose(CoContextSocket &socket);

  void CoContextSetConnectTimeout(CoContextSocket &socket, const int connect_timeout_ms);

  void CoContextSetSocketTimeout(CoContextSocket &socket, const int socket_timeout_ms);

  int CoContextSocketFd(CoContextSocket &socket);

  void CoContextSocketSetTimerID(CoContextSocket &socket, size_t timer_id);

  size_t CoContextSocketTimerID(CoContextSocket &socket);

  void CoContextSocketSetTimerID(CoContextSocket &socket, size_t timer_id);

  CoContextSocket *NewCoContextSocket();

  void CoContextSetArgs(CoContextSocket &socket, void *args);

  void* CoContextGetArgs(CoContextSocket &socket);

  void CoContextWait(CoContextSocket &socket);

  void CoContextLazyDestory(CoContextSocket &socket);

  bool IsCoContextDestory(CoContextSocket &socket);

} // namespace coroutine
