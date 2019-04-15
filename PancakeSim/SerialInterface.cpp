#include "stdafx.h"
#include "SerialInterface.h"
#include <iostream>

#include "GameObjects/Components/Debug/Console.h"
#include "GameObjects/Components/Time.h"			//use time to sync the timeout with the frame rate :)


SerialInterface::SerialInterface()
{
	std::vector <serial::PortInfo> devicesFound = serial::list_ports();

	std::vector <serial::PortInfo>::iterator iter = devicesFound.begin();

	while (iter != devicesFound.end())
	{
		serial::PortInfo device = *iter++;
		std::string port = device.port.c_str();

		if (TryConnection(port))
			break;

	}
}



SerialInterface::SerialInterface(int port)
{
	std::string comPort = "COM" + std::to_string(port);
	TryConnection(comPort);
}


SerialInterface::~SerialInterface()
{}
bool SerialInterface::TryConnection(std::string port)
{
	try {
		mySerial = new serial::Serial(port, 9600, serial::Timeout::simpleTimeout( floor(Time::GetTicksPerUpdate())-1 ));

		if (mySerial->isOpen())
		{
			std::cout << "Connection success: " << port << "\n";
			connect = true;
			return true;
		}
	}
	catch (std::exception &e) {

	}

	std::cout << "Failed to connecnt to " << port << "\n";
	return false;

}

void SerialInterface::Send(std::string msg)
{
	if (connect)
	{
		mySerial->write(msg);
	}
}

void SerialInterface::GetButton()
{
	if (connect)
	{
		mySerial->write("B");

		std::string result = mySerial->readline();

		std::string b1 = result.substr(0, 1);
		std::string b2 = result.substr(2, 1);

		button1 = std::stoi(b1);
		button2 = std::stoi(b2);

	}
}

void SerialInterface::GetPositions()
{
	if (connect)
	{
		mySerial->write("I");

		std::string result = mySerial->readline();

		//std::cout << result << std::endl;

		Console::LogMessage(MessageType::Log, "Read Value: " + result );

		if (result.length() > 6) {
			std::string sub1 = result.substr(0, 7);
			Console::LogMessage(MessageType::Log, "@Read Value: " + sub1 + " : LEN: " + std::to_string(result.length()));

			try {
				pot1 = std::stoi(sub1);
			}
			catch(std::exception &e)
			{
				Console::LogMessage(MessageType::Error, "E_Value: " + result + " : LEN: "+ std::to_string(result.length()) );
			}
/*
			std::string sub2 = result.substr(5, 9);
			pot2 = std::stoi(sub2);
*/
		}

	}
}

int* SerialInterface::GetPot(int id)
{
	switch (id)
	{
		case 1:
			return &pot1;
		case 2:
			return &pot2;
		default:
			Console::LogMessage(MessageType::Error, "Pot not found (id: "+std::to_string(id)+")");
			return &ERROR_POT;


	}
}

void SerialInterface::Close()
{
	mySerial->flush();
	mySerial->close();
}