#include "DictNode.h"
#include "Dictionary.h"

DictNode::DictNode(unsigned int codeWord, unsigned char suffixChar, char prefixChar, Dictionary& dictionary) :
	_codeWord(codeWord),
	_suffixChar(suffixChar),
	_prefixChar(prefixChar),
	_dictionary(dictionary)
{
	_arraySize = 2;
}

DictNode::DictNode(unsigned int codeWord, unsigned char suffixChar, DictNode& prefixNode, Dictionary& dictionary) :
	_codeWord(codeWord),
	_suffixChar(suffixChar),
	_prefixNode(&prefixNode),
	_dictionary(dictionary)
{
	_arraySize = prefixNode.getArraySize() + 1;
}

DictNode::~DictNode()
{
	delete _left;
	delete _right;
}

/*
We sort arrays by size, but if they are of equal size, we sort them by their size, as if interpreted as integer values.
*/

bool DictNode::findDictionaryEntry(unsigned int& codeWord, DictNode*& dictNode, const unsigned char* arrayPtr, unsigned int arraySize)
{
	if (arraySize == 1){
		return false;
	}
	DictNode* directionPtr = nullptr;
	int comparison = compareArray(arrayPtr, arraySize);
	if (comparison == 0){
		dictNode = this;
		codeWord = _codeWord;
		return false;
	}
	else if (comparison<0)
		directionPtr = _left;
	else
		directionPtr = _right;
	
	if (directionPtr == nullptr){
		if (arraySize>2){
			addChild(arrayPtr, arraySize);
			_dictionary._rootPtr->findDictionaryEntry(codeWord, dictNode, arrayPtr, arraySize - 1);
		}
		else
		{
			addChild(arrayPtr, arraySize);
			codeWord = arrayPtr[0];
		}
		return true;
	}
	return directionPtr->findDictionaryEntry(codeWord,dictNode,arrayPtr, arraySize);
}

void DictNode::getArray(unsigned char* arrayPtr)
{
	if (_prefixNode == nullptr)
		arrayPtr[0] = _prefixChar;
	else
		_prefixNode->getArray(arrayPtr);
		arrayPtr[_arraySize-1] = _suffixChar;

}

unsigned int DictNode::getArraySize()
{
	return _arraySize;
}

void DictNode::addChild(const unsigned char* arrayPtr, unsigned int arraySize)
{
	bool comparison = compareArray(arrayPtr, arraySize);
	if (comparison<0) {
		setLeftChild(arrayPtr, arraySize);
	}
	else {
		setRightChild(arrayPtr, arraySize);
	}
}

void DictNode::setLeftChild(const unsigned char* arrayPtr, unsigned int arraySize)
{
	if (_left == nullptr){
		DictNode* prefixNode = nullptr;
		unsigned int dontCare;
		_dictionary._rootPtr->findDictionaryEntry(dontCare, prefixNode, arrayPtr, arraySize - 1);
		if (prefixNode == nullptr)
			_left = new DictNode(_dictionary.getNextCodeWord(), arrayPtr[arraySize - 1], arrayPtr[0], _dictionary);
		else
			_left = new DictNode(_dictionary.getNextCodeWord(), arrayPtr[arraySize - 1], *prefixNode, _dictionary);
	}
	else
	_left->addChild(arrayPtr, arraySize);
}

void DictNode::setRightChild(const unsigned char* arrayPtr, unsigned int arraySize)
{
	if (_right == nullptr) {
		DictNode* prefixNode = nullptr;
		unsigned int dontCare;
		_dictionary._rootPtr->findDictionaryEntry(dontCare, prefixNode, arrayPtr, arraySize - 1);
		if (prefixNode == nullptr)
			_right = new DictNode(_dictionary.getNextCodeWord(), arrayPtr[arraySize - 1], arrayPtr[0], _dictionary);
		else
			_right = new DictNode(_dictionary.getNextCodeWord(), arrayPtr[arraySize - 1], *prefixNode, _dictionary);
	}
	else
		_right->addChild(arrayPtr, arraySize);
}

int DictNode::compareArray(const unsigned char* arrayPtr, unsigned int arraySize)
{
	const unsigned char* arrayAPtr = arrayPtr;
	size_t arrayASize = arraySize;
	size_t arrayBSize = getArraySize();
	unsigned char* arrayBPtr = new unsigned char[arrayBSize];
	getArray(arrayBPtr);
	size_t minArraySize = arrayASize;
	if (arrayBSize < minArraySize) minArraySize = arrayBSize;

	for (int i = minArraySize -1; i >= 0; --i) {
		if (arrayAPtr[i] != arrayBPtr[i]) {
			if (arrayAPtr[i] < arrayBPtr[i])
				return -1;
			else
				return 1;
		}
	}
	if (arrayASize < arrayBSize)
		return -1;
	else if (arrayASize > arrayBSize)
		return 1;
	
	return 0;
}

