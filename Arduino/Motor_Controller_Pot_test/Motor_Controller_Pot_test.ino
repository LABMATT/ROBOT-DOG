int ma1 = 10;
int ma2 = 11;

int mb1 = 9;
int mb2 = 8;

int pot = A2;

int spda = 5;
int spdb = 6;

int i;
int out;

void setup() {
  // put your setup code here, to run once:

  pinMode(ma1, OUTPUT);
    pinMode(ma2, OUTPUT);
      pinMode(mb1, OUTPUT);
    pinMode(mb2, OUTPUT);
     pinMode(spda, OUTPUT);
    pinMode(spdb, OUTPUT);
    pinMode(pot, INPUT);

Serial.begin(9600);
Serial.println("started");
}

void loop() {
  //Serial.println("hi+");
  // put your main code here, to run repeatedly:
  digitalWrite(ma1, HIGH);
  digitalWrite(ma2, LOW);

  digitalWrite(mb1, HIGH);
  digitalWrite(mb2, LOW);

   i = analogRead(pot);
   out = map(i, 0, 1023, 0, 255);

  Serial.println(out);

  

  analogWrite(spda, out);
   analogWrite(spdb, out);

 
}
