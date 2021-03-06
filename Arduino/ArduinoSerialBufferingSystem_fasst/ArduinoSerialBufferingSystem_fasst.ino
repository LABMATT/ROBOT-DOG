/*
 * SERIAL BUFFER TEST
 * designed to understnad and send and recive info from the serial buffer efficently.
 */

 // Buffers storing data
 int c_buffer[10];
 int p_buffer[10];

 // Time between each serial buffer dump. Interval = amout of time between serial dumps.
 long previousMillis = 0;
 long interval = 1000;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("get ready");

initBuffer();

c_buffer[0] = 1;
c_buffer[9] = 26;
Serial.println("All systems go");
delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:

updateBuffer();

c_buffer[0]++;
}


// Checks if the buffer has changed. If so send it over serial
void updateBuffer()
{
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    
    previousMillis = currentMillis;
    int asize = (sizeof(c_buffer) / sizeof(c_buffer[0]));
    
  for(int i = 0; i < 10;i++)
  {
    int currentBuffer = c_buffer[i];
    int lastBuffer = p_buffer[i];
    
    if(currentBuffer != lastBuffer)
    {
      Serial.print(i);
      Serial.print(":");
      Serial.print(currentBuffer);
      Serial.print("\n");
      
      p_buffer[i] = c_buffer[i];
    }
  }
  }
}

// Sets the buffer all to 0.
void initBuffer()
{

int asize = (sizeof(c_buffer) / sizeof(c_buffer[0]));
  
  for(int i = 0; i < asize; i++)
  {
    c_buffer[i] = 0;
    p_buffer[i] = 0;
  }
}
