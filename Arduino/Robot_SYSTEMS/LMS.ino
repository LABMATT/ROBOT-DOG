
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
  
  if(digitalRead(emgBut) == LOW)
  {
Serial.println("EMG_STOP");

enableLegs(false);

while(digitalRead(emgBut) == LOW)
{
  digitalWrite(emgLED, LOW);
  delay(650);
  digitalWrite(emgLED, HIGH);
  delay(100);
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
