#include <poll.h>
#include <errno.h>
#include "pollpoller.h"
#include "log.h"
#include "channel.h"

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
  for (PollFdList::const_iterator pfd = pollfds_.begin();
      pfd != pollfds_.end() && numEvents > 0; ++pfd) {
    if (pfd->revents > 0) {
      --numEvents;
      ChannelMap::const_iterator ch = channels_.find(pfd->fd);
      Channel* channel = ch->second;
      channel->SetREvents(pfd->events);
      activeChannels->push_back(channel);
    }
  }
}

void PollPoller::UpdateChannel(Channel* channel) {

}

void PollPoller::AddChannel(Channel* channel) {

}

void PollPoller::RemoveChannel(Channel* channel) {

}
