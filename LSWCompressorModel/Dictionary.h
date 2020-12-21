#pragma once
class DictNode;
class Dictionary
{
public:
	Dictionary();
	bool findCodeWord(unsigned int& codeWord, unsigned char* arrayPtr, unsigned int arraySize);
private:
	int getNextCodeWord();
	friend class DictNode;
	DictNode* _rootPtr = nullptr;
	int _currentBiggestCodeWord = 255;
};

