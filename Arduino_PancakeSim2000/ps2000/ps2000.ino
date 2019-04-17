#include "MPU6050_tockn.h"
#include "Wire.h"

const bool DEBUG = false;            // forces print to console    // Also displays data normalized (if it been called)
const int DEBUG_INTERVALS = 1000;   //millis
unsigned int DEBUG_LAST_INTERVAL = 0;

int incomingByte = 0;

const int OUTPUT_BUFFER_SIZE = 7;

MPU6050 MPU(Wire);  //TODO: needs to be array, futhermore tocknMPU will also need modifing to support mutiple devices

void PrintPaddedValue(int num)
{
  //define buffer and the final padded values
  char buff[ OUTPUT_BUFFER_SIZE ];
  char padded[ OUTPUT_BUFFER_SIZE + 1 ];
  
  bool neg = false; //remember if num is negitive

  if(num < 0)       // make shore that the number is positive since we are converting unsigned int to char
  {
    num = -num;
    neg = true;
  }
  
  sprintf(buff, "%.7u", num); //Convert num to chars

  // padd the buffer 
  for(int i = 0; i < OUTPUT_BUFFER_SIZE; i++)
    padded[i] = buff[i];

  padded[7] = '\0';
  if(neg) padded[0] = '-';  

  Serial.print( String(padded) ); // Output the padded value to serial console :)
  
}


void setup() 
{
  //Setup Serial and Wire
  Serial.begin(9600);

  MPU.begin();
  //MPU.calcGyroOffsets(false, 0, 0); //we will do this internaly
  
}

void loop()
{

  MPU.update(); //must be continuously updated :| (DO NOT USE DELAY, unless you want garbage values)
  
  //Check that Serial is available and read any incoming bytes
  if(Serial.available() > 0 || (DEBUG && millis() > (DEBUG_LAST_INTERVAL + DEBUG_INTERVALS)))
  {
    incomingByte = Serial.read();

    if( incomingByte == 'N' )        // Normalize Device
    { 
      MPU.normalize();
    }
    else if( DEBUG || incomingByte == 'I' || incomingByte == 'i' )   
    { // if incomingByte is 'I' then get angle noralized
      int16_t x = floor( MPU.getAngleX( incomingByte == 'I' || DEBUG ) );
      int16_t y = floor( MPU.getAngleY( incomingByte == 'I' || DEBUG ) );

      // write to console
      PrintPaddedValue( x );                // Gyro X
      Serial.print("#");
      PrintPaddedValue( y );                // Gyro Y
      Serial.print("#");
      PrintPaddedValue( analogRead(A3) );   //LDR (27k ristor)
      
      if(DEBUG)
        Serial.print("\n");
    }

    DEBUG_LAST_INTERVAL = millis();
    
  }

}
