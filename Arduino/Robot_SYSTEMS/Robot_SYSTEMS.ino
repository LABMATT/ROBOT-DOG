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
int play = 0;

boolean picomenb = true;

// POTS 1-100 
int c_buffer[100] = {};
int p_buffer[100] = {};


//#### LEG 1 ##############################################
//double aL1AKp=0.2, aL1AKi=1, aL1AKd=1;
//double L1Setpoint, L1Input, L1Output;

#define L1enable 40

#define L1Apwm 6
#define L1An 31

#define L1Bpwm 7
#define L1Bn 30

#define L1Apot A1
#define L1Bpot A2
#define L1Cpot A3

Servo servo_Leg_1;


 
//Specify the links and initial tuning parameters
//p first, how far from thing
// Kp = 1
// Ki = 0.1
// Kd = 0.25
//double Kp=0.1, Ki=0, Kd=0;


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


//#### ALL LEG VALUES ######
// Double array of all the values for each elg pid.
//              1a 1b 2a 2b 3a 3b 4a 4b
double kp[8] = {2, 6, 2, 6, 2, 6, 2, 6};
double ki[8] = {18, 18, 18, 18, 18, 18, 18, 18};
double kd[8] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01};

double L1Asetpoint = 600, L1AInput, L1AOutput, L1Bsetpoint = 600, L1BInput, L1BOutput;
PID L1A(&L1AInput, &L1AOutput, &L1Asetpoint, 0, 0, 0, DIRECT);
PID L1B(&L1BInput, &L1BOutput, &L1Bsetpoint, 0, 0, 0, DIRECT);

double L2Asetpoint = 600, L2AInput, L2AOutput, L2Bsetpoint = 600, L2BInput, L2BOutput;
PID L2A(&L2AInput, &L2AOutput, &L2Asetpoint, 0, 0, 0, DIRECT);
PID L2B(&L2BInput, &L2BOutput, &L2Bsetpoint, 0, 0, 0, DIRECT);

double L3Asetpoint = 600, L3AInput, L3AOutput, L3Bsetpoint = 400, L3BInput, L3BOutput;
PID L3A(&L3AInput, &L3AOutput, &L3Asetpoint, 0, 0, 0, DIRECT);
PID L3B(&L3BInput, &L3BOutput, &L3Bsetpoint, 0, 0, 0, DIRECT);

double L4Asetpoint = 600, L4AInput, L4AOutput, L4Bsetpoint = 600, L4BInput, L4BOutput;
PID L4A(&L4AInput, &L4AOutput, &L4Asetpoint, 0, 0, 0, DIRECT);
PID L4B(&L4BInput, &L4BOutput, &L4Bsetpoint, 0, 0, 0, DIRECT);


int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// Temp bool for direction of dog leg.
boolean dirTog = false;

void setup() {
  
ini();

piWD();

setupPID();

// Enable all legs to get running
enableLegs(true);
}


void loop() {
emgSTOP();

//updateAllPots();
picom();
//cal();

updateLEGS();
//pop();

wave();

delay(50);
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

boolean waveTog;

void wave(boolean tog)
{
waveTog = tog;
if(waveTog == true)
{
  
}
enableLegs(false); // disable all legs for top designs filming.

legEnable(2, true); // enable leg 2 to wave.

// if 250 then invert dir
if(c_buffer[69] < 100)
{
  dirTog = true;
}
else if(c_buffer[69] > 800) // Move oposite once reach max angle.
{
 dirTog = false; 
}

// Subtract 10 from setpoint for each loop.
if(dirTog == false)
{
  c_buffer[69] = c_buffer[69] - 10;
} else if (dirTog == true) // Add 10 to set point each loop.
{
  c_buffer[69] = c_buffer[69] + 10;
}


// Set B axis to solid for wave program.
c_buffer[70] = 800;
}
