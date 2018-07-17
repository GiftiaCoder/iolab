
#include "evtbus.h"
#include "evthdl.h"
#include "srvhdl.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#include <liblog.h>

class fifohdl : public evthdl
{
public:
	fifohdl();
	~fifohdl();

	bool open(const char *path);
	void close();

	int get_fd();

public:
	virtual void read(int events, evtbus *bus) override;
	virtual void write(int events, evtbus *bus) override;
	
	virtual bool error(int events, evtbus *bus) override;

private:
	int m_fd;
	
	int m_rdlen;
	char m_rdbuf[4096];
};

fifohdl::fifohdl() : m_fd(-1), m_rdlen(0)  {}
fifohdl::~fifohdl()
{
	close();
}

bool fifohdl::open(const char *path)
{
	m_rdlen = 0;

	if ((m_fd = ::open(path, O_RDWR | O_NONBLOCK)) >= 0)
	{
		return true;
	}
	E("open fifo %s fail, err: %s", path, ERRSTR);
	return false;
}

void fifohdl::close()
{
	if (m_fd >= 0)
	{
		::close(m_fd);
		m_fd = -1;
	}
}

int fifohdl::get_fd()
{
	return m_fd;
}

void fifohdl::read(int events, evtbus *bus)
{
	int ret, len = 0;
	while ((ret = ::read(m_fd, (void *) (m_rdbuf + len), (sizeof(m_rdbuf) - 1) - len)) > 0)
	{
		len += ret;
	}

	if (len > 0)
	{
		m_rdbuf[len] = 0;
		I("[read] %s", m_rdbuf);
	}
	else
	{
		E("not data read, ret: %d, error: %d,%s", ret, errno, ERRSTR);
	}
}

void fifohdl::write(int events, evtbus *bus)
{
	I("get output event");
}

bool fifohdl::error(int events, evtbus *bus)
{
	I("get error event, err: %d,%s", errno, ERRSTR);
	return true;
}

int add_fifohdl(evtbus *bus)
{
	fifohdl *phdl = new fifohdl;
	if (phdl->open("./fifo"))
	{
		if (bus->add(phdl->get_fd(), phdl))
		{
			return 0;
		}
		E("regist event fail");
		return -1;
	}
	E("open fifo fail");
	return -1;
}

int add_srvhdl(evtbus *bus)
{
	srvhdl *phdl = new srvhdl();
	if (phdl->open(8087, 64))
	{
		I("srv fd: %d", phdl->get_fd());
		if (bus->add(phdl->get_fd(), phdl))
		{
			return 0;
		}
		E("regist event fail");
		return -1;
	}
	E("open server socket fail");
	return -1;
}

int main()
{
	evtbus bus;
	if (! bus.open())
	{
		E("bus open fail");
		return 0;
			
	}
	(void) add_fifohdl(&bus);
	(void) add_srvhdl(&bus);
	bus.dispatch();

	return 0;
}

