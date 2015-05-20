/*
Button Test:
Press the button and check if the state changes in the Serial Port
*/

#include <Wire.h>
#include <EEPROM.h>

void setup()
{
  Serial.begin(9600);
  pinMode(7,INPUT);
}

void loop()
{
  
  if(digitalRead(7) == 1) {
    Serial.println("Button High (1)");
  } else {
    Serial.println("Button Low (0)");
  }
  delay(500);

}





