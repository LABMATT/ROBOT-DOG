void enableLegs(boolean en)
{

enleg = (en != enleg) ? en : enleg;
  
  if(enleg == true)
  {
    
servo_Leg_1.attach(36);
servo_Leg_2.attach(36);
servo_Leg_3.attach(38);
servo_Leg_4.attach(39);
digitalWrite(L1enable, HIGH);
digitalWrite(L2enable, HIGH);
digitalWrite(L3enable, HIGH);
digitalWrite(L4enable, HIGH);
  } else
  {
    
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



void emgSTOP()
{
  if(digitalRead(emgBut) == LOW)
  {
Serial.println("EMG_STOP");

//DISABLE ALL PINS
enableLegs(false);


while(digitalRead(emgBut) == LOW)
{
  digitalWrite(emgLED, LOW);
  delay(650);
  digitalWrite(emgLED, HIGH);
  delay(100);
}
Serial.println("SYS_ONLINE");
}

enableLegs(true);
}
