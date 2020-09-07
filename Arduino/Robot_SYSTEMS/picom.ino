float pot_buffer[100];


//Pi watch dog. Wait for com.
void piWD()
{

  Serial.println("piwd");

boolean readystate = false;
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)
int ledState = LOW; 
  
  while(Serial.available() || readystate == false)
  {
    
 unsigned long currentMillis = millis();
 
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(powLED, ledState);
  }
String a = Serial.readString();
a.trim();

 readystate = (a == "pi_online") ? true : false;
 
 Serial.println(a);
 Serial.println(readystate);
 
   if(readystate == true)
 {
  Serial.println("braking loop");
  digitalWrite(powLED, HIGH);
  break;
 }
  }
}


// Wait for commands from pi
void picom() 
{

  int code = 0;
  if(Serial.available() > 0)
  {
    code = Serial.parseInt();

    switch(code)
    {
      case 101:
      emsDIG = true;
      emgSTOP();
      break;
      case 102:
      emsDIG = false;
      break;
      case 103:
      pidUpdate(103);
      break;
      case 104:
      pidUpdate(104);
      break;
      case 105:
      pidUpdate(105);
      break;
      case 106:
      pidUpdate(106);
      break;
    }
  }

  //Serial.print("code: ");
  //Serial.println(code);
}


// Send the values of the pots
void piupdate(String name, double val)
{
Serial.println(name + val);  
}

// pi rounds
void piRounds()
{
  //Serial.println("pL1A" + )

 // piupdate("aL1AKp:", aL1AKp);
 // piupdate("aL1AKi:", aL1AKi);
 // piupdate("aL1AKd:", aL1AKd);
}

void pidUpdate(int lcode)
{
        double p = 0, i = 0, d = 0, setcode = 0;
      boolean floof = true;
      Serial.println("_Floof time");
      enableLegs(false);

      switch(lcode)
      {
      case 103:
      while(floof == true)
      {
         double newint = Serial.parseFloat();
         if(newint < 0)
         {
          Kp = newint * -1;
          piupdate("aL1AKp:", Kp);
          floof = false;
         }
         if(newint == -2000)
         {
          Kp = 0;
          piupdate("aL1AKp:", Kp);
          floof = false;
         }
      }
      break;

      case 104:
      while(floof == true)
      {
         double newint = Serial.parseFloat();
         if(newint < 0)
         {
          Ki = newint * -1;
          piupdate("aL1AKi:", Ki);
          floof = false;
         }
         if(newint == -2000)
         {
          Ki = 0;
          piupdate("aL1AKi:", Ki);
          floof = false;
         }
      }
      break;

      case 105:
      while(floof == true)
      {
         double newint = Serial.parseFloat();
         if(newint < 0)
         {
          Kd = newint * -1;
          piupdate("aL1AKd:", Kd);
          floof = false;
         }
         if(newint == -2000)
         {
          Kd = 0;
          piupdate("aL1AKd:", Kd);
          floof = false;
         }
      }
     break;

      case 106:
      while(floof == true)
      {
         int newint = Serial.parseInt();
         if(newint < 0)
         {
          Setpoint = newint * -1;
          piupdate("sL1A:", Setpoint);
          floof = false;
         }
         if(newint == -2000)
         {
          Setpoint = 0;
          piupdate("sL1A:", Setpoint);
          floof = false;
         }
      }
     break;
      }
     myPID.SetTunings(Kp, Ki, Kd);
     enableLegs(true);
     Serial.println("_PID configured.");

       analogWrite(L1Apwm, 0);
  digitalWrite(L1An, LOW); 
}
