#ifndef THREADPOOL_H #define THREADPOOL_H

#include <iostream>
#include <thread>
#include <condition_variable>
#include <algorithm>
#include <functional>
#include <atomic>

class ThreadPool {
public:
  explicit ThreadPool(std::size_t threads = std::max(4, std::thread::hardware_concurrency() * 2));

 // template <class F, class... Args>
 // auto AddTask(F&& f, Args&&... args)-> typename std::result_of<F(Args...)>::type;

  template <class F, class... Args>
  void AddTask(F&& f, Args&&... args);

  void WaitAll();
  ~ThreadPoll();

private:
  // work thread
  std::vector<std::thread> workers_;
  // queue task
  std::queue<std::function<void()>> tasks_;
  // queue length limit
  std::size_t max_queue_size_ = 10000;
  // stop signal
  bool stop_ = false;

  // Sychronization
  std::mutext mutex_;
  std::condition_variable producers_;
  std::condition_variable consumers_;
};

inline ThreadPool::ThreadPool(std::size_t threads) {
  for (size_t i = 0; i < threads; ++i) {
    workers_.emplace_back(
        [this]
        {
        while(true) {
          std::function<void()> task;
          {
            std::unique_lock<std::mutex> lock(this->mutex_);

            //avoid spurious wakeup
            while (tasks_.empty())
              consumers_.wait(lock, []{ return !tasks_.empty(); });

            if (true == stop || tasks_.empty()) return;

            //first in first out
            task = std::move(this->tasks_.front());
            this->tasks_.pop();

          //  if (this->tasks_.size() + 1 == max_queue_size_ || this->tasks_.empty())
          }
          task();
        }
        }
        );
  }
}

template <class F, class ...Args>
void ThreadPool::AddTask(F&& f, Args&&... args) {
  using return_type = typename std::result_of<F(Args...)>::type;
  auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

  std::unique_lock<std::mutex> lock(mutex_);

  while (tasks_.size() >= max_queue_size_) {
    producers_.wait(lock, []{ return tasks_.size() < max_queue_size_; });
  }

  tasks_.emplace([task]{task();});

}

ThreadPool::~ThreadPool() {
  std::unique_lock<std::mutex> lock(mutex_);
  stop_ = true;
  condition_consumers_.notify_all();
  condition_producers_.notify_all();

  condition_consumers_.wait(lock, [this]{ return this->workers_.empty(); });
}

void ThreadPool::WaitAll() {
  std::unique_lock<std::mutex> lock(this->mutex_);
  this->condition_producers_.wait(lock, [this]{ return this->tasks_.empty() };);
}

#endif
