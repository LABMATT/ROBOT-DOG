
// Enableds legs for movment. 2 motors and servos. Updates gloable variable if changed.
void enableLegs(boolean en)
{
  
enleg = (en != enleg) ? en : enleg;

legEnable(1, enleg);
legEnable(2, enleg);
legEnable(3, enleg);
legEnable(4, enleg);
}

// Set a leg to true or false
void legEnable(int leg, boolean state)
{
  if(state == true)
  {
  switch(leg)
  {
    case 1:
    servo_Leg_1.attach(36);
    digitalWrite(L1enable, HIGH);
    c_buffer[42] = 1;
    c_buffer[43] = 1;
    c_buffer[44] = 1;
    break;
    
    case 2:
    servo_Leg_2.attach(37);
    digitalWrite(L2enable, HIGH);
    c_buffer[45] = 1;
    c_buffer[46] = 1;
    c_buffer[47] = 1;
    break;

    case 3:
    servo_Leg_3.attach(38);
    digitalWrite(L3enable, HIGH);
    c_buffer[48] = 1;
    c_buffer[49] = 1;
    c_buffer[50] = 1;
    break;

    case 4:
    servo_Leg_4.attach(39);
    digitalWrite(L4enable, HIGH);
    c_buffer[51] = 1;
    c_buffer[52] = 1;
    c_buffer[53] = 1;
    break;
  }
  } else
  {
  switch(leg)
  {
    case 1:
    servo_Leg_1.detach();
    digitalWrite(L1enable, LOW);
    c_buffer[42] = 0;
    c_buffer[43] = 0;
    c_buffer[44] = 0;
    break;
    
    case 2:
    servo_Leg_2.detach();
    digitalWrite(L2enable, LOW);
    c_buffer[45] = 0;
    c_buffer[46] = 0;
    c_buffer[47] = 0;
    break;

    case 3:
    servo_Leg_3.detach();
    digitalWrite(L3enable, LOW);
    c_buffer[48] = 0;
    c_buffer[49] = 0;
    c_buffer[50] = 0;
    break;

    case 4:
    servo_Leg_4.detach();
    digitalWrite(L4enable, LOW);
    c_buffer[51] = 0;
    c_buffer[52] = 0;
    c_buffer[53] = 0;
    break;
  }
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
  updateAllPots();

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
      myPointer = &c_buffer[54]; //&L_1Ap;
      comName = "pL1A";
      break;

      case 'B':
      pot = L1Bpot;
      myPointer = &c_buffer[55]; //&L_1Bp;
      comName = "pL1B";
      break;

      case 'C':
      pot = L1Cpot;
      myPointer = &c_buffer[56]; //&L_1Cp;
      comName = "pL1C";
      break;
    }
    break;

    case 2:
    switch(part)
    {
      case 'A':
      pot = L2Apot;
      myPointer = &c_buffer[57]; //&L_2Ap;
      comName = "pL2A";
      break;

      case 'B':
      pot = L2Bpot;
      myPointer = &c_buffer[58]; //&L_2Bp;
      comName = "pL2B";
      break;

      case 'C':
      pot = L2Cpot;
      myPointer = &c_buffer[59]; //&L_2Cp;
      comName = "pL2C";
      break;
    }
    break;

    case 3:
    switch(part)
    {
      case 'A':
      pot = L3Apot;
      myPointer = &c_buffer[60]; //&L_3Ap;
      comName = "pL3A";
      break;

      case 'B':
      pot = L3Bpot;
      myPointer = &c_buffer[61]; //&L_3Bp;
      comName = "pL3B";
      break;

      case 'C':
      pot = L3Cpot;
      myPointer = &c_buffer[62]; //&L_3Cp;
      comName = "pL3C";
      break;
    }
    break;

    case 4:
    switch(part)
    {
      case 'A':
      pot = L4Apot;
      myPointer = &c_buffer[63]; //&L_4Ap;
      comName = "pL4A";
      break;

      case 'B':
      pot = L4Bpot;
      myPointer = &c_buffer[64]; //&L_4Bp;
      comName = "pL4B";
      break;

      case 'C':
      pot = L4Cpot;
      myPointer = &c_buffer[65]; //&L_4Cp;
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
   //piupdate(comName + ":", reader);
  
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


//#### Loops thought all legs and updates there pid values.
void updateLEGS()
{
  for(int ppid = 0; ppid < 8; ppid++)
  {
      Input = potRead(legnum[ppid], legchar[ppid]);

      int pwm = legPWMArray[ppid];  
      int neg = legNegArray[ppid];

      Setpoint = c_buffer[65 + ppid];

      myPID.SetTunings(kp[ppid], ki[ppid], kd[ppid]);

      switch(ppid)
      {
        case 1:
        L1A.Compute();
      }
  

if(Input > Setpoint + play || Input < Setpoint - play )
{
  myPID.Compute();
  
  Serial.println(Output);
  if(Output < 0)
  {
    
  analogWrite(pwm, (255 - (Output * -1)));
  digitalWrite(neg, HIGH);
  } else if(Output > 0)
  {

  analogWrite(pwm, Output);
  digitalWrite(neg, LOW); 
  }else
  {
  analogWrite(pwm, 0);
  digitalWrite(neg, LOW); 
  }
}else
  {
  analogWrite(pwm, 0);
  digitalWrite(neg, LOW); 
  }

c_buffer[77 + ppid] = Output;
  }
}
