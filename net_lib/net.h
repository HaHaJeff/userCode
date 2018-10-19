#ifndef NET_H
#define NET_H
#include <netdb.h>
#include <string>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

struct in_addr GetHostByName(const std::string& host) {
    struct in_addr addr;
    char buf[1024];
    struct hostent hent;
    struct hostent* he = nullptr;
    int herrno = 0;

    memset(&hent, 0, sizeof hent);
    int r = gethostbyname_r(host.c_str(), &hent, buf, sizeof buf, &he, &herrno);
    if (r == 0 && he && he->h_addrtype == AF_INET) {
        addr = *reinterpret_cast<struct in_addr*>(he->h_addr);
    } else {
        addr.s_addr = INADDR_NONE;
    }
    return addr;
}

class Ip4Addr {
public:
    Ip4Addr(const std::string& host, short port);
    Ip4Addr(short port = 0) : Ip4Addr("", port) { }
    Ip4Addr(const struct sockaddr_in& addr) : addr_(addr) {}
    std::string ToString() const;
    std::string GetIp() const;
    short GetPort() const;
    unsigned int GetNetEndianIp() const;
    short GetNetEndianPort() const;
    bool IsIpValid() const;
    struct sockaddr_in& GetAddr() { return addr_;}

private:
    struct sockaddr_in addr_;
};

#endif