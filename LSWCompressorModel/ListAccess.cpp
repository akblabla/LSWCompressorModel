#include "ListAccess.h"

ListAccess::ListAccess(std::list<unsigned char> &list) : _list(list)
{
	open();
}

ListAccess::~ListAccess()
{
}

int ListAccess::open()
{
	_iterator = _list.begin();
	return 0;
}

int ListAccess::flush()
{
	return 0;
}

int ListAccess::getc()
{
	if (_iterator == _list.end())return EOF;
	char val = *_iterator;
	++_iterator;
	return val;
}


int ListAccess::putc(int character)
{
	if (_iterator == _list.end())return EOF;
	*_iterator = character;
	++_iterator;
	return 0;
}

size_t ListAccess::read(void* ptr, size_t size, size_t count)
{
	unsigned char* charPtr = (unsigned char*)ptr;
	bool stop = false;
	size_t readElements = 0;
	for (size_t i = 0; i < count; ++i) {
		for (size_t j = 0; j < size; ++j) {
			int res = getc();
			if (res == EOF) {
				stop = true;
				break;
			}
			charPtr[i*size+j] = (unsigned char) res;
			readElements++;
		}
		if (stop) break;
	}
	return readElements;
}

size_t ListAccess::write(const void* ptr, size_t size, size_t count)
{
	const unsigned char* charPtr = (const unsigned char*)ptr;
	bool stop = false;
	size_t writtenElements = 0;
	for (size_t i = 0; i < count; ++i) {
		for (size_t j = 0; j < size; ++j) {
			size_t res = putc(charPtr[i * size + j]);
			if (res == EOF) {
				stop = true;
				break;
			}
			writtenElements++;
		}
		if (stop) break;
	}
	return writtenElements;
}

int ListAccess::seek(long int offset, SEEK_MODE origin)
{
	switch (origin)
	{
	case iAccess::SEEK_MODE::set:
		_iterator = _list.begin();
		for (long int i = 0; i<offset;++i)
		_iterator++;
		break;
	case iAccess::SEEK_MODE::cur:
		if (offset>0)
			for (long int i = 0; i < offset; ++i)
				_iterator++;
		if (offset<0)
			for (long int i = 0; i > -offset; --i)
				_iterator--;

		break;
	case iAccess::SEEK_MODE::end:
		_iterator = _list.end();
		for (long int i = 0; i > -offset; --i)
			_iterator--;
		break;
	default:
		break;
	}
	return 0;
}
