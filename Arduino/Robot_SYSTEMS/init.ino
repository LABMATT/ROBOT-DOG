/*
 * Sets arduino up with pinmodes and everything on startup.
 */

void ini()
{
Serial.begin(2000000);
Serial.println("_avr_booting");
  
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

initBuffer();

for(int i = 66; i < 78;i++)
{
  c_buffer[i] = 600;
  Serial.println("In loop");
  Serial.println(i);
}

//TEPORY FOR PHOTO SET LEG STRIGHT
c_buffer[73] = 500;

Serial.begin(2000000);
//Serial.setTimeout(50);

Serial.println("_avr_online");
}


// Set up all the pid values. 
void setupPID()
{

  // Set up leg 1 A PID
  L1AInput = potRead(1,'A');
  L1A.SetMode(AUTOMATIC);
  L1A.SetOutputLimits(-255, 255);
  L1A.SetSampleTime(50);
  L1A.SetTunings(kp[0], ki[0], kd[0]);

  // Set up leg 1 B PID
  L1BInput = potRead(1,'B');
  L1B.SetMode(AUTOMATIC);
  L1B.SetOutputLimits(-255, 255);
  L1B.SetSampleTime(50);
  L1B.SetTunings(kp[1], ki[1], kd[1]);


  // Set up leg 2 A PID
  L2AInput = potRead(2,'A');
  L2A.SetMode(AUTOMATIC);
  L2A.SetOutputLimits(-255, 255);
  L2A.SetSampleTime(50);
  L2A.SetTunings(kp[2], ki[2], kd[2]);

  // Set up leg 2 B PID
  L2BInput = potRead(2,'B');
  L2B.SetMode(AUTOMATIC);
  L2B.SetOutputLimits(-255, 255);
  L2B.SetSampleTime(50);
  L2B.SetTunings(kp[3], ki[3], kd[3]);


  // Set up leg 3 A PID
  L3AInput = potRead(3,'A');
  L3A.SetMode(AUTOMATIC);
  L3A.SetOutputLimits(-255, 255);
  L3A.SetSampleTime(50);
  L3A.SetTunings(kp[4], ki[4], kd[4]);

  // Set up leg 3 B PID
  L3BInput = potRead(3,'B');
  L3B.SetMode(AUTOMATIC);
  L3B.SetOutputLimits(-255, 255);
  L3B.SetSampleTime(50);
  L3B.SetTunings(kp[5], ki[5], kd[5]);


  // Set up leg 4 A PID
  L4AInput =  potRead(4,'A');
  L4A.SetMode(AUTOMATIC);
  L4A.SetOutputLimits(-255, 255);
  L4A.SetSampleTime(50);
  L4A.SetTunings(kp[6], ki[6], kd[6]);

  // Set up leg 4 B PID
  L4BInput =  potRead(4,'B');
  L4B.SetMode(AUTOMATIC);
  L4B.SetOutputLimits(-255, 255);
  L4B.SetSampleTime(50);
  L4B.SetTunings(kp[7], ki[7], kd[7]);
}
