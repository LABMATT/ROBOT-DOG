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

Serial.begin(2000000);
//Serial.setTimeout(50);

Serial.println("_avr_online");
}
