
#include "evtbus.h"
#include "evthdl.h"
#include "srvhdl.h"
#include "fifohdl.h"

#include <liblog.h>

int add_fifohdl(evtbus *bus)
{
	fifohdl *phdl = new fifohdl;
	if (phdl && phdl->open("./fifo"))
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
	if (phdl && phdl->open(8087, 64))
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

