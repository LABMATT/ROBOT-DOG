#include <SoftwareSerial.h>

//uno rx 10 tx 11
//mcu rx D1 tx D2

#define rxPin D1
#define txPin D2

SoftwareSerial digSerial(rxPin, txPin); //Rx, Tx

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome");
  
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT); 
  digSerial.begin(9600);
 
}

void loop() {
  
digSerial.println("Hello from uno.");
Serial.println(digSerial.readString());
}
