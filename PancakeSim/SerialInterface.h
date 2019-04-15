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
	SerialInterface(int port);

	~SerialInterface();

	bool TryConnection(std::string port);

	bool connect = false;

	void Send( std::string msg );
	void GetPositions();		//TODO: rename
	void GetButton();			//TODO: removed?

	// TODO: rename and combine POT's
	int* GetPot1() { return &pot1; };
	int GetPot2() { return pot2; };

	void Close();



private:
	serial::Serial* mySerial;

	//TODO: sort this out according to above TODO's
	int pot1 = 0;
	int pot2 = 0;
	int button1;
	int button2;
};