
#include "fifohdl.h"

//#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <stdio.h>

#include <liblog.h>

bool fifohdl::open(const char *path)
{
	int fd = ::open(path, O_RDWR | O_NONBLOCK);
	if (fd < 0)
	{
		E("file open fail, err: %s", ERRSTR);
		return false;
	}
	if (! inputhdl::open(fd))
	{
		return false;
	}
	(void) snprintf(m_path, sizeof(m_path) - 1, "%s", path);
	return true;
}

const char *fifohdl::get_path()
{
	return m_path;
}

