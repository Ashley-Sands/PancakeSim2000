#include "stdafx.h"
#include "SerialInterface.h"
#include <iostream>

#include "GameObjects/Components/Debug/Console.h"
#include "GameObjects/Components/Time.h"			//use time to sync the timeout with the frame rate :)
#include "GameObjects/Components/Vector2.h"
#include "GameObjects/Components/InputDataTypes/InputData.h"
#include "GameObjects/Components/InputDataTypes/InputData_single.h"

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

	for (int i = 0; i < TOTAL_VECT_POTS; i++)
		pot[i] = new InputData();

	ERROR_POT = new InputData();
	pot_single = new InputData_single();

}



SerialInterface::SerialInterface(int port)
{
	std::string comPort = "COM" + std::to_string(port);
	TryConnection(comPort);

	for (int i = 0; i < TOTAL_VECT_POTS; i++)
		pot[i] = new InputData();

	ERROR_POT = new InputData();
	pot_single = new InputData_single();

}


SerialInterface::~SerialInterface()
{

	delete[] &pot;

}

bool SerialInterface::TryConnection(std::string port)
{

	try {
		mySerial = new serial::Serial(port, 9600, serial::Timeout::simpleTimeout( ceil( Time::GetTicksPerUpdate() * 2.0f ) ));

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
		mySerial->write("I");	//Get the values normalized for the controller :)

		std::string result = mySerial->readline();

		Console::LogMessage(MessageType::Log, "Read Value: " + result );

		if (result.length() > 0) { //TODO: give me the real value

			int currentStrPos = 0;
			std::string sub;

			try {

				// Build the input date
				for (int i = 0; i < TOTAL_VECT_POTS; i++)
				{
					// gryo-x
					sub = result.substr(currentStrPos, INPUT_LEN);
					pot[i]->GetGyroAxis()->x = std::stoi(sub);

					currentStrPos += INPUT_LEN + INPUT_SPACING;

					// gryo-y
					sub = result.substr(currentStrPos, INPUT_LEN);
					pot[i]->GetGyroAxis()->y = std::stoi(sub);

					currentStrPos += INPUT_LEN + INPUT_SPACING;

					// LDR - onHob
					sub = result.substr(currentStrPos, INPUT_LEN);
					pot[i]->SetHobValue(std::stoi(sub));

					currentStrPos += INPUT_LEN + INPUT_SPACING;

					// heat nob
					sub = result.substr(currentStrPos, INPUT_LEN);
					pot[i]->SetHobFire(std::stoi(sub));

					currentStrPos += INPUT_LEN + INPUT_SPACING;

				}

				//Whisk
				sub = result.substr(currentStrPos, INPUT_LEN);
				pot_single->SetWhisking(std::stoi(sub));

				currentStrPos += INPUT_LEN + INPUT_SPACING;

			}
			catch (std::exception &e)
			{
				Console::LogMessage(MessageType::Error, "E_Value: " + result + " : LEN: " + std::to_string(result.length()));
			}
		}

		

	}
}

InputData* SerialInterface::GetPot(int id)
{

	if (id >= 0 && id < TOTAL_VECT_POTS)
	{
		return pot[id];
	}
	else
	{
		Console::LogMessage(MessageType::Error, "Pot not found (id: " + std::to_string(id) + ")");
		return ERROR_POT;
	}

}

InputData_single* SerialInterface::GetSinglePot()
{
	return pot_single;
}

void SerialInterface::Close()
{
	mySerial->flush();
	mySerial->close();
}