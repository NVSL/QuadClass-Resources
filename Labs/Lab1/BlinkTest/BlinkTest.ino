void setup() {
  pinMode(34, OUTPUT);  //Pin B6 as output
}

void loop() {
  digitalWrite(34, LOW); //Turn off led 
  delay(1000);           //Delay 1000 milliseconds or 1 second
  digitalWrite(34, HIGH);//Turn on led
  delay(1000);           //Delay 1000 milliseconds or 1 second
}
