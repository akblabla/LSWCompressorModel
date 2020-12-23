#include "SoftwareCompressStrategy.h"
#include "LZWGlobal.h"
#include "OBitFile.h"
static int hitCount = 0;


/***************************************************************************
*                            TYPE DEFINITIONS
***************************************************************************/
/* node in dictionary tree */
typedef struct DictNode
{
    unsigned int codeWord;      /* code word for this entry */
    unsigned char suffixChar;   /* last char in encoded string */
    unsigned int prefixCode;    /* code for remaining chars in string */

    /* pointer to child nodes */
    struct DictNode* left;   /* child with < key */
    struct DictNode* right;  /* child with >= key */
} DictNode;


SoftwareCompressStrategy::SoftwareCompressStrategy()
{
}

int SoftwareCompressStrategy::compress(std::istream& src, std::ostream& dst)
{
    unsigned int code;                  /* code for current string */
    unsigned char currentCodeLen;       /* length of the current code */
    unsigned int nextCode;              /* next available code index */
    int c;                              /* character to add to string */

    DictNode* dictRoot;              /* root of dictionary tree */
    DictNode* node;                  /* node of dictionary tree */

    OBitFile bfpOut(dst);

    /* initialize dictionary as empty */
    dictRoot = NULL;

    /* start MIN_CODE_LEN bit code words */
    currentCodeLen = MIN_CODE_LEN;

    nextCode = FIRST_CODE;  /* code for next (first) string */

    /* now start the actual encoding process */

    c = src.get();
    if (EOF == c)
    {
        return -1;      /* empty file */
    }
    else
    {
        code = c;       /* start with code string = first character */
    }

    /* create a tree root from 1st 2 character string */
    if ((c = src.get()) != EOF)
    {
        /* special case for NULL root */
        dictRoot = MakeNode(nextCode, code, c);

        if (NULL == dictRoot)
        {
            perror("Making Dictionary Root");
            return -1;
        }

        nextCode++;

        /* write code for 1st char */
        putCodeWord(bfpOut, code, currentCodeLen);

        /* new code is just 2nd char */
        code = c;
    }

    /* now encode normally */
    while ((c = src.get()) != EOF)
    {
        /* look for code + c in the dictionary */
        node = findDictionaryEntry(dictRoot, code, c);

        if ((node->prefixCode == code) &&
            (node->suffixChar == c))
        {
            /* code + c is in the dictionary, make it's code the new code */
            code = node->codeWord;
        }
        else
        {
            /* code + c is not in the dictionary, add it if there's room */
            if (nextCode < MAX_CODES)
            {
                DictNode* tmp;

                tmp = MakeNode(nextCode, code, c);

                if (NULL == dictRoot)
                {
                    perror("Making Dictionary Node");
                    FreeTree(dictRoot);
                    return -1;
                }

                nextCode++;

                if (MakeKey(code, c) <
                    MakeKey(node->prefixCode, node->suffixChar))
                {
                    node->left = tmp;
                }
                else
                {
                    node->right = tmp;
                }
            }
            else
            {
                fprintf(stderr, "Error: Dictionary Full\n");
            }

            /* are we using enough bits to write out this code word? */
            while ((code >= (CURRENT_MAX_CODES(currentCodeLen) - 1)) &&
                (currentCodeLen < MAX_CODE_LEN))
            {
                /* mark need for bigger code word with all ones */
                putCodeWord(bfpOut, (CURRENT_MAX_CODES(currentCodeLen) - 1),
                    currentCodeLen);
                currentCodeLen++;
            }

            /* write out code for the string before c was added */
            putCodeWord(bfpOut, code, currentCodeLen);

            /* new code is just c */
            code = c;
        }
    }

    /* no more input.  write out last of the code. */
    putCodeWord(bfpOut, code, currentCodeLen);

    /* free the dictionary */
    FreeTree(dictRoot);
    return 0;
}

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
unsigned int SoftwareCompressStrategy::MakeKey(const unsigned int prefixCode,
    const unsigned char suffixChar)
{
    unsigned int key;

    /* position ms nibble */
    key = suffixChar & 0xF0;
    key <<= MAX_CODE_LEN;

    /* include prefix code */
    key |= (prefixCode << 4);

    /* inclulde ls nibble */
    key |= (suffixChar & 0x0F);

    return key;
}

DictNode* SoftwareCompressStrategy::MakeNode(const unsigned int codeWord,
    const unsigned int prefixCode, const unsigned char suffixChar)
{
    DictNode* node;

    node = (DictNode*)malloc(sizeof(DictNode));

    if (NULL != node)
    {
        node->codeWord = codeWord;
        node->prefixCode = prefixCode;
        node->suffixChar = suffixChar;

        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void SoftwareCompressStrategy::FreeTree(DictNode* node)
{
    if (NULL == node)
    {
        /* nothing to free */
        return;
    }

    /* free left branch */
    if (node->left != NULL)
    {
        FreeTree(node->left);
    }

    /* free right branch */
    if (node->right != NULL)
    {
        FreeTree(node->right);
    }

    /* free root */
    free(node);
}


DictNode* SoftwareCompressStrategy::findDictionaryEntry(DictNode* root,
    const int unsigned prefixCode, const unsigned char c)
{
    unsigned int searchKey, key;

    if (NULL == root)
    {
        return NULL;
    }

    searchKey = MakeKey(prefixCode, c);     /* key of string to find */

    while (1)
    {
        /* key of current node */
        key = MakeKey(root->prefixCode, root->suffixChar);

        if (key == searchKey)
        {
            /* current node contains string */
            return root;
        }
        else if (searchKey < key)
        {
            if (NULL != root->left)
            {
                /* check left branch for string */
                root = root->left;
            }
            else
            {
                /* string isn't in tree, it can be added as a left child */
                return root;
            }
        }
        else
        {
            if (NULL != root->right)
            {
                /* check right branch for string */
                root = root->right;
            }
            else
            {
                /* string isn't in tree, it can be added as a right child */
                return root;
            }
        }
    }
}

/***************************************************************************
*   Function   : PutCodeWord
*   Description: This function writes a code word from to an encoded file.
*                In order to deal with endian issue the code word is
*                written least significant byte followed by the remaining
*                bits.
*   Parameters : bfpOut - bit file containing the encoded data
*                code - code word to add to the encoded data
*                codeLen - length of the code word
*   Effects    : code word is written to the encoded output
*   Returned   : EOF for failure, ENOTSUP unsupported architecture,
*                otherwise the number of bits written.  If an error occurs
*                after a partial write, the partially written bits will not
*                be unwritten.
***************************************************************************/
void SoftwareCompressStrategy::putCodeWord(OBitFile& bfpOut, int code, const unsigned char codeLen)
{
	bfpOut.putBits(&code, codeLen);
    hitCount++;
}



