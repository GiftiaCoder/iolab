
#ifndef __SRVHDL_H__
#define __SRVHDL_H__

#include "evthdl.h"

class srvhdl : public evthdl
{
public:
	srvhdl();
	~srvhdl();

	bool open(int port, int backlog);
	void close();
	
	int get_fd();

public:
	virtual void read(int events, evtbus *bus) override;
	virtual void write(int events, evtbus *bus) override;
	
	virtual bool error(int events, evtbus *bus) override;

private:
	int m_fd;
};

#endif

