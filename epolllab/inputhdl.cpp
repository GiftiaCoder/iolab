
#include "inputhdl.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#include <liblog.h>

inputhdl::inputhdl(int fd) : m_fd(fd) 
{
	int flag = fcntl(m_fd, F_GETFL, 0);
	int ret = fcntl(m_fd, F_SETFL, flag | O_NONBLOCK);
	if (ret)
	{
		E("fd: %d set nonblock fail, err: %s", ERRSTR);
	}
}
inputhdl::~inputhdl()
{
	if (m_fd >= 0)
	{
		close(m_fd);
		m_fd = -1;
	}
}

void inputhdl::read(int events, evtbus *bus)
{
	int ret, len = 0;
	while ((ret = ::read(m_fd, (void *) (m_rdbuf + len), (sizeof(m_rdbuf) - 1) - len)) > 0)
	{
		len += ret;
	}

	if (len > 0)
	{
		m_rdbuf[len] = 0;
		I("read %d bytes: %s", len, m_rdbuf);
	}
	else
	{
		E("read fail, ret: %d, err: %d,%s", ret, errno, ERRSTR);
	}
}

void inputhdl::write(int events, evtbus *bus)
{
	I("get write event");
}

bool inputhdl::error(int events, evtbus *bus)
{
	I("get error event, err: %d,%s", errno, ERRSTR);
}

