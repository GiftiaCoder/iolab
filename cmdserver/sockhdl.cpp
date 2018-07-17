
#include "sockhdl.h"

sockhdl::sockhdl(int fd, struct sockaddr_in *addr) : inputhdl(fd)
{
	(void) inet_ntop(AF_INET, (void *) &(addr->sin_addr), m_ip, sizeof(m_ip) - 1);
	m_port = (int) ntohs(addr->sin_port);
}

const char *sockhdl::get_ip()
{
	return m_ip;
}

int sockhdl::get_port()
{
	return m_port;
}

