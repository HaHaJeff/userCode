#include <stdlib.h>
template<class T>
RCPtr<T>::RCPtr(T* realptr): ptr_(realptr) {
  init();
}

template<class T>
RCPtr<T>::RCPtr(const RCPtr<T>& rhs): ptr_(rhs.ptr_) {
  init();
}

template<class T>
RCPtr<T>::~RCPtr() {
  if (ptr_ != NULL) {
    ptr_->RemoveReference();
  }
}

template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr<T>& rhs) {
  if (ptr_ != rhs.ptr_) {
    if (ptr_ != NULL) {
      ptr_->RemoveReference();
    }
    ptr_ = rhs.ptr_;
    init();
  }
  return *this;
}

template<class T>
T* RCPtr<T>::operator->() const {
  return ptr_;
}

template<class T>
T& RCPtr<T>::operator*() const {
  return *ptr_;
}

template<class T>
void RCPtr<T>::init() {
  if (ptr_ == NULL) return;
  if (!ptr_->IsShareable()) {
    ptr_ = new T(*ptr_);
  }

  ptr_->AddReference();
}
