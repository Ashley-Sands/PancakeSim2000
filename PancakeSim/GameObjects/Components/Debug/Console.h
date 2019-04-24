#pragma once
#include <string>

enum MessageType {Log, Warning, Error};

class Console
{
public:
	Console();
	~Console();

	static void LogMessage(MessageType messageType, std::string message);
	static void Disable(bool disable);

private:
	static bool disableConsole;

};

