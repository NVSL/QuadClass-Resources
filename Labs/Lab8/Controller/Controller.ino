

#include "RadioFunctions.h"
#include <Wire.h>
#include <EEPROM.h>
#include <limits.h>
#include "serLCD.h"


// Joystick values
union {
  struct stick{
    uint16_t ROLL;
    uint16_t PITCH;
    uint16_t YAW;
    uint16_t THROTTLE;
    uint16_t AUX1;
    uint16_t AUX2;
    uint16_t AUX3;
    uint16_t AUX4;
  } 
  m;
  uint16_t rc_channels[8];
  char buff[sizeof(struct stick)];
} 
stick_struct;

char txData[RF_BUFFER_SIZE];
char rxData[RF_BUFFER_SIZE];
char tmpBuf[32];	  // Just for printing

//Multiwii rx data
#define RC_CHANS 8
int16_t rcData[RC_CHANS];

//Analog pins corresponding to roll, pitch, yaw, throttle, in that order
int CH_PINS[] = {
  3,4,1,2};

//Less than this far away from center, and it's considered center
//In "RC" units
#define DEAD_ZONE 30  

unsigned int CH_LOWS[] = {
  0,0,0,0};   //Lowest analogRead value: pushing sticks down or left
unsigned int CH_HIGHS[] = {
  1023,1023,1023,1023};  //Highest value: sticks up/right
unsigned int CH_CENTERS[] = {
  500,500,500,500};     //Gimbals are not symmetric sometimes


byte CH_SWAPPED[] = {
  1,1,1,1};   //Gimbal values are reversed, this happens if you've installed it upside-down
unsigned int ADDR_START = 1337;

serLCD sparkfun_lcd;


//Was lazy, copy pasta'd these functions
//This function will write a 2 byte integer to the eeprom at the specified address and address + 1
void EEPROMWriteInt(int p_address, int p_value)
{
  byte lowByte = ((p_value >> 0) & 0xFF);
  byte highByte = ((p_value >> 8) & 0xFF);

  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);
}

//This function will read a 2 byte integer from the eeprom at the specified address and address + 1
unsigned int EEPROMReadInt(int p_address)
{
  byte lowByte = EEPROM.read(p_address);
  byte highByte = EEPROM.read(p_address + 1);

  return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}  



int buttonWait(int pin, unsigned int time, int high_state = 1){
  unsigned long start=millis();
  while(digitalRead(pin) == high_state){
    if(millis() - start > time)
      return 1;
  }
  return 0;
}


void calibrate(){
  Serial.print("Calibrating");
  sparkfun_lcd.clear();
  sparkfun_lcd.setCursor(0,0);
  sparkfun_lcd.print("Calibrating");
  sparkfun_lcd.setCursor(1,0);
  sparkfun_lcd.print("Center sticks");  
  delay(4000);

  unsigned long lcdMillis=0;
  int i, val;
  for(i=0;i<4;i++){
    CH_LOWS[i]=INT_MAX;
    CH_HIGHS[i]=0;
    CH_CENTERS[i] = analogRead(CH_PINS[i]);
    delay(100);
  }


  while(1){
    for(i=0;i<4;i++){
      val = analogRead(CH_PINS[i]);
      delay(3);
      if(val < CH_LOWS[i])
        CH_LOWS[i]=val;
      if(val > CH_HIGHS[i])
        CH_HIGHS[i] = val;
    }

    if(buttonWait(7, 2000, 1)){   //Quit if the button gets held down
      //Write the stuff to EEPROM
      sparkfun_lcd.clear();
      sparkfun_lcd.setCursor(0,0);
      sparkfun_lcd.print("Saving...");
      Serial.print("Saving...");
      for(i=0;i<4;i++){
        Serial.println("LOW\tCENTER\tHIGH");
        Serial.print(CH_LOWS[i]);
        Serial.print("\t");
        Serial.print(CH_CENTERS[i]);
        Serial.print("\t");
        Serial.println(CH_HIGHS[i]);
        EEPROMWriteInt(ADDR_START + 6*i,CH_LOWS[i]);
        EEPROMWriteInt(ADDR_START + 6*i + 2,CH_HIGHS[i]);
        EEPROMWriteInt(ADDR_START + 6*i + 4,CH_CENTERS[i]);
      }
      delay(2000);
      return;
    }

    if(millis() - lcdMillis > 500){
      lcdMillis = millis();
      sparkfun_lcd.clear();
      for(i=0;i<4;i++){
        Serial.print(CH_LOWS[i]);
        Serial.print("    ");
        Serial.print(CH_HIGHS[i]);
        Serial.print("    ");
        sparkfun_lcd.setCursor(0,4*i);
        sparkfun_lcd.print(CH_LOWS[i]);
        sparkfun_lcd.setCursor(1,4*i);
        sparkfun_lcd.print(CH_HIGHS[i]);
      }
      Serial.println("");
    }
  }
}


void setup()
{
  analogReference(DEFAULT);
  pinMode(6, INPUT); 
  pinMode(7,INPUT);
  Serial.begin(9600);
  Serial1.begin(9600);


  for(int i=0;i<4;i++){
    CH_LOWS[i] = EEPROMReadInt(ADDR_START + 6*i);
    CH_HIGHS[i] = EEPROMReadInt(ADDR_START + 6*i + 2);
    CH_CENTERS[i] = EEPROMReadInt(ADDR_START + 6*i + 4);
  }  
  

  for(int i=0;i<4;i++){
    Serial.print("CH_LOWS\tCH_HIGHS\tCH_CENTERS\t");
    Serial.print(i);
    Serial.println("");

    Serial.print(CH_LOWS[i]);
    Serial.print("\t");
    Serial.print(CH_HIGHS[i]);
    Serial.print("\t");
    Serial.print(CH_CENTERS[i]);
    Serial.println("");

  }

  // Add your initialization code here
  rfBegin(21);  // Initialize ATmega128RFA1 radio on channel 11 (can be 11-26)

  //Initialize values with some data
  stick_struct.m.ROLL = 1500;
  stick_struct.m.PITCH = 1600;
  stick_struct.m.YAW = 1500;
  stick_struct.m.THROTTLE = 1700;
  stick_struct.m.AUX1 = 1800;
  stick_struct.m.AUX2 = 1900;
  stick_struct.m.AUX3 = 2000;
  stick_struct.m.AUX4 = 2000;
  delay(1000);
  sparkfun_lcd.clear();
  sparkfun_lcd.print("Hello");
}


unsigned long lastMillis = 0;
uint16_t stick_values[8];


void loop()
{

  if(buttonWait(7,2000))
    calibrate();


  if(abs(millis()  - lastMillis) > 200){
    lastMillis = millis();
    sparkfun_lcd.setCursor(0,0);
    Serial.println("ROLL\tPITCH\tYAW\tTHROTTLE");
    sparkfun_lcd.print("ROL PIT YAW THR");
    sparkfun_lcd.clearLine(1);
    for(int i=0;i<4;i++){
      sparkfun_lcd.setCursor(1,i*4);
      sparkfun_lcd.print(stick_struct.rc_channels[i]);
      Serial.print(stick_struct.rc_channels[i]);
      Serial.print("\t");
    }
    Serial.println("");
  }


  for(int i=0;i<4;i++){
    int val = analogRead(CH_PINS[i]);
    delay(3);   // Let analogRead be dumb
    
    if(val < CH_CENTERS[i])
      val = map(val, CH_LOWS[i], CH_CENTERS[i], 0, 499);
    else
      val = map(val, CH_CENTERS[i], CH_HIGHS[i], 500, 1000);
      
    if(CH_SWAPPED[i])
      val = 1000 - val;
    
    val += 1000;
    if(val < 1500 + DEAD_ZONE && val > 1500 - DEAD_ZONE)
      val = 1500;

    stick_struct.rc_channels[i] = val;
  }


  // Copy the values to transmit buffer
  memcpy(&txData[0], stick_struct.buff, sizeof(stick_struct));
  txData[sizeof(stick_struct)]='\0';

  // Send Data in a serial format with null end
  rfPrint(txData, sizeof(stick_struct));
  
  delay(180);

}





