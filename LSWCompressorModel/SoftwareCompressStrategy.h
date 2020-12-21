#pragma once
#include "iCompressStrategy.h"
#include "BitFileAccess.h"
class SoftwareCompressStrategy :
	public iCompressStrategy
{
public:
	SoftwareCompressStrategy();
	int compress(iAccess& src, iAccess& dst);
private:

    //structure taken from https://github.com/MichaelDipperstein/lzw .
    //it is rewritten to have a c++ structure and better source/header structure,
    //allowing the code to be used multiple places in the same project without conflict.

    /* write encoded data */
    void putCodeWord(BitFileAccess &bfpOut, int code,
        const unsigned char codeLen);
};

