#include "OBitFile.h"

OBitFile::OBitFile(std::ostream& ostream):
	_ostream(ostream)
{
}

OBitFile::~OBitFile()
{
	close();
}

void OBitFile::close()
{
	if (!closed) {
		if (_curBitIndex % 8 != 0) {
			_ostream.put(_curByte);
			_curByte = 0;
		}
		closed = true;
	}
}

void OBitFile::putBit(unsigned char bit)
{
	if (!closed) {
		bit &= 1; //only first bit should be used
		_curByte |= (bit << (7 - _curBitIndex % 8)); //Write to most significant bit first
		incCurBitIndex();
	}
}

void OBitFile::putBits(void* bitPtr, size_t count)
{
	if (!closed) {
		long unsigned int curBitIndex;
		for (curBitIndex = 0; curBitIndex < count; ++curBitIndex) {
			long unsigned int curByteIndex = curBitIndex / 8;
			char result = 1 & (((unsigned char*)bitPtr)[curByteIndex] >> (curBitIndex % 8)); //Read the most significant bit first

			putBit(result);
		}
	}
}

int OBitFile::incCurBitIndex()
{
	if (!closed) {
		if (_curByte == EOF)
			return EOF;
		++_curBitIndex;
		if (_curBitIndex % 8 == 0) {
			_ostream.put(_curByte);
			_curByte = 0;
		}
		if (_curByte == EOF)
			return EOF;
		else
			return 0;
	}
	return EOF;
}
