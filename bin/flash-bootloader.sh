#!/usr/bin/bash

avrdude -c usbtiny -p atmega128rfa1
sleep 1;  
avrdude -p atmega128rfa1 -c usbtiny -e -u -U lfuse:w:0xff:m -U hfuse:w:0xda:m -Uefuse:w:0xf5:m lock:w:0x3F:m; 
sleep 1; 
avrdude -p atmega128rfa1 -c usbtiny -B 1 -U flash:w:ATmegaBOOT_atmega128rfa1.hex -U lock:w:0x0f:m

