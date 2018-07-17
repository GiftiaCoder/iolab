
#ifndef __FIFOHDL_H__
#define __FIFOHDL_H__

#include "inputhdl.h"

class fifohdl : public inputhdl
{
public:
	bool open(const char *path);

	const char *get_path();
private:
	char m_path[512];
};

#endif

