#include <Servo.h>

//FOOT SENSOR BLOCK
#define L_1_sensor 53
#define L_2_sensor 52
#define L_3_sensor 51
#define L_4_sensor 50

// LEG-Axis-Postive/negative-pwm/nopwm

// #### LEG 1 ##############################################
int L_1A;
int L_1B;
int L_1C;

#define L1Aenable 22
#define L1Appwm 6
#define L1An 23

#define L1Benable 24
#define L1Bppwm 7
#define L1Bn 25

float L_1_Lenth;
Servo servo_Leg_1;

// #### LEG 2 ##############################################
int L_2A;
int L_2B;
int L_2C;

#define L2enable 41

#define L2Apwm 8
#define L2An 29

#define L2Bpwm 9
#define L2Bn 28

float L_2_Lenth;
Servo servo_Leg_2;

// #### LEG 3 ##############################################
int L_3A;
int L_3B;
int L_3C;

#define L3Aenable 10
#define L3Appwm 30
#define L3Bn 31

#define L3Benable 11
#define L3BpApwm 32
#define L3Bn 33

float L_3_Lenth;
Servo servo_Leg_3;

// #### LEG 4 ##############################################
int L_4A;
int L_4B;
int L_4C;

#define L4enable 43

#define L4Appwm 12
#define L4An 25

#define L4Bppwm 13
#define L4Bn 24

float L_4_Lenth = 3;
Servo servo_Leg_4;

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

void setup() {

servo_Leg_1.attach(2);
servo_Leg_2.attach(3);
servo_Leg_3.attach(4);
servo_Leg_4.attach(5);

pinMode(L1Aenable, OUTPUT);
pinMode(L1Appwm, OUTPUT);
pinMode(L1Benable, OUTPUT);
pinMode(L1Bn , OUTPUT);
pinMode(L1Bppwm, OUTPUT);
pinMode(L1Bn, OUTPUT);

pinMode(L2enable, OUTPUT);
pinMode(L2Apwm, OUTPUT);
pinMode(L2Bn, OUTPUT);
pinMode(L2Bpwm, OUTPUT);
pinMode(L2Bn, OUTPUT);

pinMode(L3Aenable, OUTPUT);
pinMode(L3Appwm, OUTPUT);
pinMode(L3Bn, OUTPUT);
pinMode(L3Benable, OUTPUT);
pinMode(L3BpApwm, OUTPUT);
pinMode(L3Bn, OUTPUT);

Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:


  testmotor();
Serial.println("working");
}


void testmotor()
{
 //LEG1verification();
  LEG2verification();
  // LEG4verification();
}
