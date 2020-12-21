#include "FileAccess.h"

FileAccess::FileAccess(const std::string filename, const std::string mode) : _filename(filename), _mode(mode)
{
	open();
}

FileAccess::~FileAccess()
{
	close();
}

int FileAccess::close()
{
	if (!_isOpen) return EOF;
	return std::fclose(_filePtr);
}

int FileAccess::flush()
{
	if (!_isOpen) return EOF;
	return std::fflush(_filePtr);
}

int FileAccess::open()
{
	if (!_isOpen)
	_filePtr = std::fopen(_filename.c_str(), _mode.c_str());
	if (_filePtr == nullptr) return EOF;
	_isOpen = true;
	return 0;
}

int FileAccess::getc()
{
	if (!_isOpen) return EOF;
	return std::fgetc(_filePtr);
}

char* FileAccess::gets(char* str, int num)
{
	if (!_isOpen) return nullptr;
	return std::fgets(str, num, _filePtr);
}

int FileAccess::putc(int character)
{
	if (!_isOpen) return EOF;
	return std::fputc(character, _filePtr);
}

int FileAccess::puts(const char* str)
{
	if (!_isOpen) return EOF;
	return std::fputs(str, _filePtr);
}

size_t FileAccess::read(void* ptr, size_t size, size_t count)
{
	if (!_isOpen) return EOF;
	return std::fread(ptr, size, count, _filePtr);
}

size_t FileAccess::write(const void* ptr, size_t size, size_t count)
{
	if (!_isOpen) return EOF;
	return std::fwrite(ptr, size, count, _filePtr);
}

int FileAccess::seek(long int offset, SEEK_MODE origin)
{
	
	return std::fseek(_filePtr,offset,(int) origin);
}
