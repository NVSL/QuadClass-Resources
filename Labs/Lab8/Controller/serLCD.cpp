/*
 serLCD.cpp - Library for controlling a SparkFun serLCD
              module.
	      Code written for firmware version 2.5

 Created by Cody B. Null, September 9, 2011
 Modified by Jordan Hochenbaum, Dec 5, 2011. (Version 1.5)

 Modified again for sparkfun's serial LCD screen


*/


#include "arduino.h"
#include "serLCD.h"

//	PUBLIC FUNCTIONS

// Contstructor
// defaults to 16x2 display
serLCD::serLCD(){
	Serial1.begin(9600);
	_numlines = LCD_2LINE;
	_numchars = LCD_16CHAR;
	_rowoffset = 0;
}

/* Initialize.. not used trying to implement all display sizes
void serLCD::init(int pin, int rows, int cols){
	pinMode(pin, OUTPUT);
	delay(4);
	begin(9600);
	if(cols == LCD_20CHAR){
		_numchars = LCD_20CHAR;
		specialCommand(LCD_SET20CHAR);
	}else{ // default to 16 char display
		_numchars = LCD_16CHAR;
		specialCommand(LCD_SET16CHAR);
	}	
	if(rows == LCD_4LINE){
		_rowoffset = 1;
		_numlines = LCD_4LINE;
		specialCommand(LCD_SET4LINE);
	}else{ // default to 2 line if input was invalid 
		_rowoffset = 0;
		_numlines = LCD_2LINE;
		specialCommand(LCD_SET2LINE);
	}
	// clear the display
	clear();
	// set brightness to full
	setBrightness(30);
}
*/

// Set brightness value range 1-30 1=OFF 30=FULL
void serLCD::setBrightness(int val){
	if(val >= 1 && val <= 30){
		specialCommand(LCD_BACKLIGHT | (val - 1));
	}
}

// Clears screen and returns cursor to home position
void serLCD::clear(){
	command(LCD_CLEARDISPLAY);
}

// Clears a single line by writing blank spaces then returning
// cursor to beginning of line
void serLCD::clearLine(int num){
	if(num >= 0 && num < _numlines){
		setCursor(num, 0);
		print("                ");
		setCursor(num, 0);
	}
}

// Moves cursor to the beginning of selected line
void serLCD::selectLine(int num){
	if(num >= 0 && num < _numlines){
		setCursor(num, 0);
	}
}

// returns cursor to home position
void serLCD::home(){
	command(LCD_RETURNHOME);
}

// Saves first 2 lines of txt to splash screen memory
void serLCD::setSplash(){
	specialCommand(LCD_SETSPLASHSCREEN);
}

// Toggles splashscreen on and off
void serLCD::toggleSplash(){
	specialCommand(LCD_SPLASHTOGGLE);
}

//  This is for text that flows Left to Right
void serLCD::leftToRight(){
	_displaymode |= LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void serLCD::rightToLeft() {
	_displaymode &= ~LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// Blinking cursor on/off
void serLCD::blink(){
	_displaycontrol |= LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void serLCD::noBlink(){
	_displaycontrol &= ~LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Underline cursor on/off
void serLCD::cursor(){
	_displaycontrol |= LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void serLCD::noCursor(){
	_displaycontrol &= ~LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Display on/off
void serLCD::display(){
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void serLCD::noDisplay(){
	_displaycontrol &= ~LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}


void serLCD::setCursor(int row, int col){
	int row_offsets[2][4] = {
		{ 0x00, 0x40, 0x10, 0x50 },
		{ 0x00, 0x40, 0x14, 0x54 }
	};
	if((row >= 0 && row < 2) && (col >= 0 && col < 16)){
           command(LCD_SETDDRAMADDR | (col + row_offsets[_rowoffset][row]));
	}
}

// Creates custom characters 8 char limit
// Input values start with 1
void serLCD::createChar(int location, uint8_t charmap[]){
	location -= 1;
	location &= 0x07;
  for (int i=0; i<8; i++){
    command(LCD_SETCGRAMADDR | (location << 3) | i);
    write(charmap[i]);
  }
}

// Prints custom character
// Input values start with 1
void serLCD::printCustomChar(int num){
	write((num - 1));
}

void serLCD::print(const char * str){
	Serial1.print(str);
}

void serLCD::print(uint16_t val){
	Serial1.print(val);
}

// PRIVATE FUNCTIONS

// Functions for sending the special command values
void serLCD::command(uint8_t value){
	write(0xFE);
	write(value);
	delay(5);
}
void serLCD::specialCommand(uint8_t value){
	write(0x7C);
	write(value);
	delay(5);
}

void serLCD::write(uint8_t byte){
	Serial1.write(byte);
}

void serLCD::write(int number){
	Serial1.write(number);
}




