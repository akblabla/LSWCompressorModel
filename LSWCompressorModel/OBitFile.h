#pragma once
#include <ostream>
class OBitFile
{
public:
    OBitFile(std::ostream& ostream);
    ~OBitFile();
    void close();
    void putBit(unsigned char bit);
    void putBits(void* bitPtr, size_t count);
private:
    bool closed = false;
    std::ostream& _ostream;
    int incCurBitIndex();
    char _curByte = 0;
    long unsigned int _curBitIndex = 0;
};

