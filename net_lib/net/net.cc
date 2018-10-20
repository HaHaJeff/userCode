#include "net.h"
#include "log.h"
#include "util.h"

Ip4Addr::Ip4Addr(const std::string& host, short port) {
    memset(&addr_, 0, sizeof addr_);
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    if (host.size()) {
        addr_.sin_addr = GetHostByName(host);
    } else {
        addr_.sin_addr.s_addr = INADDR_ANY;
    }

    if (addr_.sin_addr.s_addr = INADDR_NONE) {
        ERROR("cannot resove %s to ip", host.c_str());
    }
}

// 网络字节序，大端模式
std::string Ip4Addr::ToString() const {
    uint32_t uip = addr_.sin_addr.s_addr;
    return Util::Format("%d.%d.%d.%d:%d", (uip>>0) & 0xff, (uip>>8) & 0xff, (uip>>16) & 0xff, (uip>>24) & 0xff, ntohs(addr_.sin_port));
}