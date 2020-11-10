void LEG1verification()
{
  digitalWrite(L1enable, HIGH);
  
  analogWrite(L1Apwm, 60);  
  analogWrite(L1Bpwm, 60);

  digitalWrite(L1An, HIGH);
  digitalWrite(L1Bn, HIGH);

  pinMode(L1Apot, OUTPUT);
  pinMode(L1Bpot, OUTPUT);
  pinMode(L1Cpot, OUTPUT);
  //digitalWrite(L1Apot, HIGH);
  //digitalWrite(L1Bpot, HIGH);
  digitalWrite(L1Cpot, HIGH);
}

void LEG2verification()
{
  digitalWrite(L2enable, HIGH);

  analogWrite(L2Apwm, 60);  
  analogWrite(L2Bpwm, 60);

  digitalWrite(L2An, HIGH);
  digitalWrite(L2Bn, HIGH);

  pinMode(L2Apot, OUTPUT);
  pinMode(L2Bpot, OUTPUT);
  pinMode(L2Cpot, OUTPUT);
  //digitalWrite(L2Apot, HIGH);
  //digitalWrite(L2Bpot, HIGH);
  //digitalWrite(L2Cpot, HIGH);
}

void LEG3verification()
{
  digitalWrite(L3enable, HIGH);
  
  analogWrite(L3Apwm, 60);  
  analogWrite(L3Bpwm, 60);

  //digitalWrite(L3An, HIGH);
  digitalWrite(L3Bn, HIGH);

  pinMode(L3Apot, OUTPUT);
  pinMode(L3Bpot, OUTPUT);
  pinMode(L3Cpot, OUTPUT);
  //digitalWrite(L3Apot, HIGH);
  //digitalWrite(L3Bpot, HIGH);
  //digitalWrite(L3Cpot, HIGH);
}

void LEG4verification()
{
  //digitalWrite(L4enable, HIGH);
  
  //analogWrite(L4Appwm, 60);  
  //analogWrite(L4Bppwm, 60);

  //digitalWrite(L4An, HIGH);
  //digitalWrite(L4Bn, HIGH);

  pinMode(L4Apot, OUTPUT);
  pinMode(L4Bpot, OUTPUT);
  pinMode(L4Cpot, OUTPUT);
  //digitalWrite(L4Apot, HIGH);
  //digitalWrite(L4Bpot, HIGH);
  //digitalWrite(L4Cpot, HIGH);
}
