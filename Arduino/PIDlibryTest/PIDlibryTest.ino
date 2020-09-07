/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>

#define PIN_INPUT A1
#define PIN_OUTPUT 6
#define neg 31

int play = 15;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=0.7, Ki=0, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  pinMode(neg, OUTPUT);
  pinMode(40, OUTPUT);
  //initialize the variables we're linked to
  Input = analogRead(PIN_INPUT);
  Setpoint = 600;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-255, 255);
  digitalWrite(neg, LOW);
  digitalWrite(40, HIGH);

  Serial.begin(2000000);
}

void loop()
{

  if(Serial.available() > 0)
  {
    int sr = Serial.parseInt();
    if(sr != 0)
    {
      Setpoint = sr;
    }
  }

  Input = analogRead(PIN_INPUT);
  myPID.Compute();

if(Input > Setpoint + play || Input < Setpoint - play )
{
  Serial.println(Output);
  if(Output < 0)
  {
    
  analogWrite(PIN_OUTPUT, (255 - (Output * -1)));
  digitalWrite(neg, HIGH);
  } else if(Output > 0)
  {

  analogWrite(PIN_OUTPUT, Output);
  digitalWrite(neg, LOW); 
  }else
  {
  analogWrite(PIN_OUTPUT, 0);
  digitalWrite(neg, LOW); 
  }
}else
  {
  analogWrite(PIN_OUTPUT, 0);
  digitalWrite(neg, LOW); 
  }
}
