/*
 * CODE WRITTEN BY LABMATT (Matthew Lewington)
 * For year 12 systesm robotic dog project
 *
 */

///////////////////////////////////////////////////
double kp = 1.61; // 1 worked well. (Force)
double ki = 0.0004; // 0.0004 (When its a little bit away)
double kd = 3; // 3 worked well. (Reacts to speed)
 
unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double input, Output, setPoint;
double cumError, rateError;
/////////////////////////////////////////////////////

 

////////////////////////Leg postion refrence points///////////////
int L1ARmax = 37;
int L1A0 = 185;
int L1A90 = 500;
int L1A180 = 820;
int L1ALmax = 980;
int L1currentAngle = 45;
///////////////////////////////////////////////////////

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


int fog = 10;
bool pretrig = false;
int period = 100;  //Refresh rate period of the loop is 50ms
float time;        //Variables for time control
int diver = 10;

// The acuruacy of the postioning. 3+- v on the pot avrage.
int ac = 3;


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

// Wait 10ms at end of serial to know if its the end.
Serial.setTimeout(10);

//Cal();

time = millis();
}

// Main loop.
void loop() {
 

  period = map(analogRead(A5), 0, 1023, 0, 500);
  //Serial.print("kd: ");
  //Serial.println(ki);

while(Serial.available() != 0)
{
       Serial.println(" FIRST TRIGGED SERIAL EVENT");

  int ph = Serial.parseInt();
  if(ph != 0)
  {
   fog = ph; 
     Serial.println("TRIGGED SERIAL EVENT");
  } 
}


   if (millis() > time+period)
  {
    time = millis();  
    //Serial.println("Time event.");

    if(fog < 0 || fog == 0)
    {
      diver = 20;
    } else if(fog > 180 || fog == 180)
    {
      diver = -20;
    }

    fog = fog + diver;
  }
  

  //Serial.print("Angle set as: ");
  //Serial.println(fog);

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
    //Serial.println(analogRead(potA));

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
  setPoint = posSh;
}

void legManger()
{
int total = 0;
  for(int i = 0; i < 10; i++)
  {
    total = total + analogRead(potA);
  }
total = total / 10;
Serial.println(total);

input = total;                //read from rotary encoder connected to A0
        Output = computePID(input);

        Output = abs(Output);

        if(Output > 255)
        {
          Output = 255;
        }

  if(total > L1currentAngle+ac || total < L1currentAngle-ac)
  {
    
//Serial.println("Leg is in the wrong postion.");
   
if(total < L1currentAngle)
   {
    //Serial.println("pot less than angle");
    
      analogWrite(ptAn, 255 - Output);
      digitalWrite(ptAp, HIGH);
       
   } else if(total > L1currentAngle)
   {
        //Serial.println("pot greather than angle");

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

double computePID(double inp){     
        currentTime = millis();                //get current time
        elapsedTime = (double)(currentTime - previousTime);        //compute time elapsed from previous computation
        
        error = setPoint - inp;                                // determine error
        cumError += error * elapsedTime;                // compute integral
        rateError = (error - lastError)/elapsedTime;   // compute derivative
 
        double out = kp*error + ki*cumError + kd*rateError;                //PID output               
 
        lastError = error;                                //remember current error
        previousTime = currentTime;                        //remember current time
 
        return out;                                        //have function return the PID output
}
