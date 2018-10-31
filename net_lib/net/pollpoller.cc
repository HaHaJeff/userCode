#include <poll.h>
#include <errno.h>
#include <assert.h>
#include <algorithm>
#include "pollpoller.h"
#include "log.h"
#include "channel.h"

/*
   struct pollfd {
      int   fd;         // file descriptor
      short events;     // requested events
      short revents;    // returned events
   };
*/


PollPoller::PollPoller(EventLoop* loop) : Poller(loop) {
}

PollPoller::~PollPoller() {
}

TimeStamp PollPoller::Poll(int timeoutMs, ChannelList* activeChannels) {
  int numEvents = poll(&*pollfds_.begin(), pollfds_.size(), timeoutMs);
  TimeStamp now(TimeStamp::Now());
  if (numEvents > 0) {
    TRACE("%d events happened", numEvents);
    FillActiveChannels(numEvents, activeChannels);
  } else if (numEvents == 0) {
    TRACE(" nothing happend");
  } else {
  }
  return now;
}

void PollPoller::FillActiveChannels(int numEvents, ChannelList* activeChannels) const {
  for (PollFdList::const_iterator pfd = pollfds_.begin(); pfd != pollfds_.end() && numEvents > 0; ++pfd) {
    if (pfd->revents > 0) {
      --numEvents;
      ChannelMap::const_iterator ch = channels_.find(pfd->fd);
      Channel* channel = ch->second;
      channel->SetREvents(pfd->revents);
      activeChannels->push_back(channel);
    }
  }
}

void PollPoller::UpdateChannel(Channel* channel) {
  Poller::AssertInLoopThread();
  TRACE("updating channel %lld fd %d events %d", (long long)channel->GetId(), channel->GetFd(), channel->GetEvents());
  int fd = channel->GetFd();
  assert(channels_.find(fd) != channels_.end());
  struct pollfd pfd;
  pfd.fd = fd;
  pfd.events = static_cast<short>(channel->GetEvents());
  pfd.revents = 0;
  // FIXME: ignore channel->IsNoneEvent()
}

void PollPoller::AddChannel(Channel* channel) {
  Poller::AssertInLoopThread();
  TRACE("adding channel %lld, fd=%d, events=%d", channel->GetFd(), channel->GetEvents());
  struct pollfd pfd;
  pfd.fd = channel->GetFd();
  pfd.events = channel->GetEvents();
  pfd.revents = 0;
  pollfds_.push_back(pfd);
  channels_[pfd.fd] = channel;
  size_t idx = pollfds_.size()-1;
  channel->SetIndex(idx);
}

void PollPoller::RemoveChannel(Channel* channel) {
  Poller::AssertInLoopThread();
  TRACE("remove channel %lld fd %d events %d", (long long)channel->GetId(), channel->GetFd(), channel->GetEvents());
  assert(channels_.find(channel->GetFd()) != channels_.end());
  assert(channels_[channel->GetFd()] == channel);
  size_t idx = channel->GetIndex();

  // 不调用vector的erase，vector在内部调用删除操作开销太大，于是选择将要删除的放至末尾
  // 调用pop_back
  if (idx == pollfds_.size() - 1) {
    pollfds_.pop_back();
  } else {
    const struct pollfd& endPfd = pollfds_.back();
    std::iter_swap(pollfds_.begin()+idx, pollfds_.end()-1);
    channels_[endPfd.fd]->SetIndex(idx);
    pollfds_.pop_back();
    channels_.erase(channel->GetFd());
  }

}
