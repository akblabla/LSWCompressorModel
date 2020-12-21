#pragma once
#include "iAccess.h"
#include <list>
class ListAccess :
	public iAccess
{
public:
	ListAccess(std::list<unsigned char> & list);
	virtual ~ListAccess();
	//File access:
	int open();
	int flush();

	//Formatted input/output:

	//Character input/output:
	int getc();
	int putc(int character);

	//Direct input/output:
	size_t read(void* ptr, size_t size, size_t count);
	size_t write(const void* ptr, size_t size, size_t count);

	//File positioning:
	int seek(long int offset, SEEK_MODE origin);
	//Error-handling:
private:
	std::list<unsigned char> &_list;
	std::list<unsigned char>::iterator _iterator;
};

