#include "stdafx.h"
#include "SerialInterface.h"
#include <iostream>

SerialInterface::SerialInterface()
{
	
	std::vector <serial::PortInfo> devicesFound = serial::list_ports();
	std::vector <serial::PortInfo>::iterator iter = devicesFound.begin();

	while (iter != devicesFound.end())
	{
		serial::PortInfo device = *iter++;
		std::string port = device.port.c_str();
		if (port == "COM1") continue;	// I have somthnk on COM1
		try {
			mySerial = new serial::Serial( port, 9600, serial::Timeout::simpleTimeout( 250 ) );

			if (mySerial->isOpen())
			{
				std::cout << "Connection success: " << port << "\n";
				connect = true;

				break;
			}
		}
		catch (std::exception &e) {

		}
	}
	
}
SerialInterface::~SerialInterface()
{

}

void SerialInterface::Send( std::string msg )
{
	if (connect)
	{
		mySerial->write( msg );
	}
}

void SerialInterface::GetButton()
{
	if (connect)
	{
		mySerial->write( "B" );

		std::string result = mySerial->readline();

		//std::vector<std::string> pos = split(result, ';');

		std::string b1 = result.substr( 0, 1 );
		std::string b2 = result.substr( 2, 1 );

		button1 = std::stoi( b1 );
		button2 = std::stoi( b2 );
		//std::cout << button1 << std::endl;
	}
}

void SerialInterface::GetPositions()
{
	if (connect)
	{
		mySerial->write( "P" );		// Send a message to the controler so it knows we need an input

		std::string result = mySerial->readline();

		if (result.length() > 5) {
			std::string sub1 = result.substr( 0, 4 );		// get chars 0 to 4 from string for input 
			pot1 = std::stoi( sub1 );						// Convert to int.

			std::string sub2 = result.substr( 5, 9 );		// get chars 5 to 9 from string for input 
			pot2 = std::stoi( sub2 );
		}

	}
}  

void SerialInterface::Close()
{
	mySerial->flush();
	mySerial->close();
}