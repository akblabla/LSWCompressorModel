/*
 * ConsoleView.h
 *
 *  Created on: 7 Dec 2020
 *      Author: akbla
 */
#ifndef SRC_CONSOLEVIEW_H_
#define SRC_CONSOLEVIEW_H_
#include <string>
#include "ControllerClient.h"
#include "PopFrontQueue.h"
class ConsoleView {
public:
	ConsoleView(Controller& controllerParam);
	void interpretCommand(std::string s);
	virtual ~ConsoleView();
private:
	int splitCommand(const std::string& src, std::string& command, std::string& param);
	void read();
	void print();
	PopFrontQueue<std::string> _queue;
	std::thread _printerThread;
	std::thread _readerThread;
	Controller& _controller;
	ControllerClient _controllerClient;
};

#endif /* SRC_CONSOLEVIEW_H_ */
