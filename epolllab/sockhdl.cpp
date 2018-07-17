
#include "sockhdl.h"

#include <arpa/inet.h>
#include <sys/types.h>

bool sockhdl::open(int fd, struct sockaddr_in *addr)
{
	if (inputhdl::open(fd))
	{
		(void) inet_ntop(AF_INET, (void *) &(addr->sin_addr), m_ip, sizeof(m_ip) - 1);
		m_port = (int) ntohs(addr->sin_port);

		return true;
	}
	return false;
}

const char *sockhdl::get_ip()
{
	return m_ip;
}

int sockhdl::get_port()
{
	return m_port;
}

