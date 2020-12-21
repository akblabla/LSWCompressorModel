#pragma once
#include "iAccess.h"
class BitFileAccess
{
public:
    enum class Mode
    {
        READ, WRITE
    };
    BitFileAccess(iAccess* fileAccessPtr, Mode);
    void close();
    int getBit();
    size_t getBits(void* bitPtr, size_t count);
    void putBit(unsigned char);
    void putBits(void* bitPtr, size_t count);
    virtual ~BitFileAccess();
private:
    bool closed = false;
    const Mode _mode;
    int incCurBitIndex();
    char _curByte = 0;
    long unsigned int _curBitIndex = 0;
    iAccess* const _fileAccessPtr;
};