#include "tcpconn.h"
#include "log.h"
#include "channel.h"
#include <poll.h>
#include <functional>

void TcpConn::Attach(EventLoop* loop, int fd, const Ip4Addr& local, const Ip4Addr& peer) {
    loop_ = loop;
    state_ = State::kHandShakeing;
    localAddr_ = local;
    peerAddr_ = peer; 

    Channel* ch = new Channel(loop, fd);
    fd_ = fd;
    channel_.reset(ch);
    TRACE("tcp constructed %s - %s fd: %d", localAddr_.ToString().c_str(), peerAddr_.ToString().c_str(), fd);

    TcpConnPtr conn = shared_from_this();
    conn->channel_->SetReadCallback([=]{conn->HandleRead(conn); });
    conn->channel_->SetWriteCallback([=]{conn->HandleWrite(conn); });
}

void TcpConn::Connect(EventLoop* loop, const Ip4Addr& local, const Ip4Addr& peer, int timeout) {
    localAddr_ = local;
    peerAddr_ = peer;
    connectTimeout_ = timeout;
    connectedTimeout_ = Util::TimeMilli();

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    Net::SetNonBlock(fd);
    
    int r = 0;
    r = bind(fd, sockaddr_cast(&peerAddr_.GetAddr()), sizeof(struct sockaddr));

    if (r < 0) {
        ERROR("bind to %s failed error %d %s", peerAddr_.ToString().c_str(), errno, strerror(errno));
    }
    if (r == 0) {
        r = connect(fd, sockaddr_cast(&peer.GetAddr()), sizeof(struct sockaddr));
        //  The socket is nonblocking and the connection cannot be completed immediately.
        if (r != 0 && errno != EINPROGRESS) {
            ERROR("connect to %s error %d %s", peerAddr_.ToString().c_str(), errno, strerror(errno));
        }
    }

    struct sockaddr_in localin = localAddr_.GetAddr();
    socklen_t len = sizeof(local);

    if (r == 0) {
        r = getsockname(fd, sockaddr_cast(&localin), &len);
        if (r < 0) {
            ERROR("getsockname failed %d %s", errno, strerror(errno));
        }
    }

    state_ = State::kHandShakeing;
    // if connected has successed, fd is writeable
    Attach(loop, fd, localAddr_, peerAddr_);
    if (timeout) {
        TcpConnPtr con = shared_from_this();
        timeoutId_ = loop_->RunAfter(timeout, [con] {
            if (con->GetState() == kHandShakeing) { con->channel_->Close(); }
        });
    }
}

void TcpConn::Close() {
    if (channel_ != nullptr) {
        TcpConnPtr con = shared_from_this();
        loop_->RunInLoop([con]{ if (con->channel_) con->channel_->Close(); });
    }
}

void TcpConn::CleanUp(const TcpConnPtr& con) {
    if (readcb_ && input_.GetSize()) {
        readcb_(con);
    }
    if (state_ == State::kHandShakeing) {
        state_ = State::kFailed;
    } else {
        state_ = State::kClosed;
    }

    TRACE("tcp closeing %s - %s fd %d %d",
        localAddr_.ToString().c_str(),
        peerAddr_.ToString().c_str(),
        channel_ ? channel_->GetFd(): -1, errno);
    loop_->Cancel(timeoutId_);

    if (statecb_) {
        statecb_(con);
    }

    readcb_ = writecb_ = statecb_ = nullptr;
}

void TcpConn::HandleRead(const TcpConnPtr& con) {
   if (state_ == State::kHandShakeing && HandleHandShake(con)) {
       return;
   }
   while (state_ == State::kConnected) {
       input_.MakeRoom();
       int rd = 0;
       if (channel_->GetFd() >= 0) {
           rd = read(channel_->GetFd(), input_.End(), input_.GetSpace());
           TRACE("channel %lld fd %d reader %d bytes", (long long)channel_->GetId(), channel_->GetFd(), rd);
       }
       // Teh call interrupted by signal
       if (rd == -1 && errno == EINTR) {
           continue;
       } else if(rd == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
           break;
       } else if (channel_->GetFd() == -1 || rd == -1) {
           CleanUp(con);
           break;
       } else {
           input_.AddSize(rd);
       }
   }
}

int TcpConn::HandleHandShake(const TcpConnPtr& con) {
    struct pollfd pfd;
    pfd.fd = channel_->GetFd();
    pfd.events = POLLOUT | POLLERR;
    int r = poll(&pfd, 1, 0);

    // if fd is connected, fd is writable
    if (r == 1 && pfd.revents == POLLOUT) {
        channel_->EnableRead();
        state_ = State::kConnected;
        if (state_ == State::kConnected) {
            connectedTimeout_ = Util::TimeMilli();
            TRACE("tcp connected %s - %s fd %d", localAddr_.ToString().c_str(), peerAddr_.ToString(), channel_->GetFd());
        }
    } else {
        TRACE("poll fd %d return %d revents %d", channel_->GetFd(), r, pfd.revents);
        CleanUp(con);
        return -1;
    }
    return 0;
}