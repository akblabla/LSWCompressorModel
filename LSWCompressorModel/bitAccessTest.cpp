#include "bitAccessTest.h"
#include "IBitFile.h"
#include "OBitFile.h"
#include <cassert>

#include <streambuf>
#include <istream>

struct membuf : std::streambuf {
	membuf(char const* base, size_t size) {
		char* p(const_cast<char*>(base));
		this->setg(p, p, p + size);
	}
};

struct memWbuf : std::streambuf // derive because std::streambuf constructor is protected
{
	memWbuf(char* p, size_t size)
	{
		setp(p, p + size); // set start end end pointers
	}
	size_t written() { return pptr() - pbase(); } // how many bytes were really written?
};

void bitAccesstest()
{
	//read test
	{
		char buf[2] = { 0b01010010,0b01010010 };
		membuf _membuf(buf, 2);
		std::istream _istream(&_membuf);
		IBitFile bitFileAccess(_istream);
		int bit = bitFileAccess.getBit();
		assert(bit == 0);
		bit = bitFileAccess.getBit();
		assert(bit == 1);
		bit = bitFileAccess.getBit();
		assert(bit == 0);
		unsigned char halfByte = 0;
		int count = bitFileAccess.getBits(&halfByte, 4);
		assert(halfByte == 0b00001001);
		unsigned int nineBit = 0;
		count = bitFileAccess.getBits(&nineBit, 9);
		assert(nineBit == 0b0000000010010100);
	}
	//write test
	{
		char buf[2] = { 0,0};
		memWbuf _membuf(buf, 2);
		std::ostream _ostream(&_membuf);
		OBitFile bitFileAccess(_ostream);
		bitFileAccess.putBit(1);
		bitFileAccess.putBit(1);
		bitFileAccess.putBit(1);
		bitFileAccess.putBit(0);
		unsigned char halfByte = 0b1100;
		bitFileAccess.putBits(&halfByte, 4);
		bitFileAccess.close();
		assert(buf[0] == -29);
	}
	//symmertry test
	{
		char buf[2] = { 0,0 };
		unsigned int dataOut = 0b0100110011;
		unsigned int dataIn = 0;
		{
			memWbuf _membuf(buf, 2);
			std::ostream _ostream(&_membuf);
			OBitFile bitFileAccess(_ostream);

			bitFileAccess.putBits(&dataOut, 10);
			bitFileAccess.close();
			assert(buf[0] == -52);
			assert(buf[1] == -128);
		}
		{
			membuf _membuf(buf, 2);
			std::istream _istream(&_membuf);
			IBitFile bitFileAccess(_istream);
			bitFileAccess.getBits(&dataIn, 10);
			bitFileAccess.close();
		}
		assert(dataOut == dataIn);
	}
}
