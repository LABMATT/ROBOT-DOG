
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
}


// #### Retruns the value for that pointer for part sefied. This canthen be used in programs (Leg, part, Motor or pot) #########################################
void legLegPointer()
{
  
}


//#### Loops thought all legs and updates there pid values.
void updateLEGS()
{

  // Loop though all leg parts
  for(int ppid = 0; ppid < 9; ppid++)
  {

      int pwm = 0;//legPWMArray[ppid];  
      int neg = 0;//legNegArray[ppid];
      int setpoint = 0;
      int output = 0;
      int input = 0;

      switch(ppid)
      {
        case 1: // L1A
        L1AInput = potRead(1, 'A');
        L1Asetpoint = c_buffer[66];
        //L1A.SetTunings(kp[ppid], ki[ppid], kd[ppid]);
        L1A.Compute();
        c_buffer[78] = L1AOutput;

        input = L1AInput;
        output = L1AOutput;
        setpoint = L1Asetpoint;
        pwm = L1Apwm;
        neg = L1An;
        break;

        case 2: //L1B
        L1BInput = potRead(1, 'B');
        L1Bsetpoint = c_buffer[67];
        //L1B.SetTunings(kp[ppid], ki[ppid], kd[ppid]);
        L1B.Compute();
        
        c_buffer[79] = L1BOutput;

        input = L1BInput;
        output = L1BOutput * -1;
        setpoint = L1Bsetpoint;
        pwm = L1Bpwm;
        neg = L1Bn;
        break;

        case 3: //L2A
        L2AInput = potRead(2, 'A');
        L2Asetpoint = c_buffer[69];
        //L2A.SetTunings(kp[ppid], ki[ppid], kd[ppid]);
        L2A.Compute();
        c_buffer[80] = L2AOutput;

        input = L2AInput;
        output = L2AOutput * -1;
        setpoint = L2Asetpoint;
        pwm = L2Apwm;
        neg = L2An;
        break;

        case 4: //L2B
        L2BInput = potRead(2, 'B');
        L2Bsetpoint = c_buffer[70];
        //L2B.SetTunings(kp[ppid], ki[ppid], kd[ppid]);
        L2B.Compute();
        c_buffer[81] = L2BOutput;
        
        input = L2BInput;
        output = L2BOutput;
        setpoint = L2Bsetpoint;
        pwm = L2Bpwm;
        neg = L2Bn;
        break;

        case 5: //L3A
        L3AInput = potRead(3, 'A');
        L3Asetpoint = c_buffer[72];
        //L3A.SetTunings(kp[ppid], ki[ppid], kd[ppid]);
        L3A.Compute();
        c_buffer[82] = L3AOutput;

        input = L3AInput;
        output = L3AOutput;
        setpoint = L3Asetpoint;
        pwm = L3Apwm;
        neg = L3An;
        break;

        case 6: //L3B
        L3BInput = potRead(3, 'B');
        L3Bsetpoint = c_buffer[73];
        //L3B.SetTunings(kp[ppid], ki[ppid], kd[ppid]);
        L3B.Compute();
        c_buffer[83] = L3BOutput;

        input = L3BInput;
        output = L3BOutput;
        setpoint = L3Bsetpoint;
        pwm = L3Bpwm;
        neg = L3Bn;
        break;

        case 7: //L4A
        L4AInput = potRead(4, 'A');
        L4Asetpoint = c_buffer[75];
        //L4A.SetTunings(kp[ppid], ki[ppid], kd[ppid]);
        L4A.Compute();
        c_buffer[84] = L4AOutput;

        input = L4AInput;
        output = L4AOutput * -1;
        setpoint = L4Asetpoint;
        pwm = L4Apwm;
        neg = L4An;
        break;

        case 8: //L4B
        L4BInput = potRead(4, 'B');
        L4Bsetpoint = c_buffer[76];
        //L4B.SetTunings(kp[ppid], ki[ppid], kd[ppid]);
        L4B.Compute();
        c_buffer[85] = L4BOutput;

        input = L4BInput;
        output = L4BOutput;
        setpoint = L4Bsetpoint;
        pwm = L4Bpwm;
        neg = L4Bn;
        break;
      }
/*
  Serial.print("_Input:");
  Serial.println(Input);
  
  Serial.print("_Output:");
  Serial.println(Output);

  Serial.print("_Setpoint:");
  Serial.println(Setpoint);
  */


if(input > setpoint + play || input < setpoint - play )
{
  
  if(output < 0)
  {
    
  analogWrite(pwm, (255 - (output * -1)));
  digitalWrite(neg, HIGH);
  } else if(output > 0)
  {

  analogWrite(pwm, output);
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
  }
}
