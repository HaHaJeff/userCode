#ifndef STATUS_H
#define STATUS_H

#include <string>
extern "C" {
#include <string.h>
#include <stdarg.h>
}

#include "util.h"

inline const char* errstr() {return strerror(errno);}

// delete: when argument is nullptr, nothing will to do
class Status {
public:
    Status() : state_(nullptr) { }
    Status(int code, const char* msg);
    Status(int code, const std::string& msg) : Status(code, msg.c_str()) { }
    ~Status() { delete[] state_; }

    Status(const Status& s) { state_ = s.Clone(); }
    void operator=(const Status& s) { delete[] state_; state_ = s.Clone(); }
    Status(Status&& s) { state_ = s.state_; s.state_ = nullptr;}
    void operator=(Status&& s) { delete[] state_; state_ = s.state_; s.state_ = nullptr; }

    // errno is threa local
    static Status FromSystem() { return Status(errno, strerror(errno)); }
    static Status FromSystem(int err) { return Status(err, strerror(err));} 
    static Status FromFormat(int code, const char* fmt, ...);
    static Status IoError(const std::string& op, const std::string& name) {
        return Status::FromFormat(errno, "%s %s %s", op.c_str(), name.c_str(), errstr());
    }

    //state_ == nullptr means ok
    int Code() { return state_ ? *(int32_t*)(state_+4) : 0;}
    const char* Msg() { return state_ ? state_ + 8 : "";}
    bool Ok() { return Code() == 0;}
    std::string ToString() { return Util::Format("%d %s", Code(), Msg());}

private:
    // deep copy
    const char* Clone() const;

private:
    // frome leveldb and handy
    // state_[0...3] == length of message
    // state_[4...7] == code   leveldb: state_[4] == code(using enum class)
    // state_[5...]  == message
    const char* state_;
};

const char* Status::Clone() const {
    if (state_ == nullptr) {
        return state_;
    }
    uint32_t size = *(uint32_t*)state_;
    char* res = new char[size];
    memcpy(res, state_, size);
    return res;
}

 // state_[0...3] == length of message
 // state_[4...7] == code   leveldb: state_[4] == code(using enum class)
 // state_[5...]  == message
inline Status::Status(int code, const char* msg) {
    uint32_t sz = strlen(msg) + 8;
    char* p = new char[sz];
    state_ = p;
    // length: include header info
    *(uint32_t*)p = sz;
    // code
    *(uint32_t*)(p+4) = code;
    // msg
    memcpy(p+8, msg, sz-8);
}

// construct Status object from fmt
inline Status Status::FromFormat(int code, const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    // get size, 1 means '\0'
    uint32_t sz = 8 + vsnprintf(nullptr, 0, fmt, ap) + 1;
    va_end(ap);

    Status res;
    res.state_ = new char[sz];
    char* p = const_cast<char*>(res.state_);
    // length: include header info
    *(uint32_t*)p = sz;
    // code
    *(uint32_t*)(p+4) = code;
    // msg
    va_start(ap, fmt);
    vsnprintf(p+8, sz-8, fmt, ap);
    va_end(ap);
    return res;
}

#endif
