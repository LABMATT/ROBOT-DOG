#include <Servo.h>
#include <PID_v1.h>


//FOOT SENSOR BLOCK
#define L_1_sensor 35
#define L_2_sensor 34
#define L_3_sensor 33
#define L_4_sensor 32

// LEG-Axis-Postive/negative-pwm/nopwm

// #### INDICATORS #########################
#define powLED 22
#define emgLED 23
#define emgBut 19

boolean enleg = false;
boolean emsDIG = false;
int play = 10;

boolean picomenb = true;

//#### ALL LEG VALUES ######
// Double array of all the values for each elg pid.
//              1a 1b 2a 2b 3a 3b 4a 4b
//double kp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
//double ki[8] = {0, 0, 0, 0, 0, 0, 0, 0};
//double kd[8] = {0, 0, 0, 0, 0, 0, 0, 0};


//#### LEG 1 ##############################################
//double aL1AKp=0.2, aL1AKi=1, aL1AKd=1;
//double L1Setpoint, L1Input, L1Output;

//Le 1 A-axis Pot reading
int L_1Ap = 0;
int L_1Bp = 0;
int L_1Cp = 0;



#define L1enable 40

#define L1Apwm 6
#define L1An 31

#define L1Bpwm 7
#define L1Bn 30

#define L1Apot A1
#define L1Bpot A2
#define L1Cpot A3

Servo servo_Leg_1;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
 
//Specify the links and initial tuning parameters
//p first, how far from thing
// Kp = 1
// Ki = 0.1
// Kd = 0.25
double Kp=0.1, Ki=0, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// #### LEG 2 ##############################################
int L_2Ap = 0;
int L_2Bp = 0;
int L_2Cp = 0;

#define L2enable 41

#define L2Apwm 8
#define L2An 29

#define L2Bpwm 9
#define L2Bn 28


#define L2Apot A4
#define L2Bpot A5
#define L2Cpot A6

float L_2_Lenth;
Servo servo_Leg_2;

// #### LEG 3 ##############################################
int L_3Ap = 0;
int L_3Bp = 0;
int L_3Cp = 0;

#define L3enable 42
#define L3Apwm 10
#define L3An 27 

#define L3Bpwm 11
#define L3Bn 26


#define L3Apot A7
#define L3Bpot A8
#define L3Cpot A9 

float L_3_Lenth;
Servo servo_Leg_3;

// #### LEG 4 ##############################################
int L_4Ap = 500;
int L_4Bp = 500;
int L_4Cp = 500;

#define L4enable 43

#define L4Apwm 12
#define L4An 25

#define L4Bpwm 13
#define L4Bn 24


#define L4Apot A10
#define L4Bpot A11
#define L4Cpot A12

float L_4_Lenth = 3;
Servo servo_Leg_4;

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

void setup() {
ini();

piWD();
enableLegs(true);

updateAllPots();

  Setpoint = 550;
  Input =  potRead(1,'A');
 //turn the PID on
 myPID.SetMode(AUTOMATIC);
 myPID.SetOutputLimits(-255, 255);

}


void loop() {
 emgSTOP();

picom();
//cal();

pop();
//delay(100);

delay(100);
}


void testmotor()
{
 LEG1verification();
 LEG3verification();
 LEG2verification();
 LEG4verification();
}


void servoalign()
{
lcservos(1, 60);
lcservos(2, 60);
delay(1500);
lcservos(1, 90);
lcservos(2, 90);
delay(1500);
lcservos(1, 120);
lcservos(2, 120);
delay(1500);
lcservos(1, 90);
lcservos(2, 90);
delay(1500);
}


void pop()
{

  Input = potRead(1,'A');
  myPID.Compute();

if(Input > Setpoint + play || Input < Setpoint - play)
{
  if(Input > 0 && Input < 1023) {
  if(Output < 0)
  {
    
  analogWrite(L1Apwm, (255 - (Output * -1)));
  digitalWrite(L1An, HIGH);
  } else if(Output > 0)
  {

  analogWrite(L1Apwm, Output);
  digitalWrite(L1An, LOW); 
  }else
  {
  analogWrite(L1Apwm, 0);
  digitalWrite(L1An, LOW); 
  }
  }else
  {
  Output = 0;
  analogWrite(L1Apwm, 0);
  digitalWrite(L1An, LOW); 
  }
}else
  {
  analogWrite(L1Apwm, 0);
  digitalWrite(L1An, LOW); 
  }

piupdate("sL1A:", Setpoint);
piupdate("mL1A:", Output);
}
