#pragma once
#include <istream>
class IBitFile
{
public:
	IBitFile(std::istream& istream);
	~IBitFile();
	void close();
	int getBit();
	size_t getBits(void* bitPtr, size_t count);

private:
	std::istream& _istream;
	bool closed = false;
	int incCurBitIndex();
	char _curByte = 0;
	long unsigned int _curBitIndex = 0;
};

