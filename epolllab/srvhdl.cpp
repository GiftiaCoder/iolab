
#include "srvhdl.h"
#include "sockhdl.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <unistd.h>
#include <fcntl.h>

#include <liblog.h>

srvhdl::srvhdl() : m_fd(-1) {}
srvhdl::~srvhdl()
{
	close();
}

int srvhdl::get_fd()
{
	return m_fd;
}

bool srvhdl::open(int port, int backlog)
{
	close();

	int srvsock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (srvsock < 0)
	{
		E("create socket fail, err: %s", ERRSTR);
		return false;
	}

	struct sockaddr_in srvaddr = { 0 };
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(port);
	srvaddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(srvsock, (struct sockaddr *) &srvaddr, sizeof(srvaddr)))
	{
		E("bind socket fail, err: %s", ERRSTR);
		::close(srvsock);
		return false;
	}

	if (listen(srvsock, backlog))
	{
		E("listen socket fail, err: %s", ERRSTR);
		::close(srvsock);
		return false;
	}

	m_fd = srvsock;
	return true;
}

void srvhdl::close()
{
	if (m_fd >= 0)
	{
		::close(m_fd);
		m_fd = -1;
	}
}

void srvhdl::read(int events, evtbus *bus)
{
	int clifd;
	
	struct sockaddr_in cliaddr = { 0 };
	socklen_t addrsz = sizeof(cliaddr);
	while ((clifd = accept(m_fd, (struct sockaddr *) &cliaddr, &addrsz)) >= 0)
	{
		sockhdl *hdl = new sockhdl;
		if (hdl)
		{
			if (hdl->open(clifd, &cliaddr))
			{
				I("accept addr: %s:%d", hdl->get_ip(), hdl->get_port());
				if (bus->add(clifd, hdl))
				{
					continue;
				}
				E("regist sockhdl to bus fail");
				continue;
			}
			continue;
		}
		E("new evthdl object fail, err: %s", ERRSTR);
		continue;
	}
}

void srvhdl::write(int events, evtbus *bus)
{
	I("get output event");
}

bool srvhdl::error(int events, evtbus *bus)
{
	I("get error event, events: %08X", events);
	return true;
}

