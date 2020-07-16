/*
 * CODE WRITTEN BY LABMATT (Matthew Lewington)
 * For year 12 systesm robotic dog project
 *
 */

//OffsetMaps for lets.
//Offset = leg at 0 postion = voltage at zeropstion maped to 360 then add angle to 0 to get to 90 for new 0.
//Offset R should be smallest number (moving left). Offset L should be largest (moving right)
int offsetAR = 55; 
int offsetAL = 950;
int offsetBR = 55;
int offsetBL = 950;
//A/B total range
int Atr = offsetAL - offsetAR;
int Btr = offsetBL - offsetAR;
//the angle diffrnce between max offset and 0 on the leg parts.
#define AangDifToZer 55
#define BangDifToZer 55



int Amap;
int Bmap;

//PT_A postive/negative pins
int ptAp = 8;
int ptAn = 9;

//PT_B postive/negative pins
int ptBp = 10;
int ptBn = 11;

//Pots for A/B
int potA = A0;
int potB = A1;

//Change the speed of movment.
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

Cal();

}

void loop() {

  maped = map(analogRead(speedPot), 0, 1000, 0, 255);


stageA();
stageB();

Serial.println(analogRead(potB));
}

int Cal()
{
  Serial.println("Calbration settings.");
 
  while(0 == 0)
  { 
  Serial.print("POTA: ");
  Serial.println(analogRead(potA));

  Serial.print("POTB: ");
  Serial.println(analogRead(potB));

  Serial.println(" ");
  delay(5000);
  }
}

//Leg mangment system. In charge of converting the angle to a postion on the pot.
int LMS(int leg, char part, int angle)
{
switch(leg)
{
  case 1:
  switch(part)
  {
    case a:
    
  }
}
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
