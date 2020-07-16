/*
 * CODE WRITTEN BY LABMATT (Matthew Lewington)
 * For year 12 systesm robotic dog project
 *
 */

////////////////////////Variables///////////////////////
int Read = 0;
float distance = 0.0;
float elapsedTime, time, timePrev;        //Variables for time control
float distance_previous_error, distance_error;
int period = 50;  //Refresh rate period of the loop is 50ms
///////////////////////////////////////////////////////

///////////////////PID constants///////////////////////
float kp=0; // 0.01 adjust first(Force to reaction)
float ki=1.0; //Mine was 1 (Error over time)
float kd=1; // 15.0 Mine was 1 ()
float distance_setpoint = 500;           //Should be the distance from sensor to the middle of the bar in mm
float PID_p, PID_i, PID_d, PID_total;
///////////////////////////////////////////////////////
 

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

time = millis();
}

// Main loop.
void loop() {

  maped = map(analogRead(speedPot), 0, 1000, 0, 255);

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

//delay(4000);

//stageA();
//stageB();

//Serial.println(analogRead(potB));
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
  distance_setpoint = posSh;
}

void legManger()
{
  if(analogRead(potA) > L1currentAngle+8 || analogRead(potA) < L1currentAngle-8)
  {
Serial.println("Leg is in the wrong postion.");
    
int Output;
 if (millis() > time+period)
  {
    time = millis();    
    distance = analogRead(potA);   
    distance_error = distance_setpoint - distance;   
    PID_p = kp * distance_error;
    float dist_diference = distance_error - distance_previous_error;     
    PID_d = kd*((distance_error - distance_previous_error)/period);
      
    if(-3 < distance_error && distance_error < 3)
    {
      PID_i = PID_i + (ki * distance_error);
    }
    else
    {
      PID_i = 0;
    }
  
    PID_total = PID_p + PID_i + PID_d;  
    Serial.println(PID_total);
    PID_total = map(PID_total, -150, 150, 0, 255);
  Serial.println(PID_total);
 
    distance_previous_error = distance_error;
 Output = PID_total;
   
if(analogRead(potA) < L1currentAngle)
   {
    Serial.println("pot less than angle");
    
      analogWrite(ptAn, 255 - Output);
      digitalWrite(ptAp, HIGH);
       
   } else if(analogRead(potA) > L1currentAngle)
   {
        Serial.println("pot greather than angle");

       analogWrite(ptAn, 255-Output);
       digitalWrite(ptAp, LOW);
 
   } else
   {
      analogWrite(ptAn, 0);
      digitalWrite(ptAp, LOW);
   }
    
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
