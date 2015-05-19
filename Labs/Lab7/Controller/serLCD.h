/*
 serLCD.h - Library for controlling a SparkFun serLCD module
	    Code written for firmware version 2.5

 Created by Cody B. Null, September 9, 2011
 Modified by Jordan Hochenbaum, Dec 5, 2011. (Version 1.5)

 Version 1.4 - This version wrote specifically for 16x2
               Display.
               More display support coming in later version.
 
 Version 1.5 - Since mid 2011 the Arduino IDE has implemented the NewSoftSerial 
               library updates in the standard SoftwareSerial library and so 
               using NewSoftSerial is no longer needed. serLCD has been updated 
               to use the Standard SoftwareSerial library. Also, Arduino 1.0
               support has been added. Backwards compatible with previous versions.

 Note -	This library requires NewSoftSerial library
        The latest version of NewSoftSerial library can 
        always be found at http://arduiniana.org. -> NO LONGER NECESSARY. See 1.5 notes above.-Jordan Hochenbaum
*/


#ifndef serLCD_h
#define serLCD_h

// Commands
#define LCD_BACKLIGHT		0x80
#define LCD_CLEARDISPLAY	0x01
#define LCD_CURSORSHIFT		0x10
#define LCD_DISPLAYCONTROL	0x08
#define LCD_ENTRYMODESET	0x04
#define LCD_FUNCTIONSET		0x20
#define LCD_SETCGRAMADDR	0x40
#define LCD_SETDDRAMADDR	0x80
#define LCD_SETSPLASHSCREEN	0x0A
#define LCD_SPLASHTOGGLE	0x09
#define LCD_RETURNHOME		0x02

// Flags for display entry mode
#define LCD_ENTRYRIGHT		0x00
#define LCD_ENTRYLEFT		0x02

// Flags for display on/off control
#define LCD_BLINKON		0x01
#define LCD_CURSORON		0x02
#define LCD_DISPLAYON		0x04

// Flags for display size
#define LCD_2LINE		0x02
#define LCD_4LINE		0x04
#define LCD_16CHAR		0x10
#define LCD_20CHAR		0x14

//  Flags for setting display size
#define LCD_SET2LINE		0x06
#define LCD_SET4LINE		0x05
#define LCD_SET16CHAR		0x04
#define LCD_SET20CHAR		0x03

class serLCD{
public:
	serLCD ();

	void clear();
	void clearLine(int);
	void home();
	void setBrightness(int);

	void setSplash();
	void toggleSplash();

	void blink();
	void noBlink();
	void cursor();
	void noCursor();
	void display();
	void noDisplay();

	void setCursor(int, int);
	void selectLine(int);

	void leftToRight();
	void rightToLeft();
	void autoscroll();
	void noAutoscroll();

	void createChar(int, uint8_t[]);
	void printCustomChar(int);

    void print(const char *);
    void print(uint16_t);


private:
	void command(uint8_t);
	void specialCommand(uint8_t);

    void write(uint8_t);
    void write(int);

	uint8_t _displayfunction;
	uint8_t _displaycontrol;
	uint8_t _displaymode;
	uint8_t _numlines;
	uint8_t _numchars;
	uint8_t _rowoffset;
};

#endif