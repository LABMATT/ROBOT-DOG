//https://howtomechatronics.com/tutorials/arduino/how-i2c-communication-works-and-how-to-use-it-with-arduino/

#include <Wire.h>

byte buff[16];

void setup() {
  
Serial.begin(9600);

//Wire.begin(D2, D1); //Start wire on these pins.

Serial.println("Online!");

Wire.beginTransmission(0x53); //Select device
Wire.write(0x2D);             //Select Power Register.
Wire.write(8);                //Change the D3 to on to mesure mode
Wire.endTransmission();       // stop transmitting

}

void loop() {

  Wire.beginTransmission(0x53); //Select device.
  Wire.write(0x32); //Ask data from register 0x32
  Wire.endTransmission(false); //This ends the previos transmission however then starts another so that another device dosent start comunication.
  
  Wire.requestFrom(0x53, 6, true);    //Asked device 0x53 (accleronmeter) for 8 bytes of data. int = 4 bytes. 4 ints = 16 bytes of data. True at the ends terminatls the i2c comuncation.
/*
  float x = (uint16_t) ((uint16_t) Wire.read()| (int) Wire.read() << 8); // X-axis value
  x = x/256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  
  float y = (uint16_t)( (uint16_t)Wire.read()| (int)Wire.read() << 4); // Y-axis value
  y = y/256;
  
  float z = (uint16_t)( (uint16_t)Wire.read()| (int)Wire.read() << 8); // Z-axis value
  z = z/256;
  */

int x,y,z;
    int16_t i16;  // the 16-bit result, signed.

  i16 = (int16_t) ((((uint16_t)Wire.read()) << 8) | Wire.read());
  x = (int) i16;

  i16 = (int16_t) ((((uint16_t)Wire.read()) << 8) | Wire.read());
  y = (int) i16;

  i16 = (int16_t) ((((uint16_t)Wire.read()) << 8) | Wire.read());
  z = (int) i16;
  
Serial.println(x);
Serial.println(y);
Serial.println(z);     
Serial.println(" ");
delay(500);

  
  //delay(1000);
  }
