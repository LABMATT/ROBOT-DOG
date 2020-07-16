//LABMATT PRD2 SYSTEMS 2020
//CORE SYSTESM FOR SENSORY AND CONTROLL
//ALL CODE IS FREE AND OPEN SOURCE FOR USE BY ANYONE!
//Resoruces from the following websties were used in the creation of this skech:
//Acclarotmer https://learn.sparkfun.com/tutorials/adxl345-hookup-guide/all

#include <SparkFun_ADXL345.h>         // SparkFun ADXL345 Library
#include <Wire.h>
#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11


//Settings for system.
String lastupdate = "17 Feb 2020";
boolean debug = true;

float pitch, roll;



ADXL345 adxl = ADXL345();// USE FOR I2C COMMUNICATION
SoftwareSerial digSerial =  SoftwareSerial(rxPin, txPin);



void setup() {

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT); 
  digSerial.begin(9600);

  Serial.begin(9600);                 // Start the serial com.
  

  //Print basic info.
  Serial.println("LABMATT. Systems Starting");
  Serial.print("last updated: ");
  Serial.println(lastupdate);
  Serial.println();
  
  
  intialAcc(); //Sets up accelromter.

  Wire.begin(); // join i2c bus (address optional for master)


}

void loop() {
  // put your main code here, to run repeatedly:

 updateAxis();
 comSend("hello", 44);
 digSerial.println("HELLO");
}



void updateAxis()
{
  int x,y,z; //Variable for axis.
  
  adxl.readAccel(&x, &y, &z);         // Read the accelerometer values and store them in variables declared above x,y,z
  
  roll = atan(y / sqrt(pow(x, 2) + pow(z, 2))) * 180 / PI;
  pitch = atan(-1 * x / sqrt(pow(y, 2) + pow(z, 2))) * 180 / PI;

}



//Intitalse the accelaromter. Most of these are the basic settings that came from example skech.
void intialAcc()
{
  adxl.powerOn();                     //Power on the ADXL345

  adxl.setRangeSetting(16);           //Range settings
                                      
  adxl.setSpiBit(0);                  //SPI data
   
  adxl.setActivityXYZ(1, 0, 0);       // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setActivityThreshold(75);      // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)
 
  adxl.setInactivityXYZ(1, 0, 0);     // Set to detect inactivity in all the axes "adxl.setInactivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setInactivityThreshold(75);    // 62.5mg per increment   // Set inactivity // Inactivity thresholds (0-255)
  adxl.setTimeInactivity(10);         // How many seconds of no activity is inactive?

  debugger("Dones setting up accalromter.");
}


void debugger(String message)
{
  
  if(debug == true)
  {
    
  Serial.println(message);  
  }
 
}

void comRec()
{
  char message[15];

}


void comSend(char var[15], int val)
{
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(var);        // sends five bytes
  Wire.write(val);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
}
