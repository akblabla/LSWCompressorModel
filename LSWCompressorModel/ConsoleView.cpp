/*
 * ConsoleView.cpp
 *
 *  Created on: 7 Dec 2020
 *      Author: akbla
 */

#include "ConsoleView.h"
#include <iostream>

ConsoleView::ConsoleView(Controller& controllerParam) :
    _controller(controllerParam),
    _controllerClient(controllerParam),
    _readerThread(&ConsoleView::read, this),
    _printerThread(&ConsoleView::print, this)
{
	_controller.subscribe(_queue);
}

void ConsoleView::interpretCommand(std::string s)
{
    std::string command;
    std::string param;
    if (splitCommand(s, command, param) == -1) std::cout<<'"'<<s<< '"' <<" does not have parameters" << std::endl;
    if (command == "compress")
        _controllerClient.compress(param);
    if (command == "decompress")
        _controllerClient.decompress(param);
}

ConsoleView::~ConsoleView() {
	// TODO Auto-generated destructor stub
}

void ConsoleView::read()
{
    for (std::string line; std::cout << "" && std::getline(std::cin, line); )
    {
        if (!line.empty()) { interpretCommand(line); }
    }
}

int ConsoleView::splitCommand(const std::string& src, std::string& command, std::string& param)
{
    size_t commandLength = src.find_first_of(" ");
    if (commandLength == std::string::npos) return -1;
    command.assign(src,0,commandLength);
    param.assign(src, commandLength+1, SIZE_MAX);
    return 0;
}

void ConsoleView::print()
{
    while (1) {
        while (_queue.empty());
        std::cout<<_queue.pop_front();
    }
}

