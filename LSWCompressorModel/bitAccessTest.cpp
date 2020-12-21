#include "bitAccessTest.h"
#include "BitFileAccess.h"
#include "ListAccess.h"
#include <cassert>

void bitAccesstest()
{
	//read test
	{
		std::list<unsigned char> l = { 0b01010010,0b01010010 };
		ListAccess listAccess(l);
		BitFileAccess bitFileAccess(&listAccess, BitFileAccess::Mode::READ);
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
		std::list<unsigned char> l = { 0,0 };
		ListAccess listAccess(l);
		BitFileAccess bitFileAccess(&listAccess, BitFileAccess::Mode::WRITE);
		bitFileAccess.putBit(1);
		bitFileAccess.putBit(1);
		bitFileAccess.putBit(1);
		bitFileAccess.putBit(0);
		unsigned char halfByte = 0b1100;
		bitFileAccess.putBits(&halfByte, 4);
		bitFileAccess.close();
		assert(*(l.begin()) == 0b11100011);
	}
	//symmertry test
	{
		std::list<unsigned char> l = { 0,0 };
		unsigned int dataOut = 0b0100110011;
		unsigned int dataIn = 0;
		{
			ListAccess listAccess(l);
			BitFileAccess bitFileAccess(&listAccess, BitFileAccess::Mode::WRITE);
			bitFileAccess.putBits(&dataOut, 10);
			bitFileAccess.close();
			assert(*(l.begin()) == 0b11001100);
			assert(*(++l.begin()) == 0b10000000);
		}
		{
			ListAccess listAccess(l);
			BitFileAccess bitFileAccess(&listAccess, BitFileAccess::Mode::READ);
			bitFileAccess.getBits(&dataIn, 10);
			bitFileAccess.close();
		}
		assert(dataOut == dataIn);
	}
}
