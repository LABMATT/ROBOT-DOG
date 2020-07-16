/*
 * CODE WRITTEN BY LABMATT (Matthew Lewington)
 * For year 12 systesm robotic dog project
 *
 */

// Leg postion refrence points.
int L1ARmax = 37;
int L1A0 = 185;
int L1A90 = 500;
int L1A180 = 820;
int L1ALmax = 980;
int L1currentAngle = 45;


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

//Cal();

}


// Main loop.
void loop() {

  maped = map(analogRead(speedPot), 0, 1000, 0, 255);

testAngle(20);
legManger();

//delay(4000);

//stageA();
//stageB();

//Serial.println(analogRead(potB));
}

void testAngle(int angle)
{
  if(angle > -1 && angle < 91)
  {
    int posSh = map(angle, 0, 90, L1A0, L1A90);

    Serial.print("Your pot value should be: ");
    Serial.println(posSh);

  Serial.print("POTA: ");
  Serial.println(analogRead(potA));

  L1currentAngle = posSh;
  
  }
  
}

void legManger()
{
int speedos = 100;
  
  if(analogRead(potA) < L1currentAngle - 8 || analogRead(potA) > L1currentAngle + 8  )
  {
        Serial.println("leg not in right spot");

   if(analogRead(potA) < L1currentAngle)
   {
    Serial.println("pot less than angle");
    
      analogWrite(ptAn, 255 - speedos);
      digitalWrite(ptAp, HIGH);
       
   } else if(analogRead(potA) > L1currentAngle)
   {
        Serial.println("pot greather than angle");

       analogWrite(ptAn, speedos);
       digitalWrite(ptAp, LOW);
 
   } else
   {
      analogWrite(ptAn, 0);
      digitalWrite(ptAp, LOW);
   }
  }else
   {
      analogWrite(ptAn, 0);
      digitalWrite(ptAp, LOW);
   }
}


//Cal Mode
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
{/*
switch(leg)
{
  case 1:
  switch(part)
  {
    case a:
    
  }
}
*/
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
