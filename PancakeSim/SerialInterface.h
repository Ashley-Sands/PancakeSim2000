#pragma once

#include <serial\serial.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

class InputData;
class InputData_single;

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

	InputData* GetPot(int id);
	InputData_single* GetSinglePot();

	void Close();

private:
	serial::Serial* mySerial;

	const int INPUT_LEN = 5;
	const int INPUT_SPACING = 1;

	static const int TOTAL_VECT_POTS = 3;
	InputData* pot[TOTAL_VECT_POTS];

	InputData* ERROR_POT;		// prevent errors (this will never be updated)

	InputData_single* pot_single;	// for for items we only have once ie whisk


	//TODO: sort this out according to above TODO's
	//?????
	int button1;
	int button2;
};