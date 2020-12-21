#pragma once
#include "iDecompressStrategy.h"
#include "BitFileAccess.h"
typedef struct
{
	unsigned char suffixChar;   /* last char in encoded string */
	unsigned int prefixCode;    /* code for remaining chars in string */
} decode_dictionary_t;

class SoftwareDecompressStrategy :
	public iDecompressStrategy
{
public:
	SoftwareDecompressStrategy();
	int decompress(iAccess& src, iAccess& dst);
private:
	/***************************************************************************
	*   Function   : DecodeRecursive
	*   Description: This function uses the dictionary to decode a code word
	*                into the string it represents and write it to the output
	*                file.  The string is actually built in reverse order and
	*                recursion is used to write it out in the correct order.
	*   Parameters : code - the code word to decode
	*                fpOut - the file that the decoded code word is written to
	*   Effects    : Decoded code word is written to a file
	*   Returned   : The first character in the decoded string
	***************************************************************************/
	unsigned char DecodeRecursive(unsigned int code, iAccess& dst, decode_dictionary_t* dictionary);

	/***************************************************************************
	*   Function   : GetCodeWord
	*   Description: This function reads and returns a code word from an
	*                encoded file.  In order to deal with endian issue the
	*                code word is read least significant byte followed by the
	*                remaining bits.
	*   Parameters : bfpIn - bit file containing the encoded data
	*                codeLen - number of bits in code word
	*   Effects    : code word is read from encoded input
	*   Returned   : The next code word in the encoded file.  EOF if the end
	*                of file has been reached.
	*
	*   NOTE: If the code word contains more than 16 bits, this routine should
	*         be modified to read in all the bytes from least significant to
	*         most significant followed by any left over bits.
	***************************************************************************/
	int GetCodeWord(BitFileAccess& bfpiN, const unsigned char codeLen);
};

