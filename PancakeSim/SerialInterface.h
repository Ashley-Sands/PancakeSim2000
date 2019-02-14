#pragma once

#include <serial\serial.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

class SerialInterface
{
public:
	SerialInterface();
	~SerialInterface();

	bool connect = false;

	void Send( std::string msg );
	void GetPositions();
	void GetButton();

	int GetPot1() { return pot1; };
	int GetPot2() { return pot2; };

	void Close();



private:
	serial::Serial* mySerial;


	int pot1 = 0;
	int pot2 = 0;
	int button1;
	int button2;
};