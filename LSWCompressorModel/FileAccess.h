#pragma once
#include "iAccess.h"
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
class FileAccess :
	public iAccess
{
public:
	FileAccess(const std::string filename, const std::string mode);
	virtual ~FileAccess();
	//File access:
	int open();
	int flush();

	//Formatted input/output:

	//Character input/output:
	int getc();
	char* gets(char* str, int num);
	int putc(int character);
	int puts(const char* str);

	//Direct input/output:
	size_t read(void* ptr, size_t size, size_t count);
	size_t write(const void* ptr, size_t size, size_t count);

	//File positioning:
	int seek(long int offset, SEEK_MODE origin);
	//Error-handling:
private:
	//File access:
	int close();
	int _failedToOpen;
	const std::string _filename;
	const std::string _mode;
	FILE* _filePtr;
};

