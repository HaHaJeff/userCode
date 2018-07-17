#ifndef RCPTR_H
#define RCPTR_H

template<class T>
class RCPtr {
  public:
    RCPtr(T* realPtr = 0);
    RCPtr(const RCPtr& rhs);
    ~RCPtr();

    RCPtr& operator=(const RCPtr& rhs);

    T* operator->() const;
    T& operator*() const;

  private:
    T *ptr_;
  private:
    void init();
};

#include "rcptr_i.cc"

#endif
