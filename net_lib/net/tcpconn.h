#ifndef TCPCONN_H
#define TCPCONN_H

#include <memory>
#include "socket.h"
#include "net.h"
#include "buffer.h"
#include "util.h"
#include "eventloop.h"

class TcpConn;
typedef std::shared_ptr<TcpConn> TcpConnPtr;
typedef std::function<void(const TcpConnPtr&)> TcpCallBack;
typedef std::function<void(const TcpConnPtr&, std::string msg)> MsgCallBack;

class TcpConn : public std::enable_shared_from_this<TcpConn>, private Noncopyable{
public:
    enum State { kDisconnected, kDisconnecting, kConnected, kConnecting };
    TcpConn(EventLoop* loop, int sockfd, Ip4Addr local, Ip4Addr peer);
    virtual ~TcpConn();

    EventLoop* GetLoop() const { return loop_; }
    const Ip4Addr GetLocalAddress() const { return localAddr_; }
    const Ip4Addr GetPeerAddress() const { return peerAddr_; }
    bool IsConnected() const {return state_ == kConnected; }
    bool GetTcpInfo(struct tcp_info*) const; 
    std::string GetTcpinfoString() const;

    void Send(const char* message, size_t len);
    void Send(std::string&& message);
    void Send(Buffer& message);
    void Send(const char* s) { Send(s, strlen(s));}

    void OnRead(const TcpCallBack& cb) { readcb_ = cb; }
    void OnWrite(const TcpCallBack& cb) { writecb_ = cb; }
    void OnState(const TcpCallBack& cb) { statecb_ = cb; }

private:
    

private:
    EventLoop* loop_;
    const Ip4Addr localAddr_;
    const Ip4Addr peerAddr_;
    State state_;
    Buffer input_;
    Buffer output_;
    TcpCallBack readcb_;
    TcpCallBack writecb_;
    TcpCallBack statecb_;

    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;

};

#endif