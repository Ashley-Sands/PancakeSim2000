#include "Arduino.h"

#define ADXL345_ADDR	(0x53)
 
class TwoWire;

class ADXL345{

public:

	ADXL345(TwoWire &w);

	void begin();
	void update();
	
	int GetGyro_x(){ return gyro_x; }
	int GetGyro_y(){ return gyro_y; }
	int GetGyro_z(){ return gyro_z; }
	
	
private: 
	TwoWire* wire;
	 
	int gyro_x = 0;
	int gyro_y = 0;
	int gyro_z = 0;
	
	byte gyro_values[6];		// we read 6 bytes from the gyro
	
};
