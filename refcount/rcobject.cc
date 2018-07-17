#include "rcobject.h"

RCObject::RCObject() : refCount_(0), shareable_(this){
}

RCObject::RCObject(const RCObject& rhs) : refCount_(0), shareable_(true){
}

RCObject& RCObject::operator=(const RCObject& rhs) {
  return *this;
}

RCObject::~RCObject() {
}

void RCObject::AddReference() {
  ++refCount_;
}

void RCObject::RemoveReference() {
  if (--refCount_ == 0) {
    delete(this);
  }
}

void RCObject::MarkUnshareable() {
  shareable_ = false;
}

bool RCObject::IsShared() const {
  return refCount_ > 1;
}

bool RCObject::IsShareable() const {
  return shareable_;
}
