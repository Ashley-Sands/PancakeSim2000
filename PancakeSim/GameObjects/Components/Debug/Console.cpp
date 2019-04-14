#include "Console.h"
#include <iostream>




Console::Console(){}


Console::~Console(){}

void Console::LogMessage(MessageType messType, std::string message)
{
	
	switch (messType)
	{
		case MessageType::Log:
			std::cout << "[LOG] \t\t"<< message << "\n";
			break;
		case MessageType::Warning:
			std::cout << "[Warning] \t"<< message << "\n";
			break;
		case MessageType::Error:
			std::cout << "[ERROR] \t"<< message << "\n";
			break;
	}


}
