/*
  BlinkTest
*/

char tmpBuf[128];       // Temporary buffer
int i = 0;	  

void setup() {
  pinMode(34, OUTPUT);  // Pin B6 as output
  Serial.begin(9600);   // Start up serial with baud rate = 9600
}

void loop() {
  // Blink led
  digitalWrite(34, LOW); // Turn off led 
  delay(1000);           // Delay 1000 milliseconds or 1 second
  digitalWrite(34, HIGH);// Turn on led
  delay(1000);           // Delay 1000 milliseconds or 1 second
  
  // Print some data
  sprintf(tmpBuf, "%i. HELLO WORLD \n\r", i++);
  Serial.print(tmpBuf);  // Send data to serial port
}
