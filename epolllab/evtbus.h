
#ifndef __EVTBUS_H__
#define __EVTBUS_H__

class evthdl;

class evtbus
{
public:
	evtbus();
	~evtbus();

	bool open();
	void close();

	void dispatch();

public:
	bool add(int fd, evthdl *hdl);
	bool del(int fd);

private:
	int m_epfd;
};

#endif

