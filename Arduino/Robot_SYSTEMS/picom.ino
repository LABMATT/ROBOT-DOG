
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
    }
  }

  Serial.print("code: ");
  Serial.println(code);
}
