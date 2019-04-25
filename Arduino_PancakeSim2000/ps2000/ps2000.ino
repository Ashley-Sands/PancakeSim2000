#include "MPU6050_tockn.h"
#include "ADXL345_Lib.h"
#include "Wire.h"

#define MUX_ADDR    0x70


// Debuging
bool DEBUG = false;            // forces print to console    // Also displays data normalized (if it been called)
const int DEBUG_INTERVALS = 200;   //millis
unsigned long DEBUG_LAST_INTERVAL = 0;

// Frying pan
MPU6050 MPU[3](Wire);  //TODO: needs to be array, futhermore tocknMPU will also need modifing to support mutiple devices

//Jug
//ADXL345 jug_adxl(Wire);

// Whisk
const int whisk_pin = A0;
const int whisking_switch_lowValue = 700;   // a value above this is considered high value
int whisking_lastWasLow = false;

const int whisking_valueChanged_interval = 250;             //ms
unsigned long whisking_nextInterval = 200;

bool whisking;

// Fire Alarm
const int fireAlarm_pin = 6;//A0;
unsigned long fireAlarm_length = 3350;

unsigned long fireAlarm_cookedPancake_length = 100;

unsigned long fireAlarm_endTime = 0;

// serial
int incomingByte = 0;
const int OUTPUT_BUFFER_SIZE = 5;

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
  
  sprintf(buff, "%.5u", num); //Convert num to chars

  // padd the buffer 
  for(int i = 0; i < OUTPUT_BUFFER_SIZE; i++)
    padded[i] = buff[i];

  padded[OUTPUT_BUFFER_SIZE] = '\0';
  if(neg) padded[0] = '-';  

  Serial.print( String(padded) ); // Output the padded value to serial console :)
  Serial.print("#");
}

void MUX_select(int8_t i2cBus)
{
  
  if (i2cBus > 7) return;
  Wire.beginTransmission(MUX_ADDR);
  Wire.write(1 << i2cBus);
  Wire.endTransmission(true);  
}

void setup() 
{
  //Setup Serial and Wire
  Wire.begin();
  Serial.begin(9600);
  
  //jug_adxl.begin();   //TODO this dont work if wire.begin is not called but if any MPU functions are called after Wire.begin is called serial does not work... hmmm..
  for(int i = 0; i < 3; i++)
  {
    MUX_select(i);
    MPU[i].begin();
  }
  
  pinMode(fireAlarm_pin, OUTPUT);
  digitalWrite(fireAlarm_pin, LOW);

  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  
  pinMode(A4, INPUT);
  
}

void loop()
{
  MUX_select(0);
  MPU[0].update();
  MUX_select(1);
  MPU[1].update();
  MUX_select(2);
  MPU[2].update();
  UpdateWhisking();
  //Check that Serial is available and read any incoming bytes
  if(Serial.available() > 0 || (DEBUG && millis() > (DEBUG_LAST_INTERVAL + DEBUG_INTERVALS)))
  {
    incomingByte = Serial.read();

    if(incomingByte == 'd' || incomingByte == 'D')  //DEBUG INPUT, D == true
    {
      DEBUG =  incomingByte == 'D';
    }
    else if(incomingByte == 'N' || incomingByte == 'n' )        // Normalize Device
    { 
      for(int i = 0; i < 3; i++)
        MPU[i].normalize();
    }
    else if( DEBUG || incomingByte == 'I' || incomingByte == 'i' )
    {
      printGroupValues();
    }
    
    if(incomingByte == 'f')
    {
      fireAlarm_endTime = millis() + fireAlarm_length;
      digitalWrite(fireAlarm_pin, HIGH);//fireAlarm_vol);
    }
    else if(incomingByte == 'e')
    {
      fireAlarm_endTime = millis() + fireAlarm_cookedPancake_length;
      digitalWrite(fireAlarm_pin, HIGH);
    }

     if(DEBUG)
        Serial.print("\n");
        
    DEBUG_LAST_INTERVAL = millis();
    
  }
  
  if( fireAlarm_endTime > 0 && millis() > fireAlarm_endTime )
  {
    // Stop fire alarm
    //analogWrite(fireAlarm_pin, 0);
    digitalWrite(fireAlarm_pin, LOW);
    fireAlarm_endTime = 0;
  }
  analogWrite(9, 255);
}

void printGroupValues()
{
    // Print Group Data
    // Hob[n] panX#panY#onStove#hobNob#...
    MUX_select(0);
    PrintPaddedValue( (MPU[0].getAngleX( true )) );
    PrintPaddedValue( (MPU[0].getAngleY( true )) );
    PrintPaddedValue( analogRead(A3) );   //LDR (27k ristor)    //TODO: need to be in array
    PrintPaddedValue( analogRead(A0) );  // Hob Nob             //TODO: needs to be in an array.
    
    MUX_select(1);
    PrintPaddedValue( (MPU[1].getAngleX( true )) );
    PrintPaddedValue( (MPU[1].getAngleY( true )) );
    PrintPaddedValue( analogRead(A4) );   //LDR (27k ristor)    //TODO: need to be in array
    PrintPaddedValue( analogRead(A1) );  // Hob Nob             //TODO: needs to be in an array.
    
    MUX_select(2);
    PrintPaddedValue( (MPU[2].getAngleX( true )) );
    PrintPaddedValue( (MPU[2].getAngleY( true )) );
    PrintPaddedValue( analogRead(A5) );   //LDR (27k ristor)    //TODO: need to be in array
    PrintPaddedValue( analogRead(A2) );  // Hob Nob             //TODO: needs to be in an array.
    
    // Print sigleData
    // d ...#Whisking#
    PrintPaddedValue( whisking );        // whisk rt tilt switch (1k ristor)
}

void UpdateWhisking()
{

  int currentValue = analogRead(whisk_pin);
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
