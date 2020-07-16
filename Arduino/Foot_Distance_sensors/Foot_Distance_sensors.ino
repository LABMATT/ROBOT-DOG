int in = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(in, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(analogRead(in));

}
