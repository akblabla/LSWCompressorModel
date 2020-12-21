#pragma once
#include <string>
class iAccess
{
public:
	enum class SEEK_MODE
	{
		set = 0, cur = 1, end = 2
	};
	//File access:
	virtual int open() = 0;
	virtual int flush() = 0;
	virtual bool isOpen();

	//Formatted input/output:

	//Character input/output:
	virtual int getc() = 0;
	virtual int putc(int character) = 0;

	//Direct input/output:
	virtual size_t read(void* ptr, size_t size, size_t count) = 0;
	virtual size_t write(const void* ptr, size_t size, size_t count) = 0;

	//File positioning:
	virtual int seek(long int offset, SEEK_MODE origin) = 0;
	//Error-handling:
protected:
	bool _isOpen = false;
};

