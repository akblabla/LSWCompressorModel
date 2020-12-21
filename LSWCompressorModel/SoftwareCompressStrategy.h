#pragma once
#include "iCompressStrategy.h"
#include "BitFileAccess.h"

struct DictNode;
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

    /***************************************************************************
    *   Function   : MakeKey
    *   Description: This routine creates a simple key from a prefix code and
    *                an appended character.  The key may be used to establish
    *                an order when building/searching a dictionary tree.
    *   Parameters : prefixCode - code for all but the last character of a
    *                             string.
    *                suffixChar - the last character of a string
    *   Effects    : None
    *   Returned   : Key built from string represented as a prefix + char.  Key
    *                format is {ms nibble of c} + prefix + {ls nibble of c}
    ***************************************************************************/
    unsigned int MakeKey(const unsigned int prefixCode,
        const unsigned char suffixChar);

    /***************************************************************************
    *   Function   : MakeNode
    *   Description: This routine creates and initializes a dictionary entry
    *                for a string and the code word that encodes it.
    *   Parameters : codeWord - code word used to encode the string prefixCode +
    *                           suffixChar
    *                prefixCode - code for all but the last character of a
    *                             string.
    *                suffixChar - the last character of a string
    *   Effects    : Node is allocated for new dictionary entry
    *   Returned   : Pointer to newly allocated node or NULL on error.
    *                errno will be set on an error.
    ***************************************************************************/
    DictNode* MakeNode(const unsigned int codeWord,
        const unsigned int prefixCode, const unsigned char suffixChar);



    /***************************************************************************
    *   Function   : FreeTree
    *   Description: This routine will free all nodes of a tree rooted at the
    *                node past as a parameter.
    *   Parameters : node - root of tree to free
    *   Effects    : frees allocated tree node from initial parameter down.
    *   Returned   : none
    ***************************************************************************/
    void FreeTree(DictNode* node);

    /***************************************************************************
    *   Function   : FindDictionaryEntry
    *   Description: This routine searches the dictionary tree for an entry
    *                with a matching string (prefix code + suffix character).
    *                If one isn't found, the parent node for that string is
    *                returned.
    *   Parameters : prefixCode - code for the prefix of string
    *                c - last character in string
    *   Effects    : None
    *   Returned   : If string is in dictionary, pointer to node containing
    *                string, otherwise pointer to suitable parent node.  NULL
    *                is returned for an empty tree.
    ***************************************************************************/
    DictNode* findDictionaryEntry(DictNode* root,
        const int unsigned prefixCode, const unsigned char c);


    /* write encoded data */
    void putCodeWord(BitFileAccess &bfpOut, int code,
        const unsigned char codeLen);
};

