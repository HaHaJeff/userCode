#ifndef STATUS_H
#define STATUS_H

#include <string>
extern "C" {
#include <string.h>
}

// delete: when argument is nullptr, nothing will to do
class Status {
public:
    Status() : state_(nullptr) { }
    Status(int code, const char* msg);
    Status(int code, const std::string& msg) : Status(code, msg.c_str()) { }
    ~Status() { delete[] state_; }


    Status(const Status& s) { state_ = s.Clone(); }
    void operator=(const Status& s) { delete[] state_; state_ = s.Clone(); }
    Status(Status&& s) { state_ = s.state_; }
    void operator=(Status&& s) { delete[] state_; state_ = s.state_; s.state_ = nullptr; }

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

#endif
