
// Enableds legs for movment. 2 motors and servos. Updates gloable variable if changed.
void enableLegs(boolean en)
{

enleg = (en != enleg) ? en : enleg;
  
  if(enleg == true)
  {
    Serial.println("_Legs Enabled");
    
servo_Leg_1.attach(36);
servo_Leg_2.attach(37);
servo_Leg_3.attach(38);
servo_Leg_4.attach(39);
digitalWrite(L1enable, HIGH);
digitalWrite(L2enable, HIGH);
digitalWrite(L3enable, HIGH);
digitalWrite(L4enable, HIGH);
  } else
  {
    
        Serial.println("_Legs Disabled");
servo_Leg_1.detach();
servo_Leg_2.detach();
servo_Leg_3.detach();
servo_Leg_4.detach();
digitalWrite(L1enable, LOW);
digitalWrite(L2enable, LOW);
digitalWrite(L3enable, LOW);
digitalWrite(L4enable, LOW);
}
}


// If an interupt is triggerd then disable all pins NOW!
void emgSTOPint()
{
  enableLegs(false); 
}

// If emgacny stop button is pressed then activate this funtion apon reaching it in loop.
void emgSTOP()
{
  
  if(digitalRead(emgBut) == LOW || emsDIG == true)
  {
Serial.println("EMG_STOP");

enableLegs(false);

while(digitalRead(emgBut) == LOW || emsDIG == true)
{
  digitalWrite(emgLED, LOW);
  delay(650);
  digitalWrite(emgLED, HIGH);
  delay(100);
  picom();
  Serial.print("pot is: ");
  Serial.println(analogRead(L1Apot));
}
Serial.println("SYS_ONLINE");
enableLegs(true);
}
}


// Controll servo movment
void lcservos(int leg, int pos)
{
  
  switch(leg)
  {
    case 1:
 //  pos = (pos > l1constraint[2]) ? l1constraint[2] : pos;
 //   pos = (pos < l1constraint[0]) ? l1constraint[0] : pos;
    servo_Leg_1.write(pos);
    break;
    
    case 2:
 //  pos = (pos > l1constraint[2]) ? l1constraint[2] : pos;
 //   pos = (pos < l1constraint[0]) ? l1constraint[0] : pos;
    servo_Leg_2.write(pos);
    break;
    
    case 3:
 //  pos = (pos > l1constraint[2]) ? l1constraint[2] : pos;
 //   pos = (pos < l1constraint[0]) ? l1constraint[0] : pos;
    servo_Leg_3.write(pos);
    break;
    
    case 4:
 //  pos = (pos > l1constraint[2]) ? l1constraint[2] : pos;
 //   pos = (pos < l1constraint[0]) ? l1constraint[0] : pos;
    servo_Leg_4.write(pos);
    break;
  }
}


void cal()
{
  Serial.println("Make sure all servo mounts are disconnected and motors are clear.");
  lcservos(1, 90);
  lcservos(2, 90);
  lcservos(3, 90);  
  lcservos(4, 90);
}


void vectorLeg(int leg, int part)
{
analogWrite(L1Apwm, 70);
digitalWrite(L1An, LOW);

analogWrite(L2Apwm, 70);
digitalWrite(L2An, LOW);


analogWrite(L3Apwm, 70);
digitalWrite(L3An, LOW);


analogWrite(L4Apwm, 70);
digitalWrite(L4An, LOW);

delay(500);

analogWrite(L1Apwm, 255 - 70);
digitalWrite(L1An, HIGH);

analogWrite(L2Apwm, 255 - 70);
digitalWrite(L2An, HIGH);


analogWrite(L3Apwm, 255 -70);
digitalWrite(L3An, HIGH);


analogWrite(L4Apwm, 255 -70);
digitalWrite(L4An, HIGH);

delay(500); 
}



//Returns the port value of the leg. 
int potVale(int leg, char axis)
{

int avrage[5];
int pot;
int *potPointer;
  
  for(int i = 0; i < 5; i++)
  {
    switch(leg) 
    {
      case 1: 
      switch(axis)
      {
        case 'A':
        avrage[i] = analogRead(L1Apot);
        Serial.print("currentAv: ");
        Serial.println(avrage[i]);
        potPointer = &L1Apot;

        case 'B':
        pot = L1Bpot;

        case 'C':
        pot = L1Cpot;
        
      }
    }
  }

int fav = ((avrage[0] + avrage[1] + avrage[2] + avrage[3] + avrage[4]) / 5);
potPointer = fav;

Serial.print("fav: ");
Serial.println(fav);

Serial.println("done");
 
 return fav;
}
