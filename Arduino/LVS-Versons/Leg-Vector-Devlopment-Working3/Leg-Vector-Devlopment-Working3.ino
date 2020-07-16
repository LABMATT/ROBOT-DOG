/*
 * CODE WRITTEN BY LABMATT (Matthew Lewington)
 * For year 12 systesm robotic dog project
 *
 */
 #include <PID_v1.h> 

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=0, Kd=0; //kp0.3, ki0.4,kd=0.2
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

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

int fog = 45;


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

  Input = analogRead(potA);
  Setpoint = 500;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

// Main loop.
void loop() {

if(Serial.available() > 0)
{
  int ph = Serial.parseInt();
  if(ph != 0)
  {
   fog = ph; 
     Serial.println("TRIGGED SERIAL EVENT");

  } 
}
  Serial.print("Angle set as: ");
  Serial.println(fog);

testAngle(fog);
legManger();
}

void testAngle(int angle)
{
  int posSh;
  if(angle > -1 && angle < 91)
  {
    posSh = map(angle, 0, 90, L1A0, L1A90);

    Serial.print("90 : Your pot value should be: ");
    Serial.println(posSh);

  Serial.print("POTA: ");
  Serial.println(analogRead(potA));

  L1currentAngle = posSh;
  } else if(angle > 89 && angle < 181)
  {
    posSh = map(angle, 90, 180, L1A90, L1A180);

    Serial.print("180 : Your pot value should be: ");
    Serial.println(posSh);

  Serial.print("POTA: ");
  Serial.println(analogRead(potA));

  }
  L1currentAngle = posSh;
  Setpoint = posSh;
}

void legManger()
{
  Input = analogRead(potA);
  myPID.Compute();
  
  if(analogRead(potA) > L1currentAngle+0 || analogRead(potA) < L1currentAngle-0)
  {
Serial.println("Leg is in the wrong postion.");

// Output = PID_total;


  Serial.print("PID in is: ");
  Serial.println(Input);
  Serial.print("PID out is: ");
  Serial.println(Output);

   
if(analogRead(potA) < L1currentAngle)
   {
    Serial.println("pot less than angle");
    
      analogWrite(ptAn, 255 - Output);
      digitalWrite(ptAp, HIGH);
       
   } else if(analogRead(potA) > L1currentAngle)
   {
        Serial.println("pot greather than angle");

       analogWrite(ptAn, Output);
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
