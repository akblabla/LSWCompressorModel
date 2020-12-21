#include "Dictionary.h"
#include "DictNode.h"


Dictionary::Dictionary()
{
}

bool Dictionary::findCodeWord(unsigned int& codeWord, unsigned char* arrayPtr, unsigned int arraySize)
{
	if (arraySize == 1) {
		codeWord = arrayPtr[0];
		return false;
	}
	if (_rootPtr == nullptr)
	{
		_rootPtr = new DictNode(++_currentBiggestCodeWord, arrayPtr[arraySize-1], arrayPtr[0],*this);
		codeWord = arrayPtr[0];
		return true;
	}
	DictNode* dictNodePtr;
	bool result = _rootPtr->findDictionaryEntry(codeWord,dictNodePtr,arrayPtr, arraySize);
	return result;
}

unsigned int Dictionary::getNextCodeWord()
{
	_currentBiggestCodeWord++;
	return _currentBiggestCodeWord;
}
