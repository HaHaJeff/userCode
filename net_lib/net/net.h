#ifndef NET_H
#define NET_H

#include <netdb.h>
#include <string>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

class Net {
  public:
    static int SetNonBlock(int fd, bool value=true);
    static int SetReuseAddr(int fd, bool value=true);
    static int SetReusePort(int fd, bool value=true);
    static int SetNoDelay(int fd, bool value=true);
    static struct in_addr GetHostByName(const std::string& host);
};


class Ip4Addr {
public:
    Ip4Addr(const std::string& host, short port);
    Ip4Addr(short port = 0) : Ip4Addr("", port) { }
    Ip4Addr(const struct sockaddr_in& addr) : addr_(addr) {}
    std::string ToString() const;
    std::string GetIp() const;
    short GetPort() const;
    unsigned int GetIpInt() const;
    unsigned int GetNetEndianIp() const;
    short GetNetEndianPort() const;
    bool IsIpValid() const;
    struct sockaddr_in& GetAddr() { return addr_;}

private:
    struct sockaddr_in addr_;
};

#endif
