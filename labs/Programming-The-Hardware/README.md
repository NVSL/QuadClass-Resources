# Arduino, Wireless, and Quadcopter Hardware

This is big lab, but there shouldn’t be many surprises. You’re mostly getting parts and pieces together for future labs, but you do have to integrate everything into one app at the end, and integration is always harder than you think.  
There’s a lot to do. Get started!

## Pick your Team

You will work on this lab and all future labs in teams of two. You will need to create a team on Eaglint and via the github classroom interface. The name of your team in github classroom must match the team name you use in Eaglint, or Eaglint will refuse to check your work.

## Skills to Learn

1. Installing the Arduino GUI.
2. Programming your remote and the test stand board.
3. Communicating with the boards using an FTDI serial port.
4. Communicate wirelessly between the remote and the FCB.
5. Reading values from the controller gimbals.
6. Use the other features of the remote.
7. Driving a DC motor with PWM.

## Equipment, Supplies, and Software You Will Need

1. The starter repo for this lab: https://classroom.github.com/g/LqnP9DDz. **You should create you GitHub classroom team before you create your eaglint group, and you must use exactly the same name for the Eaglint group.**
2. test stand and remote control part kit.
3. Laser-cut parts for a test stand and airframe.
4. 1 micro USB cable.
5. 1 flight control board (FCB).
6. Two LiPo batteries.
7. 1 set of motors.
8. 1 set of matched propellers (2xCW, 2xCCW)

### Your Remote Control

You are responsible for the care of the remote:

1. If you break it, you'll need to pay replace the broken parts.
2. Be reasonably gentle with the gimbals (joysticks). They are of high quality, but are not indestructible.
3. Be careful to install the batteries in the correct orientation.  This mostly means attaching the battery leads to the screw terminals correctly (red is '+').

Unfortunately, you cannot keep the remote.  However, it is pretty easy to build you own.  Ask the professor, if you are interested.

### Your Flight Control Board and Test Stand

The flight control board (FCB) is a PCB very similar to the quadcopter
you will eventually build.  It mounts to the test stand and will
provide a platform for your initial quadcopter firmware development.
The flight control boards are provided for your use during the class.

## Preliminaries 

### Install Arduino

Install Arduino 1.8.5 or later.  This is the only version we will be supporting in class.

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

Here's the command sequence on my machine: 

```
(cd ./firmware/libraries/; git clone git@github.com:NVSL/QuadClass-AHRS.git)
(cd ./firmware/libraries/; git clone git@github.com:NVSL/QuadClass-LSM9DS1.git)
(cd ./firmware/libraries/; git clone git@github.com:NVSL/QuadClass-Sensor.git)
(cd ./firmware/libraries/; git clone git@github.com:sparkfun/SparkFun_SerLCD_Arduino_Library.git)
(cd ./firmware/hardware/;  git clone git@github.com:NVSL/QuadClass-Atmega128RFA-Arduino-Addon.git)
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
./firmware/libraries/SparkFun_SerLCD_Arduino_Library
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

#### Getting Updates For the Starter Repo

Occasionally, I find bugs in the starter repo and push updates to it.  To get them you need to 'fetch from upstream' using git.  The first time you do this you need to do:

```git remote add upstream git@github.com:UCSD-Quadcopter-Class/QuadClass-Quadcopter-Starter-sp19.git```

or (if you don't have public key set up on github):


```git remote add upstream https://github.com/UCSD-Quadcopter-Class/QuadClass-Quadcopter-Starter-sp19.git```

Then, each time I push a new update you should do this:

```
git fetch upstream
git merge remotes/upstream/master
git push
``` 

#### Create Your Firmware Source Files

Create sketches for your quad ard remote control firmware.  

* `firmware/quad_firmware/quad_firmware.ino` will hold the firmware (i.e., flight control software) for your quadcopter
* `firmware/remote_firmware/remote_firmware.ino` will hold the code for your remote control. 

### Arduino Troubleshooting

Programming Arduino microcontrollers can be a temperamental process. If you get an error while programming the board, there are many different things you can try to make it work (some of whi
h seem like black magic):

* Make sure you have the right board and programmer selected.
* Try a different USB port. Computer have internal USB hubs and some hubs don’t play well with Arduino.
* Try a USB 2.0 port. Sometimes programming doesn’t work over USB 3.0. If your computer has a USB 2.0 hub use it. If not, get a USB 2.0 hub and plug the Arduino into that.  On some machines
he blue USB ports are 3.0 and black ones are 2.0.
* Unplug everything, quit Arduino, plug everything back in, restart Arduino.
* Google the error. Chances are you are not alone.

In rare cases, you may need to install drivers for the FTDI programming board. Read the How to Install FTDI Drivers Tutorial https://learn.sparkfun.com/tutorials/how-to-install-ftdi-drivers
.

## Bringing Up the Remote

Your first task to "bring up" your remote.  This means verifying that all of it's components work and that you can successfully access them via software.

### Assembling the Remote 

To assemble the remote you will need the following:

* 8x 1-inch standoffs
* 4x 1/2-inch standoffs
* 4x 3/8-inch standoffs
* 8x 1-1/2-inch screws
* 4x 1-1/4-inch screws
* 12x nuts
* 4x small zip ties
* 1x PCB
* 1x LCD
* 1x battery cable
* 2x gimbals 
* 1x USB Micro cable

##### Steps

**All the Parts** 

![Remote Parts](images/remote-parts.jpg)

**Add Screws**

![Add Screws](images/add-screws.jpg)

**Add Standoffs**

![Add standoffs](images/add-standoffs.jpg)

**Add Gimbals and PCB**

The vertical axis of the left gimbal should not return to the center position automatically.  The other gimbal axes will. 

![Add gimbals](images/add-gimbals-pcb.jpg)

**Add Gimbal Nuts**

![Add gimbal nuts](images/add-gimbal-nuts.jpg)

**Plug in Gimbals**

![Plug in gimbals](images/plug-in-gimbals.jpg)

**Install Standoffs and LCD**

![Install standoffs and lcds](images/add-standoffs-and-lcd.jpg)

**Add LCD Nuts**

![Add LCD nuts](images/add-lcd-nuts.jpg)

**Attach Zip ties as 'feet'**

![Remote FTDI](images/remote-feet.jpg)

**Attach Battery and 2-pin jumper**

![Add battery](images/add-battery.jpg)


### Installing a Battery

The remote can be powered either via USB or via a LiPo battery.  It also has a builtin LiPo charger that will charge the battery when it's attached to USB.  You'll have two batteries.  Keep one charging on the remote and the other
hooked to the FCB.

### Run a Test Program On the Remote

The Remote has a builtin USB-to-serial converter that allows it to program the microcontroller on the remote.  It can also program the FCB via a cable.   Whether it will program the remote or the quadcopter target is controlled by the `quad/RC` switch at the top of the remote.

* Plug your USB cable into the the remote.
* Set the the RC/Quad switch to 'RC'
* Open up `File->Examples->01.Basics->Blink`. 
* Compile and download to the remote.
* One of the LEDs on the board will start blinking.
* Open up `File->Examples->01.Basics->AnalogReadSerial`, and run it. 
* Then, open `Tools->Serial Monitor`. You should find it printing a number at you.  Moving the left stick on your remote should cause it to change.

### Reading the Buttons

The `Radio` library provides access to the basic hardware features of the remote.  You get access to the library with `#include "quad_remote.h"` and calling `quad_remote_setup()` in your Arduino `setup()` function.

The library provides a call-back-based mechanism for detecting when the user presses the buttons.  Function pointers (e.g, `btn1_cb`) hold functions that will be called when a button (e.g., button 1) is pressed or released.  The callbacks you set need to run quickly (e.g., ideally, they should not print anything to the serial port). 
 
To see how it works open `Open->Examples->Remote->knob_and_buttons.ino`.  Run it,
pen the serial monitor, push some buttons, and see what happens.

There is also a simple 'is_pressed()' function that you can use to tell if a given button is currently pressed.  You should pass the `*_PIN` constant for the button you want to test.  The `*_PIN` macros are in `quad-remote.h`.

Read the code to understand how it works.

### Reading the Knob

There's a similar mechanism for the knob.  The library defines an object called `knob1`, and calls a callback (`knobs_update_cb`) when it's value might have changed (i.e., sometimes it'll be called even though the value remains the same).  This funtion needs to run very quickly (e.g., it should not write anything to te serial port), otherwise you might miss some movement of the knob.

You can access the current value of the knob with `knob1.getCurrentPos()`.  The knob can turn indefinitely in either direction and the number will grow and shrink accordingly.  You can also set the current knob value with `knob1->setCurrentPos()` (see `knob_pressed()` in the example).

Look at `Open->Examples->Remote->knob_and_buttons.ino` and the `libraries/RotaryEncoder/RotaryEncoder.h` for details.  Run the example and turn the knob.  The knob has a builtin button, too.  It works just like the other buttons.

### Writing to the LCD

The remote has a fancy LCD screen with an RGB LED backlight (it's this: https://www.sparkfun.com/products/14073).  

The `Remote` library sets up the lcd for you as an object called `lcd`.

THe `knobs_and_buttons.ino` example shows how to use it:  It displays the value of the knob and lets you move it's location around on the display.

Here are the basic commands.

* `lcd.clear()` clears the display
* `lcd.home()` move the cursor to the top left position.
* `lcd.print(char *)` write some text to the display.  It works with `int`, `float`, `char *`, etc.
* `lcd.setCursor(int c, int r)` Move the cursor to the `c` position of row `r`.

There's some other fancy stuff you can do, too, like scrolling, changing the contrast setting, and changing the backlight color.  Checkout the examples, but note that the examples all assume I2C connectivity, but the remote uses `SoftwareSerial`, so you'll have to adapt/copy from the examples rather than running them directly.    

### Reading the Gimbals

1. Write a function that reads values from the gimbals and use it to writes them to the serial port.
  * Check out [analog_read()](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/).
  * The [Arduino Serial monitor](https://www.arduino.cc/reference/en/language/functions/communication/serial/) will tell you how to get output to the serial port.
  * The function should go in your  `firmware/remote_firmware/remote_firmware.ino`, which will slowly grow into your remote’s firmware.
2. Does the value you read from the gimbals vary across the gimbals’ full range of motion?  If not, let us know.
3. Have your code scale the values you get from the gimbals so the full range of motion corresponds to the range 0-255. Arduino's `map()` and `constrain()` functions are useful here.

## Assemble your Test Stand

Parts:

* 1x FCB
* 1x Air frame
* 4x smallest nylon spacers
* 4x small wooden spacers
* 4x 1/2-inch (or 5/8th) screws
* 4x nuts
* 1 set of motors
* 2x small white zip ties
* 1x skewer
* 1x battery
* 2x test stand sides
* 1x test stand cross-brace
* 1x 6-pin FTDI-to-FTDI cable
* 1x 2-pin jumper
* 2x Blades (A)
* 2x Blades (B)

### Assemble the Frame

The test stand assembles without any tools, and should look like this when it's done:

![Test Stand](images/teststand.jpg)

1. The middle brace slides into the slots on the two end pieces.  You can use either the vertical or horizontal slot.
2. The wooden dowel goes through the holes
3. You can attach two small zip ties to the down to keep it from sliding too much.

It's easy to disassemble as well, although the corners are a bit sharp.

### Assemble the FCB and Airframe

![Air frame](images/airframe.jpg)

The FCB mounts to the wooden air frame as shown above by following the steps below:

1. Use four screws and nuts to attach the FCB to the airframe.  Include a 1/8" nylon space and a wooden spacer (not shown in this photo) to provide a gap between the two.  

![Air frame](images/fcb_to_airframe.jpg)

2. Use another two zip ties to attach the air frame to the dowel.  Make it as tight as you can. 

![Air frame](images/airframe-zip-ties.jpg)

3. Trim the tails of your zip ties.
4. The battery should tuck neatly between the dowel and the FCB.
5. The motors plug into the four recepticals on the FCB.  You need two read/blue and two black/white motors and matching colors need to diagonally opposite eachother (like in the picture above)
6. Wrap the wire around the arms once or twice and then insert the motor into its holder.  It is a tight fit.
7. Install the four propellers.  You need two clockwise (labeled "A" -- see below) and two counter-clockwise propellers (labeled 'B').  Matched propellers should be diagonally opposite eachother.  Color has no relationship to direction.  Check the motor direction before installing the propeller to make sure they blow down.

![Air frame](images/clockwise_motor.jpg)
![Air frame](images/counterclockwise_motor.jpg)

8. If you need to attach a battery cable, unscrew the two screws on the green terminal block and insert the lead on the battery cable.  Make sure you get the polarity right: red is positive:
![Air frame](images/battery_polarity.jpg)


## Bringing up the FCB

The FCB has three key hardware components you'll need to test:  The microcontroller, the accelerameter, and the motors.

### Run a Test Program on the FCB

The FCB can be programmed via the remote control's USB-to-serial converter.  The colorful 6-strand cable is for this purpose.  The remote control and the FCB both have `B` and `G` marking the correct location of the blue and green wires in the cable.

![FCB FTDI](images/fcb-ftdi.jpg)

![Remote FTDI](images/remote-ftdi.jpg)

The cable will also power the FCB's microcontroller and IMU even if no battery is attached.

* Set the 'RC/Quad' switch to 'Quad'.
* Run the `Blink` example.  The light should blink.
* Run the `AnalogReadSerial` example.  It will print at you, but the number won't change.

### Reading from the IMU

Load, compile, and run `Open->Examples->QuadClass Adafruit LSM9DS1 Library->lsm9ds1` on the FCB.  Open the serial monitor (You may need to adjust the BAUD rate to 115200), and you should see something like this:

![IMU Output](images/IMU_Output.png)

Shows the raw sensor readings from your IMU.  As you move the FCB, they should respond accordingly.  See if you can find gravity.  It's 9.8 m/s^2.

### Driving the Motors

The FCB's motors are driven directly by the battery, and the battery is connected to the board via 2-pin header.  Your FCB has a small 'jumper' that connects the pin.  
When it's not in use, you should leave the jumper disconnected.  Otherwise, the FCB will discharge your battery to a dangerously low level.

* Attach a changed battery to the FCB.
* Install the jumper.

The motors on the FCB are attached to pins 8, 3, 4, and 5.

Add some code to `firmware/quad_firmware/quad_firmware.ino` to control the speed of the motors, and use the functions to run the motors at different speeds.  [analog_write()](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/) will be useful.

To avoid injury take the following precautions

   1. Be careful of the propellers on the motors. They can hurt you.
   2. Before you start, make sure the airframe is in the “locked” position.

## Using the Radio

**Note:** In your `setup()` function, you should call `rfBegin()` after you
  call `quad_remote_setup()`, otherwise things won't work.

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
monitor (while it's connected to the remote) and type some text into the field at the top, and hit return.
It'll bounce the data off the FCB and print out the result.  You might
get some garbage too, don't worry about it.

Look at the `RFChat` code to understand how it works: It checks if
data is available from the radio and writes it to the serial
port. Then, it reads data from the serial port and writes it to the
radio.  Note that it sends and recevies multi-byte packets.

## Sending Useful Data

Your next task is to think about how you will transmit data from your
remote to the quadcopter.  A reasonable approach is to create a `struct`
that holds all the control values you want to send to the
teststand/quadcopter and transmit that struct, using `rfWrite()`. You
should include the gimbal values and the buttons.

There are some caveats:

First, you must tolerate the fact that the the radio channel you are using is a shared resource (it's the same RF range as WiFi).
This means you may pick up data that is not yours, so you must be able to tell which packets are meant for you and which aren't. 

One way to do this is to include a “magic number” in your command struct so
you can make sure you are getting commands from your remote and not
some other random data or packets from another team or noise. If you want to be more careful, you can include
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
principle](https://en.wikipedia.org/wiki/Don%27t_repeat_yourself).  Here's a tutorial on writing an Arduino library: https://www.arduino.cc/en/Hacking/libraryTutorial.  
Or you can look at the librarise in your repo for guidance (`firmware/libraries`).

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

Use the LCD to tell the user that they are in calibration mode.

### Arming your FCB

The propellers are sharp enough and fast enough to hurt you.  To
prevent accidents, your firmware should require you to "arm" your
quadcopter before it will turn on the motors.

Our arming sequence is to put the both gimbals in the lowest,
outermost position (left gimbal to lower-left, right gimbal to lower-right).  This position is useful in two critical ways: 1)
the pilot is unlikely to do it by accident and 2) it ensures that the
throttle is at 0 when the quadcopter is initially armed.  Turn on the LED on the quadcopter when it is armed.

Your remote and the quadcopter need to always be in agreement about
whether the quadcopter is armed.  For instance, if your reset your
remote, the FCB should be disarmed.  If you reset the FCB it should
disarm and remain disarmed until the remote arms it again.

### Throttle Control

Once the FCB is armed, the throttle gimbal (the vertical axis of the left
stick) should control the speed of all four of your motors.

Make sure of the following:

1. When the stick is all the way down, the motor should turn off (I.e., writing 0 with `analogWrite()`).
2. When the stick is all the way up, you should be driving the motor at full power (i.e., writing 255 with `analogWrite()` )
3. As you move the stick, motor power should vary smoothly with the sticks position.  (i.e., If the stick is at its midway paint, you should be writing 128).
4. If you push a little bit on the stick when it is all the way up or down, it shouldn’t behave strangely.  Achieving this will require you to deal with non-idealness of the gimbals.  The Arduino `constrain` function is useful here.

## Turn in Your Work

### Commit Your Code

1. Your remote firmware in `firmware/remote_firmware/remote_firmware.ino`.
2. Your quad firmware in `firmware/quad_firmware/quad_firmware.ino`.
3. Any other code you created (e.g., a library with your radio packet format).

Once you’ve committed everything, create a tag called “programming-the-hardware” Be sure to make it an “annotated” tag and push it to your repo (https://git-scm.com/book/en/v2/Git-Basics-Tagging). Verify that it is visible on github.

### Demo Your Code

1. Demo your remote controlled motors.
2. Complete the reflection for this lab: https://docs.google.com/forms/d/e/1FAIpQLScKSJucU3BTdXCpcaoRSXui36gL--QQvO2Y9j9LpOaGY0qj-w/viewform

### Rubric

Possible points: 10

Check list (-1 point for each missing item):

1.  No motor activity when disarmed.
2.  Motor control active when armed.
3.  Arming turns on FCB LED.
4.  FCB reset disarms.
5.  Remote reset disarms.
6.  Calibration works.
7.  Calibration values saved.
8.  Calibration mode unavailable when armed.
9.  Calibration feedback on LCD.
10.  Pushing sticks past calibrated values doesn't result in strange behavior.
11.  Zero motor activity at 0 throttle.
12.  Throttle smoothly controls motor output across full gimbal range.

You will lose one point for each day late your solution is. 
