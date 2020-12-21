#pragma once
#include<string>
#include<queue>
#include <thread>
#include"iController.h"
#include"Controller.h"
#include "iCommand.h"
#include "Invoker.h"
class ControllerClient : iController
{
public:
	ControllerClient(Controller& controller);
	void compress(std::string s);
	void decompress(std::string s);
	void print(std::string s);
	void subscribe(PopFrontQueue<std::string>& queue);
private:
	Controller* const _controllerPtr;
	Invoker _invoker;
	std::thread _thread;
	class CompressCommand : public iCommand
	{
	public:
		CompressCommand(Controller* controllerPtr, std::string s);
		void execute();
	private:
		Controller* const _controllerPtr;
		std::string _s;
	};
	class DecompressCommand : public iCommand
	{
	public:
		DecompressCommand(Controller* controllerPtr, std::string s);
		void execute();
	private:
		Controller* const _controllerPtr;
		std::string _s;
	};
	class PrintCommand : public iCommand
	{
	public:
		PrintCommand(Controller* controllerPtr, std::string s);
		void execute();
	private:
		Controller* const _controllerPtr;
		std::string _s;
	};
	class SubscribeCommand : public iCommand
	{
	public:
		SubscribeCommand(Controller* controllerPtr, PopFrontQueue<std::string>& queue);
		void execute();
	private:
		Controller* const _controllerPtr;
		PopFrontQueue<std::string>& _queue;
	};
};

