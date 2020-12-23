#include <iostream>
#include "ConsoleView.h"
#include "ControllerFactory.h"
#include <thread>
#include "test.h"
#include "Dictionary.h"
int main()
{
    test();
    std::cout << "type something" << std::endl;
    Controller controller = ControllerFactory::createController();
    ConsoleView consoleView(controller);
    while (1);
}