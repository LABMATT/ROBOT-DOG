/*
 * CODE WRITTEN BY LABMATT (Matthew Lewington)
 * For year 12 systesm robotic dog project
 *
 *PID from: https://www.teachmemicro.com/arduino-pid-control-tutorial/#:~:text=Implementing%20PID%20in%20Code,value%20and%20set%20point%20value.&text=output%20%3D%20Kp%20*%20error%20%2B%20Ki%20*%20cumError,-%2B%20Kd%20*%20rateError%3B&text=Here%2C%20the%20Kp%2C%20Ki%20and%20Kd%20are%20the%20predetermined%20constants.
 */

///////////////////////////////////////////////////
double kp = 0.4; // 1.61 or 0.5 worked well. (Force)
double ki = 0; // 0.0004 (When its a little bit away)
double kd = 3; // 3 worked well. (Reacts to speed)
 
unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double input, Output, setPoint;
double cumError, rateError;
/////////////////////////////////////////////////////

 

////////////////////////Leg 1 voltage postion refrence points ///////////////
int L1ARmax = 37;
int L1AR140 = 52; // 140 degreese left
int L1A90 = 513; // center
int L1AL140 = 976;
int L1ALmax = 980; //
int L1currentAngle = 45;

int L1BRmax = 90; // 50
int L1B0 = 245; // 0 degreese
int L1B90 = 494; // 90 degreese
int L1B180 = 765; // 180 degreese
int L1BLmax = 905; // 50 degreese
int L1BcurrentAngle = 45;

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


int fog = 90;
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
 Serial.println(" ");
  Serial.println(" ");

 Serial.println(" ");


 // period = map(analogRead(A5), 0, 1023, 0, 500);
  //Serial.print("kd: ");
  //Serial.println(ki);

while(Serial.available() != 0)
{
       Serial.println(" FIRST TRIGGED SERIAL EVENT");

  int ph = Serial.parseInt();
  if(ph != 0)
  {
    if(ph == 2000)
    {
      fog = 0;
    } else 
    {
      fog = ph; 
    }
   
     Serial.println("TRIGGED SERIAL EVENT");
  } 
}

/*
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
  */
  

  Serial.print("Angle set as: ");
  Serial.println(fog);

testAngle(1, 'A', fog);
legManger();

}


////////////////////////////////////////// This is in charge of converting angle to voltage.
void testAngle(int leg, byte part, int angle)
{
int partMin;
int part90;
int partMax;
int returner;
int tempAngler;

switch(leg)
{
  case 1:
  if(part == 'A')
  {
   partMin = L1AR140;
   part90 = L1A90;
   partMax = L1AL140;
   returner = L1currentAngle;
   
  } else if(part == 'B')
  {
   partMin = L1BRmax;
   part90 = L1B90;
   partMax = L1BLmax;
   retuner = L1BcurrentAngle;
  }
  break;
}

Serial.print("angle in angler: ");
Serial.println(angle);

Serial.print("partMin: ");
Serial.println(partMin);

Serial.print("Part90: ");
Serial.println(part90);

Serial.print("partMax: ");
Serial.println(partMax);


// Using preset values preform the pot to voltage convertion.
 if(angle < 0)
    {
      if(angle > -140)
      {
        angle = -140;
        }
      Serial.println("less than 0");
      angle = abs(angle);
     L1currentAngle = map(angle, 0, 140, part90, partMin);
    } else if(angle > 0)
    {
      if(angle > 140)
      {
        angle = 140;
        }
     L1currentAngle = map(angle, 0, 140, part90, partMax);
    } else 
    {
      L1currentAngle = part90;
    }

Serial.print("Angle Needed: ");
Serial.println(L1currentAngle);

/*
// Convert Quadrants to angles. Then Angles to volts. 
if(x < 0 && y < 0)
{
  
  // If both x and y are negative.
  L1currentAngle = map(angle, 0, 53, L1A180, L1ALmax);
  
} else if(x < 0)
{

   // If x is negative. 
  taskAngle = 90 + angle;
  
} else if(y < 0)
{

  //If y is negative.
  taskAngle = map(angle, 0, 53, L1A0, L1ARmax);

}

  
  // If angle is between 0-90 then map between these pot voltages.
  if(angle > -1 && angle < 91)
  {
    L1currentAngle = map(angle, 0, 90, L1A0, L1A90);
  } else if(angle > 89 && angle < 181)
  {
    L1currentAngle = map(angle, 90, 180, L1A90, L1A180);
  }
  */
}


////////////////////////////////// Leg manger is in charge of Moving the leg to that voltage. Handles PID.
void legManger()
{
  setPoint = L1currentAngle;
  
int total = 0;
  for(int i = 0; i < 10; i++)
  {
    total = total + analogRead(potA);
  }
total = total / 10;

Serial.print("Angle Current: ");
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
    
Serial.println("Leg is in the wrong postion.");
   
if(total < L1currentAngle)
   {
    Serial.println("pot less than angle");
    
      analogWrite(ptAn, 255 - Output);
      digitalWrite(ptAp, HIGH);
       
   } else if(total > L1currentAngle)
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
