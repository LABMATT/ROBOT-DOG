
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
piupdate("eL1A:", true);
piupdate("eL1B:", true);
piupdate("eL1C:", true);

piupdate("eL2A:", true);
piupdate("eL2B:", true);
piupdate("eL2C:", true);

piupdate("eL3A:", true);
piupdate("eL3B:", true);
piupdate("eL3C:", true);

piupdate("eL4A:", true);
piupdate("eL4B:", true);
piupdate("eL4C:", true);

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


piupdate("eL1A:", false);
piupdate("eL1B:", false);
piupdate("eL1C:", false);

piupdate("eL2A:", false);
piupdate("eL2B:", false);
piupdate("eL2C:", false);

piupdate("eL3A:", false);
piupdate("eL3B:", false);
piupdate("eL3C:", false);

piupdate("eL4A:", false);
piupdate("eL4B:", false);
piupdate("eL4C:", false);



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
Serial.println("_EMG_STOP");

enableLegs(false);

while(digitalRead(emgBut) == LOW || emsDIG == true)
{
  digitalWrite(emgLED, LOW);
  delay(650);
  digitalWrite(emgLED, HIGH);
  delay(100);
  picom();

}
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
  Serial.println("_Make sure all servo mounts are disconnected and motors are clear.");
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



//#### Reads and avrages the value of a pot on legs. ########################################
int potRead(int leg, char part)
{
  int pot = 0;
  int *myPointer;
  String comName = "";

  switch(leg)
  {
    case 1:
    switch(part)
    {
      case 'A':
      pot = L1Apot;
      myPointer = &L_1Ap;
      comName = "pL1A";
      break;

      case 'B':
      pot = L1Bpot;
      myPointer = &L_1Bp;
      comName = "pL1B";
      break;

      case 'C':
      pot = L1Cpot;
      myPointer = &L_1Cp;
      comName = "pL1C";
      break;
    }
    break;

    case 2:
    switch(part)
    {
      case 'A':
      pot = L2Apot;
      myPointer = &L_2Ap;
      comName = "pL2A";
      break;

      case 'B':
      pot = L2Bpot;
      myPointer = &L_2Bp;
      comName = "pL2B";
      break;

      case 'C':
      pot = L2Cpot;
      myPointer = &L_2Cp;
      comName = "pL2C";
      break;
    }
    break;

    case 3:
    switch(part)
    {
      case 'A':
      pot = L3Apot;
      myPointer = &L_3Ap;
      comName = "pL3A";
      break;

      case 'B':
      pot = L3Bpot;
      myPointer = &L_3Bp;
      comName = "pL3B";
      break;

      case 'C':
      pot = L3Cpot;
      myPointer = &L_3Cp;
      comName = "pL3C";
      break;
    }
    break;

    case 4:
    switch(part)
    {
      case 'A':
      pot = L4Apot;
      myPointer = &L_4Ap;
      comName = "pL4A";
      break;

      case 'B':
      pot = L4Bpot;
      myPointer = &L_4Bp;
      comName = "pL4B";
      break;

      case 'C':
      pot = L4Cpot;
      myPointer = &L_4Cp;
      comName = "pL4C";
      break;
    }
    break;
  }

int reader = 0;
  
  for(int i = 0; i < 10; i++)
  {
    reader = reader + analogRead(pot);
  }

reader = reader/10;

  *myPointer = reader;
   piupdate(comName + ":", reader);
  
  return reader;
}


//#### SET NEW POIT POINT ##########################################################################################################
void legSetPoint(int leg, char part)
{
  
}

//#### Update all the pot on startup ###############################################################################################
void updateAllPots()
{
  potRead(1,'A');
  potRead(1,'B');
  potRead(1,'C');

  potRead(2,'A');
  potRead(2,'B');
  potRead(2,'C');

  potRead(3,'A');
  potRead(3,'B');
  potRead(3,'C');

  potRead(4,'A');
  potRead(4,'B');
  potRead(4,'C');

  piupdate("mL1A:", Input);
}


// #### Retruns the value for that pointer for part sefied. This canthen be used in programs (Leg, part, Motor or pot) #########################################
void legLegPointer()
{
  
}
