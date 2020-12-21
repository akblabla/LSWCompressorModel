#include "dictionaryTest.h"
#include "Dictionary.h"
#include <cassert>
void dictionaryTest()
{
	Dictionary dict;
	unsigned char data[18] = "this_is_his_thing";
	unsigned char* dataPtr = data;
	unsigned int codeWord = 0;
	bool isNewCode = dict.findCodeWord(codeWord, dataPtr, 1);
	assert(isNewCode == false);

	isNewCode = dict.findCodeWord(codeWord, dataPtr, 2);
	assert(isNewCode == true);
	assert(codeWord == 't');
	dataPtr++;

	isNewCode = dict.findCodeWord(codeWord, dataPtr, 2);
	assert(isNewCode == true);
	assert(codeWord == 'h');
	dataPtr++;

	isNewCode = dict.findCodeWord(codeWord, dataPtr, 2);
	assert(isNewCode == true);
	assert(codeWord == 'i');
	dataPtr++;

	isNewCode = dict.findCodeWord(codeWord, dataPtr, 2);
	assert(isNewCode == true);
	assert(codeWord == 's');
	dataPtr++;

	isNewCode = dict.findCodeWord(codeWord, dataPtr, 2);
	assert(isNewCode == true);
	assert(codeWord == '_');
	dataPtr++;

	isNewCode = dict.findCodeWord(codeWord, dataPtr, 2);
	assert(isNewCode == false);
	isNewCode = dict.findCodeWord(codeWord, dataPtr, 3);
	assert(isNewCode == true);
	assert(codeWord == 258);
	dataPtr++;
	dataPtr++;

	isNewCode = dict.findCodeWord(codeWord, dataPtr, 2);
	assert(isNewCode == true);
	assert(codeWord == '_');
	dataPtr++;

	isNewCode = dict.findCodeWord(codeWord, dataPtr, 2);
	assert(isNewCode == false);
	isNewCode = dict.findCodeWord(codeWord, dataPtr, 3);
	assert(isNewCode == true);
	assert(codeWord == 257);
	dataPtr++;
	dataPtr++;

}
