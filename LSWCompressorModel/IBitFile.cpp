#include "IBitFile.h"

IBitFile::IBitFile(std::istream& istream) : _istream(istream)
{
	_curByte = _istream.get();
}

IBitFile::~IBitFile()
{
	close();
}

void IBitFile::close()
{
	closed = false;
}

int IBitFile::getBit()
{
	if (!closed) {
		char result = 1 & (_curByte >> (7 - _curBitIndex % 8));
		if (incCurBitIndex() == EOF) return EOF;
		return result;
	}
	else return EOF;
}

size_t IBitFile::getBits(void* bitPtr, size_t count)
{
	if (!closed) {
		long unsigned int curBitIndex;
		for (curBitIndex = 0; curBitIndex < count; ++curBitIndex) {
			int bit = getBit();
			if (bit == EOF) break;
			long unsigned int curByteIndex = curBitIndex / 8;
			int shiftedBit = (bit << (curBitIndex % 8));
			((unsigned char*)bitPtr)[curByteIndex] |= shiftedBit; //Write to most significant bit first
		}
		return curBitIndex;
	}return 0;
}

int IBitFile::incCurBitIndex()
{
	if (!closed) {
		if (_curByte == EOF)
			return EOF;
		++_curBitIndex;
		if (_curBitIndex % 8 == 0) {
			_curByte = _curByte = _istream.get();
		}
		if (_curByte == EOF)
			return EOF;
		else
			return 0;
	}
	return EOF;
}
