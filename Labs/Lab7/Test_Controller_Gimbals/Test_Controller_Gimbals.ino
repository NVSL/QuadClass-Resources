/*
Gimbals Test:
Check that when moving the joysticks the values change in a range from (300 - 700) aprox
in each direction THROTTLE, YAW, PITCH using the Serial Monitor;
*/

#include <Wire.h>
#include <EEPROM.h>

uint16_t THROTTLE = 0, YAW =0, PITCH =0, ROLL = 0;  
char buff[124];

void setup()
{
  Serial.begin(9600);
  analogReference(DEFAULT);
}

void loop()
{
  THROTTLE = analogRead(2);
  YAW = analogRead(1);
  PITCH= analogRead(4);
  ROLL = analogRead(3);
  
  sprintf(buff,
    "THROTTLE= %i\t YAW = %i\t PITCH = %i\t ROLL= %i\t  ",
     THROTTLE, YAW, PITCH, ROLL);
     
  Serial.println(buff);
  
  delay(250);
}





