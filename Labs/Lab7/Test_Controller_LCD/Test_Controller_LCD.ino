/*
LCD Display Test:
Check that the LCD Display prints "IT WORKS!" followed by a incrementing number"
*/

#include <Wire.h>
#include <EEPROM.h>
#include "serLCD.h"

serLCD sparkfun_lcd;

void setup()
{
  
}

void loop()
{
  static int i=0;
  sparkfun_lcd.clear();
  sparkfun_lcd.setCursor(0,0);
  sparkfun_lcd.print("IT WORKS! ");
  sparkfun_lcd.setCursor(1,0);
  sparkfun_lcd.print(i++);
  delay(500);

}





