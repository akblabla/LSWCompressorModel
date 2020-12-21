#pragma once
#include <queue>
#include "iCommand.h"
#include <mutex>
class Invoker
{
public:
	Invoker();
	void addCommand(iCommand*);
	void run();
private:
	std::queue<iCommand*> _commandPtrQueue;
	std::mutex _mutex;
};

