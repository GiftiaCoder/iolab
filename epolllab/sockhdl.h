
#ifndef __SOCKHDL_H__
#define __SOCKHDL_H__

#include "inputhdl.h"

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class sockhdl : public inputhdl
{
public:
	sockhdl(int fd, struct sockaddr_in *addr);

	const char *get_ip();
	int get_port();

private:
	char m_ip[64];
	int m_port;
};

#endif

