#include "SoftwareCompressStrategy.h"
#include "Dictionary.h"
#include "LZWGlobal.h"
#include <vector>
#define BUFFER_SIZE 256
unsigned char buf[BUFFER_SIZE];
SoftwareCompressStrategy::SoftwareCompressStrategy()
{
}

int SoftwareCompressStrategy::compress(iAccess& src, iAccess& dst)
{
    size_t currentBufLength = 0;
    Dictionary dict;
    while (1) {
        int byte = src.getc();
        if (byte == EOF) break;
        if (currentBufLength >= BUFFER_SIZE) {
            throw "ran out of buffer";
        }
        buf[currentBufLength] = byte;
        currentBufLength++;
        unsigned int codeWord = 0;
        if (dict.findCodeWord(codeWord, buf, currentBufLength)) {
            dst.putc((unsigned char)(codeWord>>8));
            dst.putc(((unsigned char) codeWord));
            buf[0] = byte;
            currentBufLength = 1;
        }
    }

    return -1;
}

void SoftwareCompressStrategy::putCodeWord(BitFileAccess& bfpOut, int code, const unsigned char codeLen)
{
	bfpOut.putBits(&code, codeLen);
}



