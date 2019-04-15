
#include "Wire.h"

const int MPU_ADDR_0 = 0x68; //AD0 Set to low //TODO: make array

int16_t acc_x, acc_y, acc_z;
int16_t gyro_x, gyro_y, gyro_z;
int16_t temp;


char out_str[8];

//convert int16_t to string
char* convert_int16_to_str(int16_t val) 
{
  sprintf(out_str, "%6d", val);
  return out_str;
}


void setup() 
{
  //Setup Serial and Wire
  Serial.begin(9600);
  Wire.begin();
  // setup the MPU device 
  Wire.beginTransmission(MPU_ADDR_0);   // Begin transmission between the I2C salve (GY-521)
  Wire.write(0x6B);
  Wire.write(0);                        //Set to zero (wake up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {

  //Get values from the MPU device.
  Wire.beginTransmission(MPU_ADDR_0);
  Wire.write(0x3B);                   //Start with register 0X3B (accel X Out)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR_0, 7*2, true);

  // Get values from MPU
  gyro_x = Wire.read()<<8  | Wire.read(); // 0X3B
  gyro_y = Wire.read()<<8  | Wire.read(); // 0X3D
  ayro_z = Wire.read()<<8  | Wire.read(); // 0X3F

  temp = Wire.read()<<8   | Wire.read(); // 0X41

  acc_x = Wire.read()<<8 | Wire.read(); // 0X43
  acc_y = Wire.read()<<8 | Wire.read(); // 0X45
  acc_z = Wire.read()<<8 | Wire.read(); // 0X47

  // print some shiz to console :)
  Serial.print(" Ax: ");   Serial.print( convert_int16_to_str(temp));//gyro_x) );
  Serial.print(" | Ay: "); Serial.print( convert_int16_to_str(gyro_y) );
  Serial.print(" | Az: "); Serial.print( convert_int16_to_str(gyro_z) );
  Serial.print("\n");
  delay(1000);
}
