
#ifndef __EVTHDL_H__
#define __EVTHDL_H__

#include "evtbus.h"

class evthdl
{
public:
	virtual void read(int events, evtbus *bus) = 0;
	virtual void write(int events, evtbus *bus) = 0;
	
	virtual bool error(int events, evtbus *bus) = 0;
};

#endif

