#pragma once
class Dictionary;
class DictNode
{
public:
    DictNode(unsigned int codeWord, unsigned char suffixChar, char prefixChar, Dictionary& dictionary);
    DictNode(unsigned int codeWord, unsigned char suffixChar, DictNode& _prefixNode, Dictionary& dictionary);
    ~DictNode();
    bool findDictionaryEntry(unsigned int& codeWord, DictNode*& dictNode, const unsigned char* arrayPtr, unsigned int arraySize);
    void getArray(unsigned char* arrayPtr);
    unsigned int getArraySize();
    
    void addChild(unsigned int codeWord, unsigned char suffixChar, unsigned char prefixChar);
    void addChild(unsigned int codeWord, unsigned char suffixChar, DictNode& prefixNode);

    const unsigned int _codeWord;      /* code word for this entry */
    const unsigned char _suffixChar;   /* last char in encoded string */
private:


    void setLeftChild(unsigned int codeWord, unsigned char suffixChar, unsigned char prefixChar);
    void setLeftChild(unsigned int codeWord, unsigned char suffixChar, DictNode& prefixNode);

    void setRightChild(unsigned int codeWord, unsigned char suffixChar, unsigned char prefixChar);
    void setRightChild(unsigned int codeWord, unsigned char suffixChar, DictNode& prefixNode);

    int compareArray(const unsigned char* arrayAPtr, const unsigned char* arrayBPtr, unsigned int arraySize);
    unsigned int _arraySize;
    DictNode* const _prefixNode = nullptr;   /* child with < key */
    const char _prefixChar = 0;   /* child with < key */
    /* pointer to child nodes */
    DictNode* _left = nullptr;   /* child with < key */
    DictNode* _right = nullptr;  /* child with >= key */
    Dictionary& _dictionary;
};

