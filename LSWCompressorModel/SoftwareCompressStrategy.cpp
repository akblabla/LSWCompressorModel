#include "SoftwareCompressStrategy.h"
#include "DictNode.h"
#include "LZWGlobal.h"
SoftwareCompressStrategy::SoftwareCompressStrategy()
{
}

int SoftwareCompressStrategy::compress(iAccess& src, iAccess& dst)
{
    BitFileAccess dstBitAccess(&dst, BitFileAccess::Mode::WRITE);
    unsigned int code;                  /* code for current string */
    unsigned char currentCodeLen = 16;       /* length of the current code */
    unsigned int nextCode;              /* next available code index */
    int c = 0;                              /* character to add to string */

    DictNode* dictRoot;              /* root of dictionary tree */
    DictNode* node;                  /* node of dictionary tree */

    /* initialize dictionary as empty */
    dictRoot = NULL;

    /* start MIN_CODE_LEN bit code words */
    currentCodeLen = MIN_CODE_LEN;

    nextCode = FIRST_CODE;  /* code for next (first) string */

    /* now start the actual encoding process */

    return -1;
}

void SoftwareCompressStrategy::putCodeWord(BitFileAccess& bfpOut, int code, const unsigned char codeLen)
{
	bfpOut.putBits(&code, codeLen);
}



