#pragma once

#include <serial\serial.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

#include "GameObjects/Components/Vector2.h"

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


	Vector2* GetPot(int id);

	void Close();



private:
	serial::Serial* mySerial;

	const int INPUT_LEN = 7;
	const int INPUT_SPACING = 1;

	static const int TOTAL_VECT_POTS = 1;
	Vector2* pot[TOTAL_VECT_POTS];

	Vector2* ERROR_POT;		// prevent errors (this will never be updated)




	//TODO: sort this out according to above TODO's
	//?????
	int button1;
	int button2;
};