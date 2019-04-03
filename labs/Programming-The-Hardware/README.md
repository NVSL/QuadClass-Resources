# Arduino, Wireless, and Quadcopter Hardware

This is big lab, but there shouldn’t be many surprises. You’re mostly getting parts and pieces together for future labs. However, don’t assume it won’t take much time. There’s a lot to do. Get started!

## Pick your Team
You will work on this lab and all future labs in teams of two. You will need to create a team on Eaglint and via the github classroom interface. The name of your team in github classroom must match the team name you use in Eaglint, or Eaglint will refuse to check your work.

## Skills to Learn

1. Installing the Arduino GUI.
2. Programming your remote and the test stand board.
3. Communicating with the boards using an FTDI serial port.
4. Communicate wirelessly between the two boards.
5. Reading values from the controller gimbals.
6. Use the other features of the remote.
7. Driving a DC motor with PWM.

## Equipment, Supplies, and Software You Will Need

1. The starter repo for this lab: .
2. 1 fully-assembled remote control.
4. 1 micro USB cable.
5. The contents of the github repo for the remote control (https://github.com/NVSL/Quadcopter-Remote) for reference.
6. 1 flight control board (FCB).
7. Two LiPo batteries.
8. Laser-cut parts for a test stand and airframe.
9. 1 set of motors.
10. 1 set of matched propellers (2xCW, 2xCCW)
11. 4 small zip ties.
12. Four short screws, four nuts, and four 3mm nylon spacers.
13. One set of four motors.
14. One set of propellors: 2 CW and 2 CCW.

### Your Remote Control

You are responsible for the care of the remote:

1. If you break it, you'll need to pay replace the broken parts.
2. Be reasonably gentle with the gimbals (joysticks). They are of high quality, but are not indestructible.
3. Be careful to install the batteries in the correct orientation.  This mostly means attaching the battery leads to the screw terminals correctly (red is '+').

### Your Flight Control Board and Test Stand

The flight control board (FCB) is a PCB very similar to the quadcopter
you will eventually build.  It mounts to the test stand and will
provide a platform for your initial quadcopter firmware development.
The flight control boards are provided for your use during the class.

## Preliminaries 

### Install Arduino

Install Arduino 1.8.5 or
later.  This is the only version we will be supporting in class.

### Setup Your Firmware Development Environment

The repo you create and use for this lab will be the repository you use for your software development during the rest of the class. The `firmware` directory is organized as an Arduino Sketchbook, which means the Arduino toolchain and IDE know where to look for things.  To use it, you’ll need to set that directory as your sketch book directory in Arduino (`Preferences->Sketchbook location`).

#### Add Board Definition Files

This will let Arduino talk to all the boards we will be using in this class, including your quadcopter.

* Clone the Arduino addon (https://github.com/NVSL/QuadClass_Atmega128RFA_Arduino_Addon) into `firmware/hardware`.  You should end up with this directory `firmware/hardware/QuadClass_Atmega128RFA_Arduino_Addon/avr`.
* Restart Arduino.  Then, under `Tool->Board` you should see `Quad Class ATmega128RFA1 Boards`.  Select that board.
* Select `Tools->Programmer->USBTinyISP`

#### Install the Libraries

You’ll need a few libraries, so you might as well install them now, but you won’t use all of them in this lab:

1. Attitude, Heading, and Reference System (AHRS): https://github.com/NVSL/QuadClass_AHRS 
2. Adafruit LSM96S1 library: https://github.com/NVSL/QuadClass_LSM9DS1
3. Adafruit unified sensor library: https://github.com/NVSL/QuadClass_Sensor
4. Sparkfun SerLCD library: https://github.com/sparkfun/SparkFun_SerLCD_Arduino_Library

Clone them into `firmware/libraries`.

There are a few libraries you'll need for the remote as well.  These are in  `Quadcopter-Remote/src/libraries/`.  From there, copy `quad_remote`, `RotaryEncoder` and `radio' into your `firmware/libraries/` directory:
 
```
 $ cp -r <path to>/Quadcopter-Remote/src/libraries/quad_remote firmware/libraries
 $ cp -r <path to>/Quadcopter-Remote/src/libraries/RotaryEncoder firmware/libraries
 $ cp -r <path to>/Quadcopter-Remote/src/libraries/radio firmware/libraries
 ```
 
or create symbolic links:

```
 $ ln -sf <path to>/Quadcopter-Remote/src/libraries/quad_remote firmware/libraries
 $ ln -sf <path to>/Quadcopter-Remote/src/libraries/RotaryEncoder firmware/libraries
 $ ln -sf <path to>/Quadcopter-Remote/src/libraries/radio firmware/libraries
 ```

Here's the command sequence on my machine: 

```
ln -sf ../../QuadClass-Remote/firmware/libraries/Remote ./firmware/libraries/
ln -sf ../../QuadClass-Remote/firmware/libraries/RotaryEncoder ./firmware/libraries/
ln -sf ../../QuadClass-Remote/firmware/libraries/Radio ./firmware/libraries/
(cd ./firmware/libraries/; git clone git@github.com:NVSL/QuadClass-AHRS.git)
(cd ./firmware/libraries/; git clone git@github.com:NVSL/QuadClass-LSM9DS1.git)
(cd ./firmware/libraries/; git clone git@github.com:NVSL/QuadClass-Sensor.git)
(cd ./firmware/libraries/; git clone git@github.com:sparkfun/SparkFun_SerLCD_Arduino_Library.git)
(cd ./firmware/hardware/; git clone git@github.com:NVSL/QuadClass-Atmega128RFA-Arduino-Addon.git)
```

When you're done, the top few levels of your repo should look like this:

```
./firmware
./firmware/hardware
./firmware/hardware/QuadClass-Atmega128RFA-Arduino-Addon
./firmware/RFEcho
./firmware/RFEcho/RFEcho.ino
./firmware/RFChat
./firmware/RFChat/RFChat.ino
./firmware/libraries
./firmware/libraries/Radio
./firmware/libraries/RotaryEncoder
./firmware/libraries/QuadClass-Sensor
./firmware/libraries/QuadClass-AHRS
./firmware/libraries/QuadClass-LSM9DS1
./firmware/libraries/Remote
./firmware/RFCount
./firmware/RFCount/RFCount.ino
./hardware
```
 
Restart Arduino and the bottom of your `Sketch->Include Library`  menu should look something like this:

![Libraries installed](images/installed_libraries.png)

#### Create Your Firmware Source Files

Create sketches for your quad ard remote control firmware.  

* `firmware/quad_firmware/quad_firmware.ino` will hold the firmware (i.e., flight control software) for your quadcopter
* `firmware/remote_firmware/remote_firmware.ino` will hold the code for your remote control. 

### Run a Test Program 

* Open up `File->Examples->01.Basics->Blink`. 
* Compile and download to the remote.
* One of the LEDs on the board will start blinking.
* Open up `File->Examples->01.Basics->AnalogReadSerial`, and run it. 
* Then, open `Tools->Serial Monitor`. You should find it printing a number at you.  Moving the right stick on your remote should cause it to change.

### Reading from the IMU

Load, compile, and run `Open->Examples->QuadClass Adafruit LSM9DS1 Library->lsm9ds1`.  Open the serial monitor (You may need to adjust the BAUD rate to 115200), and you should see something like this:

![IMU Output](images/IMU_Output.png)

Shows the raw sensor readings from your IMU.  As you move the FCB, they should respond accordingly.  See if you can find gravity.  It's 9.8 m/s^2.

### Driving the Motors

The motors on the FCB are attached to pins 8, 3, 4, and 5.

Add some code to `firmware/quad_firmware/quad_firmware.ino` to control the speed of the motors, and use the functions to run the motors at different speeds.  [analog_write()](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/) will be useful.

To avoid injury take the following precautions

   1. Be careful of the propellers on the motors. They can hurt you.
   2. Before you start, make sure the airframe is in the “locked” position.

## Using the Radio

The microcontroller on the remote and the FCB (and eventually your
quadcopter) use has a built-in radio.  We will use it to send commands
from the remote to the FCB and to return telemetry.

First, find out your groups assigned channel.  You'll need to edit the
examples below to pass a channel number to `rfBegin()`.  Eaglint will
assign you a channel number.  It's at the top of your list of group
design checks.

To test the wireless, open `firmware/RFCount/RFEcho.ino` and run it on
your FCB.

Then run `firmware/RFChat/RFChat.ino` on your remote.  Open the serial
monitor and type some text into the field at the top, and hit return.
It'll bounce the data off the FCB and print out the result.  You might
get some garbage too, that's fine.

Look at the `RFChat` code to understand how it works: It checks if
data is available from the radio and writes it to the serial
port. Then, it reads data from the serial port and writes it to the
radio.  Note that it sends and recevies multi-byte packets.

## Sending Useful Data

Your next task is to think about how you will transmit data from your
remote to the quadcopter. A reasonable approach is to create a struct
that holds all the control values you want to send to the
teststand/quadcopter and transmit that struct, using `rfWrite()`. You
should include the gimbal values and the buttons.

There are some caveats:

First, you should include a “magic number” in your command struct so
you can make sure you are getting commands from your remote and not
some other random data or packets from another team (we may have more
teams than channels). If you want to be more careful, you can include
a checksum as well. For instance, the last entry in the struct could
hold the `XOR` of all the other words in the struct. If they don’t
match, it’s a packet from somewhere else.

Second, don’t spam the world with your radio traffic. Modify your
remote firmware to send the command packet between 10 and 20 times per
second.  The `millis()` functions (search for “arduino millis") will
help you here.

Third, your struct and the related function will be shared between
your quadcopter firmware and your remote firmware. The clever way to
do this is to create your own Arduino library that holds the struct
and related code. Otherwise, if you change it in one place, you’ll
have to remember to change it in another. This violates the [DRY
principle](https://en.wikipedia.org/wiki/Don%27t_repeat_yourself).

To test it, program the test stand board to receive the data from your
remote and print it out. Verify that the values change as you move the
gimbals, etc.

## Putting it All Together: Remote Controlled Motors and LEDs

Modify `firmware/quad_firmware/quad_firmware.ino` and
`firmware/remote_firmware/remote_firmware.ino` so you can arm your
FCB, calibrate your gimbals, and control your motors’ speed with the
remote.

### Calibrating Your Gimbals

The potentiameters in your gimbals are imperfect, so they need to be
calibrated.  As you move them around, you'll notice that the values
don't go from 0 to 1023 (the full range of the microcontrollers ADC).
My yaw control, for intsance, only goes from 57 to 906.  You'll need
the actual values for your gimbals so you can know, for instance,
where the neutral position for pitch, yaw, and roll are.  To collect
these values, you'll need a calibration mode.  The Arduino `map` functions is useful here.

A few nice things to have in a calibration mode:

1.  You don't have to do it every time your quadcopter restarts.
2.  You can't accidently enter it while your quadcopter is flying (since it requires you moving te sticks all over the place)

For #1, the Arduino EEPROM library is useful:
https://www.arduino.cc/en/Reference/EEPROM.  It let's you store data
across resets.

For #2, you should only be able to enter calibration mode while the
quadcopter is not armed (see below).  You will also need a way to
trigger calibration mode (e.g., pressing one of the buttons).

### Arming your FCB

The propellers are sharp enough and fast enough to hurt you.  To
prevent accidents, your firmware should require you to "arm" your
quadcopter before it will turn on the motors.

A typical arming sequence is to put the both gimbals in the lowest,
outermost position.  This position is useful in two critical ways: 1)
the pilot is unlikely to do it by accident and 2) it ensures that the
throttle is at 0.  Turn on the LED on the quadcopter when it is armed.

Your remote and the quadcopter need to always be in agreement about
whether the quadcopter is armed.  For instance, if your reset your
remote, the FCB should be disarmed.  If you reset the FCB it should
disarm and remain disarmed until the remote arms it again.

### Throttle Control

Once the FCB is armed, the throttle gimbal (the vertical axis of the
left stick) should control the speed of all four of your motors.
 
Make sure of the following:

1. When the stick is all the way down, the motor should turn off (I.e., writing 0 with `analogWrite()`).
2. When the stick is all the way up, you should be driving the motor at full power (i.e., writing 255 with `analogWrite()` )
3.  As you move the stick, motor power should vary smoothly with the sticks position.  (i.e., If the stick is at its midway paint, you should be writing 128).
4. If you push a little bit on the stick when it is all the way up or down, it shouldn’t behave strangely.  Achieving this will require you to deal with non-idealness of the gimbals.  The Arduino `constrain` function is useful here.

## Turn in Your Work

### Commit Your Code

1. Your remote firmware in `firmware/remote_firmware/remote_firmware.ino`.
2. Your quad firmware in `firmware/quad_firmware/quad_firmware.ino`.

Once you’ve committed everything, create a tag called “Lab03” Be sure to make it an “annotated” tag and push it to your repo (https://git-scm.com/book/en/v2/Git-Basics-Tagging). Verify that it is visible on github.

### Demo Your Code

1. Demo your remote controlled motors.

### Rubric

Possible points: 10

Check list (1 point each):

1.  No motor activity when disarmed.
2.  Motor control active when armed.
3.  Arming turns on FCB LED.
4.  FCB reset disarms.
5.  Remote reset disarms.
6.  Calibration works.
7.  Calibration values saved
8.  Calibration mode unavailable when armed.
9.  Pushing sticks past calibrated values doesn't result in strange behavior.
10.  Zero motor activity at 0 throttle.
11.  Throttle smoothly controls motor output across full gimbal range.

You will lose one point for each day late your solution is.