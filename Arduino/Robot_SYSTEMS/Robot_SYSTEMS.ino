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

// #### LEG 1 ##############################################
float L_1_Lenth;

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
double Kp=0.2, Ki=1, Kd=1;
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
pinMode(powLED, OUTPUT);
pinMode(emgLED, OUTPUT);
pinMode(emgBut, INPUT_PULLUP);

attachInterrupt(digitalPinToInterrupt(emgBut), emgSTOPint, FALLING);

digitalWrite(powLED, HIGH);
digitalWrite(emgLED, HIGH);
delay(2000);
digitalWrite(powLED, LOW);

pinMode(L1enable, OUTPUT);
pinMode(L1Apwm, OUTPUT);
pinMode(L1Bn , OUTPUT);
pinMode(L1Bpwm, OUTPUT);
pinMode(L1Bn, OUTPUT);
pinMode(L1Apot, INPUT);
pinMode(L1Bpot, INPUT);
pinMode(L1Cpot, INPUT);

pinMode(L2enable, OUTPUT);
pinMode(L2Apwm, OUTPUT);
pinMode(L2Bn, OUTPUT);
pinMode(L2Bpwm, OUTPUT);
pinMode(L2Bn, OUTPUT);
pinMode(L2Apot, INPUT);
pinMode(L2Bpot, INPUT);
pinMode(L2Cpot, INPUT);

pinMode(L3enable, OUTPUT);
pinMode(L3Apwm, OUTPUT);
pinMode(L3Bn, OUTPUT);
pinMode(L3Bpwm, OUTPUT);
pinMode(L3Bn, OUTPUT);
pinMode(L3Apot, INPUT);
pinMode(L3Bpot, INPUT);
pinMode(L3Cpot, INPUT);

pinMode(L4enable, OUTPUT);
pinMode(L4Apwm, OUTPUT);
pinMode(L4Bn , OUTPUT);
pinMode(L4Bpwm, OUTPUT);
pinMode(L4Bn, OUTPUT);
pinMode(L4Apot, INPUT);
pinMode(L4Bpot, INPUT);
pinMode(L4Cpot, INPUT);

Serial.begin(9600);

piWD();
enableLegs(true);

updateAllPots();

 Setpoint = 500;
 
 //turn the PID on
 myPID.SetMode(AUTOMATIC);
}


void loop() {
 emgSTOP();
 //Serial.println("mainlop");

picom();
//cal();

//pop();
//delay(100);

potRead(1, 'A');
potRead(1, 'B');
potRead(1, 'C');

potRead(2, 'A');
potRead(2, 'B');
potRead(2, 'C');

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

int pot;

void pop()
{
pot = analogRead(L1Apot);


if(pot < 500 - play)
{
 Input = pot;
 if(myPID.Compute() == true)
 {
 Serial.println("1");
 Serial.println(pot);
 Serial.println(Output);
 analogWrite(L1Apwm, Output);
 digitalWrite(L1An, LOW);
 }
} else if(pot > 500 + play)
{
 Input = 1023 - pot;
 if(myPID.Compute() == true)
 {
 Serial.println("2");
 Serial.println(pot);
 Serial.println(Output);
 analogWrite(L1Apwm, 255 - Output);
 digitalWrite(L1An, HIGH);
 }
} else
{
 analogWrite(L1Apwm, 0);
 digitalWrite(L1An, LOW);
}
}
