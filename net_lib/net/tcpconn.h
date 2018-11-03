#ifndef TCPCONN_H
#define TCPCONN_H

#include <memory>
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
    bool IsConnected() const {}

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


};

#endif