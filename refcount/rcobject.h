#ifndef RCOBJECT_H
#define RCOBJECT_H

class RCObject {
  public:
    RCObject();
    RCObject(const RCObject& rhs);
    RCObject& operator=(const RCObject& rhs);
    virtual ~RCObject()=0;
    void AddReference();
    void RemoveReference();
    void MarkUnshareable();
    bool IsShared() const;
    bool IsShareable() const;
  private:
    int refCount_;
    bool shareable_;
};

#endif
