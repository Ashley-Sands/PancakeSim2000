
#include "Wire.h"

const int MPU_ADDR_0 = 0x68; //AD0 Set to low //TODO: make array

int16_t acc_x, acc_y, acc_z;

int16_t s_gyro_x, s_gyro_y, s_gyro_z;
int16_t gyro_x, gyro_y, gyro_z;

int16_t temp;

int incomingByte = 0;

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

  MPU( &s_gyro_x, &s_gyro_y, &s_gyro_z ); //Get the start values to normalized the device.
  
}

void loop(){

  MPU( &gyro_x, &gyro_y, &gyro_z );   // get the values from the device.

  //Check that Serial is available and read any incoming bytes
  if(Serial.available() > 0)
  {
    incomingByte = Serial.read();

    if( incomingByte == 'N' )        // Normalize Device 
      MPU( &s_gyro_x, &s_gyro_y, &s_gyro_z );
    else if( incomingByte == 'I' )   // Print values (Normalized)
      Serial.print( convert_int16_to_str(gyro_x - s_gyro_x));
    else if( incomingByte == 'i' )   // Print values (RAW)
      Serial.print( convert_int16_to_str(gyro_x));
  }
  //print value to console nomalized.
  

  delay(1000);
}

void MPU(int16_t* Gx, int16_t* Gy, int16_t* Gz) {

  //Get values from the MPU device.
  Wire.beginTransmission(MPU_ADDR_0);
  Wire.write(0x3B);                   //Start with register 0X3B (accel X Out)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR_0, 7*2, true);

  // Get values from MPU
  /*gyro_x*/ *Gx = Wire.read()<<8  | Wire.read(); // 0X3B
  /*gyro_y*/ *Gy = Wire.read()<<8  | Wire.read(); // 0X3D
  /*gyro_z*/ *Gz = Wire.read()<<8  | Wire.read(); // 0X3F

  temp = Wire.read()<<8   | Wire.read(); // 0X41

  acc_x = Wire.read()<<8 | Wire.read(); // 0X43
  acc_y = Wire.read()<<8 | Wire.read(); // 0X45
  acc_z = Wire.read()<<8 | Wire.read(); // 0X47

  //Serial.print( convert_int16_to_str(gyro_x));

  // print some shiz to console :)
  //Serial.print(" Ax: ");   Serial.print( convert_int16_to_str(temp));//gyro_x) );
  //Serial.print(" | Ay: "); Serial.print( convert_int16_to_str(gyro_y) );
  //Serial.print(" | Az: "); Serial.print( convert_int16_to_str(gyro_z) );
  //Serial.print("\n");

}
