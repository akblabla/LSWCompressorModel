#include "ControllerClient.h"

ControllerClient::ControllerClient(Controller& controller) : _controllerPtr(&controller), _thread(&Invoker::run,&_invoker)
{

}

void ControllerClient::compress(std::string s)
{
	_invoker.addCommand(new CompressCommand(_controllerPtr,s));
}

void ControllerClient::decompress(std::string s)
{
	_invoker.addCommand(new DecompressCommand(_controllerPtr,s));
}

void ControllerClient::print(std::string s)
{
	_invoker.addCommand(new PrintCommand(_controllerPtr,s));
}

void ControllerClient::subscribe(PopFrontQueue<std::string>& queue)
{
	_invoker.addCommand(new SubscribeCommand(_controllerPtr,queue));
}

ControllerClient::CompressCommand::CompressCommand(Controller* controllerPtr, std::string s) : _controllerPtr(controllerPtr)
{
	_s = s;
}

void ControllerClient::CompressCommand::execute()
{
	_controllerPtr->compress(_s);
}

ControllerClient::DecompressCommand::DecompressCommand(Controller* controllerPtr, std::string s) : _controllerPtr(controllerPtr)
{
	_s = s;
}

void ControllerClient::DecompressCommand::execute()
{
	_controllerPtr->decompress(_s);
}

ControllerClient::PrintCommand::PrintCommand(Controller* controllerPtr, std::string s) : _controllerPtr(controllerPtr)
{
	_s = s;
}

void ControllerClient::PrintCommand::execute()
{
	_controllerPtr->print(_s);
}

ControllerClient::SubscribeCommand::SubscribeCommand(Controller* controllerPtr, PopFrontQueue<std::string>& queue) : _controllerPtr(controllerPtr), _queue(queue)
{
}

void ControllerClient::SubscribeCommand::execute()
{
	_controllerPtr->subscribe(_queue);
}
