#!/bin/bash

/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avrdude -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega128rfa1 -carduino -P$1 -b57600 -D -Uflash:w:$2:i

