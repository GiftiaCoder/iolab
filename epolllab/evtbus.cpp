
#include "evtbus.h"
#include "evthdl.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#include <sys/epoll.h>

#include <liblog.h>

#define EPOLL_WAIT_NUM (64)

#define EPEVT_IN (EPOLLIN | EPOLLPRI)
#define EPEVT_OUT (EPOLLOUT)
#define EPEVT_ERR (EPOLLERR | EPOLLHUP | EPOLLRDHUP)

evtbus::evtbus() : m_epfd(-1) {}
evtbus::~evtbus()
{
	close();
}

bool evtbus::open()
{
	if ((m_epfd = epoll_create(1)) >= 0)
	{
		return true;
	}
	E("create epoll fd fail, err: %s", ERRSTR);
	return false;
}

void evtbus::close()
{
	if (m_epfd >= 0)
	{
		::close(m_epfd);
		m_epfd = -1;
	}
}

void evtbus::dispatch()
{
	I("begin dispatch");
	int nevt = 0;
	struct epoll_event epevts[EPOLL_WAIT_NUM];
	while ((nevt = epoll_wait(m_epfd, epevts, EPOLL_WAIT_NUM, -1)) >= 0)
	{
		I("%d events waited", nevt);

		int i = 0;
		while (i < nevt)
		{
			struct epoll_event *epevt = epevts + i;

			int events = epevt->events;
			evthdl *hdl = (evthdl *) epevt->data.ptr;
			
			I("idx: %d, events: %018p", i, (void *) events);

			bool down = true;
			if ((events & EPEVT_ERR))
			{
				down = hdl->error(events, this);
			}
			
			if (down)
			{
				if ((events & EPEVT_IN))
				{
					hdl->read(events, this);
				}
				if ((events & EPEVT_OUT))
				{
					hdl->write(events, this);
				}
			}
			++i;
		}	
	}
	E("wait %d event from epoll, err: %s", nevt, ERRSTR);
}

bool evtbus::add(int fd, evthdl *hdl)
{
	struct epoll_event epevt = { 0 };
	epevt.events = EPEVT_IN | /*EPEVT_OUT | */EPEVT_ERR | EPOLLET;
	epevt.data.ptr = (void *) hdl;

	if (! epoll_ctl(m_epfd, EPOLL_CTL_ADD, fd, &epevt))
	{
		return true;
	}
	E("epoll_ctl regist fd fail, err: %e", ERRSTR);
	return false;
}

bool evtbus::del(int fd)
{
	if (! epoll_ctl(m_epfd, EPOLL_CTL_DEL, fd, NULL))
	{
		return true;
	}
	E("epoll_ctl remove fd fail, err: %s", ERRSTR);
	return false;
}

