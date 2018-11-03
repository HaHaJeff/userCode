#include <netinet/tcp.h>
#include "socket.h"

Socket::~Socket() {
    close(sockfd_);
}

bool Socket::GetTcpInfo(struct tcp_info* tcpi) const {
    socklen_t len = sizeof(*tcpi);
    bzero(tcpi, len);
    return getsockopt(sockfd_, SOL_TCP, TCP_INFO, tcpi, &len) == 0;
}

bool Socket::GetTcpInfoString(char*buf, int len) const {
    struct tcp_info tcpi;
    bool ok = GetTcpInfo(&tcpi);
    if (ok) {
        snprintf(buf, len, "unrecoverd=%u "
        "rto=%u ato=%u snd_mss=%u rcv_mss=%u "
        "lost=%u retrans=%u rtt=%u rttvar=%u "
        "sshthresh=%u cwnd=%u total_retrans=%u",
        tcpi.tcpi_retransmits,
        tcpi.tcpi_rto,
        tcpi.tcpi_ato,
        tcpi.tcpi_snd_mss,
        tcpi.tcpi_rcv_mss,
        tcpi.tcpi_lost,
        tcpi.tcpi_retrans,
        tcpi.tcpi_rtt,
        tcpi.tcpi_rttvar,
        tcpi.tcpi_snd_ssthresh,
        tcpi.tcpi_snd_cwnd,
        tcpi.tcpi_total_retrans);
    }
    return ok;
}

void Socket::BindAddress(const Ip4Addr& addr) {
    
}