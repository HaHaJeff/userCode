#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <thread>
#include <condition_variable>
#include <algorithm>
#include <functional>
#include <atomic>
#include <queue>

class ThreadPool {
public:
  explicit ThreadPool(std::size_t threads = (std::max)(4u, std::thread::hardware_concurrency() * 2));

 // template <class F, class... Args>
 // auto AddTask(F&& f, Args&&... args)-> typename std::result_of<F(Args...)>::type;

  template <class F, class... Args>
  void AddTask(F&& f, Args&&... args);

  ~ThreadPool();

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
  std::mutex mutex_;
  std::condition_variable condition_;
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
            while (!this->stop_ && tasks_.empty())
              condition_.wait(lock, [this]{ return this->stop_ || !tasks_.empty(); });

          //  if (true == stop_ || tasks_.empty()) return;
              if (stop_ && tasks_.empty()) {
                return;
              }

            //first in first out
            task = std::move(this->tasks_.front());
            this->tasks_.pop();

          //  if (this->tasks_.size() + 1 == max_queue_size_ || this->tasks_.empty())
          }
//          std::cout << "thread_id: " << std::this_thread::get_id() << std::endl;
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

  {
    std::unique_lock<std::mutex> lock(mutex_);

    while (tasks_.size() >= max_queue_size_) {
      condition_.wait(lock, [this]{ return tasks_.size() < max_queue_size_; });
    }

    tasks_.emplace([task]{task();});
  }

}

ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> lock(mutex_);
    stop_ = true;
  }
  condition_.notify_all();

  for (auto &worker: workers_)
    worker.join();
}

#endif
