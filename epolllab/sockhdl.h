
#ifndef __SOCKHDL_H__
#define __SOCKHDL_H__

#include "inputhdl.h"

#include <netinet/in.h>

class sockhdl : public inputhdl
{
public:
	bool open(int fd, struct sockaddr_in *addr);
	
	const char *get_ip();
	int get_port();

private:
	char m_ip[64];
	int m_port;
};

#endif

