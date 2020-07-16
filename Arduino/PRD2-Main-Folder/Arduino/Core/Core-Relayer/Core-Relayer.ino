//LABMATT PRD2 SYSTEMS 2020
//CORE SYSTESM FOR COM WITH PC AND CONTROLL.
//ALL CODE IS FREE AND OPEN SOURCE FOR USE BY ANYONE!
//Resoruces from the following websties were used in the creation of this skech:

#include <Wire.h>

String lastupdate = "17 Feb 2020";

int recVAL;
char recVAR;



void setup() {
  Serial.begin(9600);                 // Start the serial com.

  //Print basic info.
  Serial.println("LABMATT. Systems Starting");
  Serial.print("last updated: ");
  Serial.println(lastupdate);
  Serial.println();

  Wire.begin(4, D1, D2); //SDA SCL

  Wire.onReceive(comRec); // register event

}

void loop() {

comSend("It worked!", 5);

  delay(500);
}


void comRec(int howMany)
{
  Serial.println("trigged rec");
  
 while(1 < Wire.available()) // loop through all but the last
  {
    
    recVAL = Wire.read(); // receive byte as a character
    Serial.println(recVAL);
  }
  
  int recVAR = Wire.read();    // receive byte as an integer
  Serial.println(recVAR);
}


void comSend(char message[], int lenth)
{

}
