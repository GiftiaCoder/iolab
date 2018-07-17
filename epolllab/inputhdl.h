
#ifndef __INPUTHDL_H__
#define __INPUTHDL_H__

#include "evthdl.h"

class inputhdl : public evthdl
{
public:
	inputhdl();
	~inputhdl();
	
	bool open(int fd);
	void close();

	int get_fd();

public:
	virtual void read(int events, evtbus *bus) override;
	virtual void write(int events, evtbus *bus) override;
	
	virtual bool error(int events, evtbus *bus) override;

private:
	int m_fd;

	int m_rdlen;
	char m_rdbuf[1024 * 8];
};

#endif

