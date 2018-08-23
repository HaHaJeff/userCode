#ifndef THREADPOOLFUTURE_H
#define THREADPOOLFUTURE_H

#include <iostream>
#include <thread>
#include <condition_variable>
#include <algorithm>
#include <functional>
#include <atomic>
#include <queue>


class ThreadPool {
public:
  explicit ThredadPool(std::size_t threads = std::max(4u, std::thread::hardware_concurrency() * 2));

  template <class Func, class ...Args>
  auto AddTask(Func&& f, Args&&... args) -> typename std::result_of<Func(Args...)>::type;

  ~ThreadPool();

private:
  std::vector<std::thread> workers_;
  std::size_t pool_size_;
  std::queue<std::function<void()>> tasks_;
  std::size_t max_queue_size_ {100000};
  bool stop_{false};
};

template <class Func, class ...Args>
auto ThreadPool::AddTask(Func&& f, Args&&... args)
  -> std::future<typename std::result_of<Func(Args...)>::type>
{
  using return_type = typename std::result_of<Func(Args...)>::type;

  auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<Func>(f), std::forward<Args>(args)...));

  auto result = task.get_future();

  tasks_.emplace([task](){
      (*task)();   //std::function<void()>;
      });


  return result;
}

#endif
