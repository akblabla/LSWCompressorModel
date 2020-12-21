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
	DictNode* directionPtr = nullptr;
	if (arraySize < getArraySize())
		directionPtr = _left;
	else if (arraySize > getArraySize())
		directionPtr = _right;
	else
	{
		unsigned char* arrayOfNodePtr = new unsigned char[getArraySize()];
		getArray(arrayOfNodePtr);
		int comparison = compareArray(arrayPtr, arrayOfNodePtr, getArraySize());
		if (comparison == 0){
			dictNode = this;
			return false;
		}
		else if (comparison<0)
			directionPtr = _left;
		else
			directionPtr = _right;
	}
	if (directionPtr == nullptr){
		if (arraySize>2){
			DictNode* prefixNode;
			_dictionary._rootPtr->findDictionaryEntry(codeWord, prefixNode, arrayPtr, arraySize-1);
			addChild(_dictionary.getNextCodeWord(), arrayPtr[arraySize-1], *prefixNode);
			dictNode = this;
			codeWord = _codeWord;
		}
		else
		{
			addChild(_dictionary.getNextCodeWord(), arrayPtr[arraySize - 1], arrayPtr[0]);
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

void DictNode::addChild(unsigned int codeWord, unsigned char suffixChar, DictNode& prefixNode)
{
	bool comparison = compareArray(const unsigned char* arrayAPtr, const unsigned char* arrayBPtr, unsigned int arraySize)
	if (codeWord < _codeWord) {
		setLeftChild(codeWord, suffixChar, prefixNode);
	}
	else {
		setRightChild(codeWord, suffixChar, prefixNode);
	}
}

void DictNode::setLeftChild(unsigned int codeWord, unsigned char suffixChar, DictNode& prefixNode)
{
	if (_left == nullptr)
	_left = new DictNode(codeWord, suffixChar, prefixNode, _dictionary);
	else
	_left->addChild(codeWord, suffixChar, prefixNode);
}

void DictNode::setRightChild(unsigned int codeWord, unsigned char suffixChar, DictNode& prefixNode)
{
	if (_right == nullptr)
		_right = new DictNode(codeWord, suffixChar, prefixNode,_dictionary);
	else
		_right->addChild(codeWord, suffixChar, prefixNode);
}

void DictNode::addChild(unsigned int codeWord, unsigned char suffixChar, unsigned char prefixChar)
{
	if (codeWord < _codeWord) {
		setLeftChild(codeWord, suffixChar, prefixChar);
	}
	else {
		setRightChild(codeWord, suffixChar, prefixChar);
	}
}

void DictNode::setLeftChild(unsigned int codeWord, unsigned char suffixChar, unsigned char prefixChar)
{
	if (_left == nullptr)
		_left = new DictNode(codeWord, suffixChar, prefixChar, _dictionary);
	else
		_left->addChild(codeWord, suffixChar, prefixChar);
}

void DictNode::setRightChild(unsigned int codeWord, unsigned char suffixChar, unsigned char prefixChar)
{
	if (_right == nullptr)
		_right = new DictNode(codeWord, suffixChar, prefixChar, _dictionary);
	else
		_right->addChild(codeWord, suffixChar, prefixChar);
}

int DictNode::compareArray(const unsigned char* arrayAPtr, const unsigned char* arrayBPtr, unsigned int arraySize)
{
	for (size_t i = 0; i < arraySize; ++i) {
		if (arrayAPtr[i] != arrayBPtr[i]) {
			if (arrayAPtr[i] > arrayBPtr[i])
				return 1;
			else
				return -1;
		}
	}
	return 0;
}

