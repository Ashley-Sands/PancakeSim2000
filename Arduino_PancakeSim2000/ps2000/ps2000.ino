#include "MPU6050_tockn.h"
#include "ADXL345_Lib.h"
#include "Wire.h"

// Debuging
bool DEBUG = false;            // forces print to console    // Also displays data normalized (if it been called)
const int DEBUG_INTERVALS = 200;   //millis
unsigned long DEBUG_LAST_INTERVAL = 0;

// Frying pan
MPU6050 MPU(Wire);  //TODO: needs to be array, futhermore tocknMPU will also need modifing to support mutiple devices

//Jug
//ADXL345 jug_adxl(Wire);

// Whisk
const int whisking_switch_lowValue = 750;   // a value above this is considered high value
int whisking_lastWasLow = false;

const int whisking_valueChanged_interval = 250;             //ms
unsigned long whisking_nextInterval = 500;

bool whisking;

// Fire Alarm
const int fireAlarm_pin = A0;
unsigned long fireAlarm_length = 3350;
unsigned long fireAlarm_startTime = 0;

// serial
int incomingByte = 0;
const int OUTPUT_BUFFER_SIZE = 7;

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
  //Wire.begin();
  Serial.begin(9600);
  
  //jug_adxl.begin();   //TODO this dont work if wire.begin is not called but if any MPU functions are called after Wire.begin is called serial does not work... hmmm..
  MPU.begin();
  //MPU.calcGyroOffsets(false, 0, 0); //we will do this internaly
  
  pinMode(fireAlarm_pin, OUTPUT);
  
}

void loop()
{

  MPU.update(); //must be continuously updated :| (DO NOT USE DELAY, unless you want garbage values)
  //jug_adxl.update();
  
  UpdateWhisking();
  
  //Check that Serial is available and read any incoming bytes
  if(Serial.available() > 0 || (DEBUG && millis() > (DEBUG_LAST_INTERVAL + DEBUG_INTERVALS)))
  {
    incomingByte = Serial.read();

    if(incomingByte == 'd' || incomingByte == 'D')  //DEBUG INPUT, D == true
    {
      DEBUG =  incomingByte == 'D';
    }
    else if(incomingByte == 'N' )        // Normalize Device
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
      Serial.print("#");
      PrintPaddedValue( analogRead(A2) );  // Hob Nob
        
      Serial.print("#");
      PrintPaddedValue( whisking );        // whisk rt tilt switch (1k ristor)
      
      if(DEBUG)
        Serial.print("\n");
    }
    else if(incomingByte == 'f')
    {
      fireAlarm_startTime = millis();
      analogWrite(fireAlarm_pin, 1024);
    }

    DEBUG_LAST_INTERVAL = millis();
    
  }

  if( fireAlarm_startTime > 0 && millis() > (fireAlarm_startTime + fireAlarm_length) )
  {
    // Stop fire alarm
    analogWrite(fireAlarm_pin, 0);
  }
  
/*
   Serial.print( analogRead(A4) );
   Serial.print("\n");
   Serial.print( whisking );
   Serial.print("\n");
*/
}

void UpdateWhisking()
{

  int currentValue = analogRead(A4);
  bool valueIsLow = currentValue < whisking_switch_lowValue;
  
  if(valueIsLow != whisking_lastWasLow)
  {
    whisking = true;
    whisking_nextInterval = millis() + whisking_valueChanged_interval;
  }
  else if(millis() >= whisking_nextInterval)
  {
    whisking = false;
    whisking_nextInterval = millis() + whisking_valueChanged_interval; 
  }

  whisking_lastWasLow = valueIsLow;
  
}
