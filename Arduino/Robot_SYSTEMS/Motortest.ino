void LEG1verification()
{
  digitalWrite(L1Aenable, HIGH);
  
  analogWrite(L1Appwm, 60);  
  analogWrite(L1Bppwm, 60);

  digitalWrite(L1An, HIGH);
  digitalWrite(L1Bn, HIGH);
}

void LEG2verification()
{
  digitalWrite(L2enable, HIGH);

  //analogWrite(L2Apwm, 60);  
  //analogWrite(L2Bpwm, 60);

  //digitalWrite(L2An, HIGH);
  digitalWrite(L2Bn, HIGH);
}

void LEG4verification()
{
  //digitalWrite(L4enable, HIGH);
  
  //analogWrite(L4Appwm, 60);  
  //analogWrite(L4Bppwm, 60);

  //digitalWrite(L4An, HIGH);
  //digitalWrite(L4Bn, HIGH);
}
