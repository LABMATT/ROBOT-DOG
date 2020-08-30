
// Pots to read
int L_1Ap = 0;
int L_1B = 0;
int L_1C = 0;

int L1Apot = A1;
#define L1Bpot A2
#define L1Cpot A3

void setup() {
  pinMode(L1Apot, INPUT);
  pinMode(L1Bpot, INPUT);
  pinMode(L1Cpot, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(potRead(1, 'A'));

  Serial.print("pointer Val: ");
  Serial.println(L_1Ap);

}


int potRead(int leg, char part)
{
  int pot;
  int *myPointer;

  switch(leg)
  {
    case 1:
    switch(part)
    {
      case 'A':
      pot = L1Apot;
      myPointer = &L_1Ap;
      
    }
  }

int reader = analogRead(pot);

  /*
  for(int i = 0; i < 5; i++)
  {
    reader = reader + analogRead(pot);
  }

  reader = reader;
  */
  *myPointer = reader;
   

  return reader;
}
