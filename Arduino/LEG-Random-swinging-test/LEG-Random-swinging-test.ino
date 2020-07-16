int ptAp = 8;
int ptAn = 9;

int ptBp = 10;
int ptBn = 11;

int potA = A0;
int potB = A1;

int speedPot = A5;

int prepotval = 0;
int potval;
int maped;

void setup() {
// put your setup code here, to run once:
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);

pinMode(10, OUTPUT);
pinMode(11, OUTPUT);

pinMode(potA, INPUT);
pinMode(potB, INPUT);
pinMode(speedPot, INPUT);

Serial.begin(9600);

}

void loop() {

  maped = map(analogRead(speedPot), 0, 1000, 0, 255);


stageA();
stageB();

Serial.println(analogRead(potB));
}

int stageA()
{
  
  prepotval = potval;
potval = analogRead(potA);


if(potval == prepotval)
{
  analogWrite(ptAn, 127);
}
else if(potval < 300)
{
  analogWrite(ptAn, maped);
  digitalWrite(ptAp, LOW);
  
} else if(potval > 900)
{
  analogWrite(ptAn, 255 - maped);
 digitalWrite(ptAp, HIGH);
}
}

int stageB()
{
if(analogRead(potB) < 300)
{
  analogWrite(ptBn, maped);
  digitalWrite(ptBp, LOW);
  
} else if(analogRead(potB) > 800)
{
  analogWrite(ptBn, 255 - maped);
 digitalWrite(ptBp, HIGH);
}}
