#include "BitFileAccess.h"

BitFileAccess::BitFileAccess(iAccess* fileAccessPtr, Mode mode) : _fileAccessPtr(fileAccessPtr), _mode(mode)
{
	if (_mode == Mode::READ)
		_curByte = _fileAccessPtr->getc();
	if (_mode == Mode::WRITE) {
		_curByte = 0;
	}
}

void BitFileAccess::close()
{
	if (!closed){
		if (_curBitIndex % 8 != 0) {
			if (_mode == Mode::WRITE) {
				_fileAccessPtr->putc(_curByte);
				_curByte = 0;
			}
		}
	closed = true;
	}
}

int BitFileAccess::getBit()
{
	if (!closed) {
		char result = 1 & (_curByte >> (7 - _curBitIndex % 8));
		if (incCurBitIndex() == EOF) return EOF;
		return result;
	}
	else return EOF;
}

size_t BitFileAccess::getBits(void* bitPtr, size_t count)
{
	if (!closed) {
		size_t curBitIndex;
		for (curBitIndex = 0; curBitIndex < count; ++curBitIndex) {
			int bit = getBit();
			if (bit == EOF) break;
			long int curByteIndex = curBitIndex / 8;
			int shiftedBit = (bit << (curBitIndex % 8));
			((unsigned char*)bitPtr)[curByteIndex] |= shiftedBit; //Write to most significant bit first
		}
		return curBitIndex;
	}return 0;
}

void BitFileAccess::putBit(unsigned char bit)
{
	if (!closed) {
		bit &= 1; //only first bit should be used
		_curByte |= (bit << (7 - _curBitIndex % 8)); //Write to most significant bit first
		incCurBitIndex();
	}
}

void BitFileAccess::putBits(void* bitPtr, size_t count)
{
	if (!closed) {
		size_t curBitIndex;
		for (curBitIndex = 0; curBitIndex < count; ++curBitIndex) {
			long int curByteIndex = curBitIndex / 8;
			char result = 1 & (((unsigned char*)bitPtr)[curByteIndex] >> (curBitIndex % 8)); //Read the most significant bit first

			putBit(result);
		}
	}
}

BitFileAccess::~BitFileAccess()
{
	close();
}

int BitFileAccess::incCurBitIndex()
{
	if (!closed) {
		if (_curByte == EOF)
			return EOF;
		++_curBitIndex;
		if (_curBitIndex % 8 == 0) {
			if (_mode == Mode::READ)
				_curByte = _fileAccessPtr->getc();
			if (_mode == Mode::WRITE) {
				_fileAccessPtr->putc(_curByte);
				_curByte = 0;
			}
		}
		if (_curByte == EOF)
			return EOF;
		else
			return 0;
	}
	return EOF;
}
