#include "Invoker.h"

Invoker::Invoker()
{
	
}

void Invoker::addCommand(iCommand* commandPtr)
{
	_mutex.lock();
	_commandPtrQueue.push(commandPtr);
	_mutex.unlock();
}

void Invoker::run()
{
	while(1){
		while (_commandPtrQueue.empty());
		_mutex.lock();
		auto commandPtr = _commandPtrQueue.front();
		_commandPtrQueue.pop();
		commandPtr->execute();
		_mutex.unlock();
	}
}
