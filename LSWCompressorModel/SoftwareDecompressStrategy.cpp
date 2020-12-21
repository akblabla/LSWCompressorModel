#include "SoftwareDecompressStrategy.h"
#include "LZWGlobal.h"

static int hitCount = 0;
SoftwareDecompressStrategy::SoftwareDecompressStrategy()
{
}

int SoftwareDecompressStrategy::decompress(iAccess& src, iAccess& dst)
{
    unsigned int nextCode;              /* value of next code */
    unsigned int lastCode;              /* last decoded code word */
    unsigned int code;                  /* code word to decode */
    unsigned char currentCodeLen;       /* length of code words now */
    unsigned char c;                    /* last decoded character */
    decode_dictionary_t* dictionary = new decode_dictionary_t[(MAX_CODES - FIRST_CODE)];

    /* convert input file to bitfile */
    BitFileAccess bfpIn(&src, BitFileAccess::Mode::READ);

    /* start MIN_CODE_LEN bit code words */
    currentCodeLen = MIN_CODE_LEN;

    /* initialize for decoding */
    nextCode = FIRST_CODE;  /* code for next (first) string */

    /* first code from file must be a character.  use it for initial values */
    lastCode = GetCodeWord(bfpIn, currentCodeLen);
    c = lastCode;
    dst.putc(lastCode);

    /* decode rest of file */
    while ((int)(code = GetCodeWord(bfpIn, currentCodeLen)) != EOF)
    {

        /* look for code length increase marker */
        while (((CURRENT_MAX_CODES(currentCodeLen) - 1) == code) &&
            (currentCodeLen < MAX_CODE_LEN))
        {
            currentCodeLen++;
            code = GetCodeWord(bfpIn, currentCodeLen);
        }

        if (code < nextCode)
        {
            /* we have a known code.  decode it */
            c = DecodeRecursive(code, dst, dictionary);
        }
        else
        {
            /***************************************************************
            * We got a code that's not in our dictionary.  This must be due
            * to the string + char + string + char + string exception.
            * Build the decoded string using the last character + the
            * string from the last code.
            ***************************************************************/
            unsigned char tmp;

            tmp = c;
            c = DecodeRecursive(lastCode, dst, dictionary);
            dst.putc(tmp);
        }

        /* if room, add new code to the dictionary */
        if (nextCode < MAX_CODES)
        {
            dictionary[nextCode - FIRST_CODE].prefixCode = lastCode;
            dictionary[nextCode - FIRST_CODE].suffixChar = c;
            nextCode++;
        }

        /* save character and code for use in unknown code word case */
        lastCode = code;
    }
    delete[] dictionary;
	return 0;
}

unsigned char SoftwareDecompressStrategy::DecodeRecursive(unsigned int code, iAccess& dst, decode_dictionary_t* dictionary)
{
    unsigned char c;
    unsigned char firstChar;

    if (code >= FIRST_CODE)
    {
        /* code word is string + c */
        c = dictionary[code - FIRST_CODE].suffixChar;
        code = dictionary[code - FIRST_CODE].prefixCode;

        /* evaluate new code word for remaining string */
        firstChar = DecodeRecursive(code, dst,dictionary);
    }
    else
    {
        /* code word is just c */
        c = code;
        firstChar = code;
    }

    dst.putc(c);
    return firstChar;
}

int SoftwareDecompressStrategy::GetCodeWord(BitFileAccess& bfpiN, const unsigned char codeLen)
{
    int code = 0;
    int count;
    count = bfpiN.getBits(&code, codeLen);
    if (count < codeLen)
    {
        code = EOF;     /* BitFileGetBitsNum gives partial results at EOF */
    }
    hitCount++;
    return code;
}
