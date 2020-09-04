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

  Serial.begin(9600);
}

void loop()
{

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

/*
   int pot = analogRead(PIN_INPUT);

  if(pot < 500 - play)
{
  
 Input = pot;
 myPID.Compute();
 analogWrite(PIN_OUTPUT, Output);
 digitalWrite(neg, LOW);
} else if(pot > 500 + play)
{
  
 Input = 1023 - pot;
 myPID.Compute();
 analogWrite(PIN_OUTPUT, 255 - Output);
 digitalWrite(neg, HIGH);
} else
{
 analogWrite(PIN_OUTPUT, 0);
 digitalWrite(neg, LOW);
}
 */
