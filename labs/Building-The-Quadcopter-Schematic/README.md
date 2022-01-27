# Assembling The Quadcopter Schematic

To be completed in pairs.

Check course schedule for the due dates. 

## Skills to Learn

1. Design a schematic to match a written specification.
2. Integrate portions of a reference design into your schematic.
3. Read and understand key portions of part datasheets.

## Equipment, Supplies, and Software You Will Need

1. Create a team in eaglint.  You _must_ do this before clicking the starter link below. <!-- Covid ONly -->
1. The starter repo for this lab: https://classroom.github.com/a/XtjNtfPa. <!-- Covid ONLY --> <!-- Next time reveal this link in eaglint after they have formed the group, so they know what name to use -->
<!-- 1. The repo you started in "Programming the Hardware Lab" -->
2. The `custom.lbr` library you built in previous lab, OR your cloud save for the custom library. From here on out, maintain copies of your libraries on the cloud.
3. Read through the [Fusion Tricks Page](../../Fusion-Tricks.md) and skim the [Autodesk docs](https://help.autodesk.com/view/fusion360/ENU/?guid=ECD-SCHEMATIC) that go over the design tools you will use this lab. 

## Preliminaries

### Setting up Fusion360

The repo for this lab will evolve to hold all the hardware and software for your quadcopter for the remainder of the quarter.

Now would be a good time to start utilizing Fusion Teams. To get started, decide between you and your partner on whose `custom` library should be used. That person should locate the Team online manager in the Data panel on the left:

![](images/team_1.png)

This will open up a web browser to manage your team. You can edit the name, invite your partner using their email, and have shared access to a cloud version of your library! Rename it as `custom_<name>` so that the versions from both team members can co-exist. If you run into issues with one partner's library, you can always import your other library into Fusion360, just be sure to maintain them using the cloud! You should not reference local versions of `.lbr` files, and you should only export them when you are ready to submit.

To clean up local copies of previously-used `.lbr` files, and to remove unnecessary third-party libraries, you can remove them using the library manager (make sure to keep your team's library in use):

![](images/library_1.png)

Feel free to remove all libraries except for your `custom` team library from last lab.

### Make Fusion360 Easier to Use

By default, Fusion360 comes configured with a bunch of libraries that can make it hard to find the libraries we are using for this class. This is controlled by the directories Fusion360 is setup to look in for library and other files. You can change the directories by selecting `User->Preferences` (upper-right corner) and then selecting `General->Electronics->Directory`.

To keep Fusion happy and make it easier to access and update libraries in the cloud, remove all the local folders Fusion is configured to look in for libraries. For Design rules and CAM files, I suggest the following settings:

* Design Rules: `<path to>/QuadClass-Resources/Eagle/DRU`
* CAM Jobs: `<path to>/QuadClass-Resources/Eagle/CAM`

## Assembling the Schematic

You’ll build quadcopter in the cloud starting from a new Fusion360 electronics design called `quadcopter`. When creating this design, make sure to save it to the right team. 

In this lab, you will create a schematic associated with this design, to be exported to the folder `hardware/quadcopter.sch`. Feel free to review [Lab 1](https://github.com/NVSL/QuadClass-Resources/tree/master/labs/Introduction-To-Eagle#exporting-files) for a refresher on exporting. You'll assemble the design by studying reference designs and the datasheets for the components you will use.

We will be sharing a library with you via the cloud called `quadparts_prebuilt`. You will be reusing your `custom` library from last lab, and in this lab you will also create a new library called `LEDs`. These should be the only 3 libraries you use to assemble your schematic,  Fusion360 comes with a bunch of built in libraries but they are off limits.

### General Schematic Style Guidelines

Here are the course style guidelines for schematics. Your schematics must adhere to these guidelines.  If you don't, Eaglint will give warnings and we won’t accept the design.

1. All visible net and component names must not have “\$” in them. When Fusion360 automatically generates names for nets and components it includes “$”. This is fine if the name is not visible (e.g., on an anonymous wire between two components), but if you it shows up on your schematic, you should give it a nice name like `CTRL` or `SCL`.
2. By convention power supply symbols point up, and ground symbols point down.  Neither should ever point to the side.
3. Nets should not cross each other unless they are electrically connected.
4. Nets should only be drawn at right angles.
5. Fusion360 embeds libraries in the `.sch` and `.brd` files. Make sure that you are keeping libraries up-to-date with  `Library->Update...` or `Library->Update All`. We won’t accept designs with inconsistent libraries.
6. Include a frame around our schematic.  Use device `FRAME_B_L`.
7. Use lines in `Info` layer to divide the frame into logically related regions (e.g., the IMU, the power supply, and the microcontroller). See the BBB schematic below for an example. Drawn nets shouldn’t cross these boundaries.
8. Use drawn nets connect components that are closely related (e.g., between the caps and the microcontroller in the BBB schematic)
9. Use named nets to connect separate “sub units” of your schematic. For instance, use drawn nets to connect all the capacitors to your IMU, but use named nets to connect your IMU to the microcontroller.
10. You should not use any libraries other than `quadparts_prebuilt`, your `custom_*`, and your `LEDs` libraries.
11. Schematic symbols and wires should all be aligned to 0.05in grid (or, if you like, a 0.1in grid).
12. Labels for nets (created using the 'label' tool) should need to placed on the net they label.  This means the label's location (which is marked with a gray '+') needs to be on top of a corner or end of the net.  This guards against "drifting labels" that seem to be attached to another net.

### Selecting Parts

The `quadparts_prebuilt` library has lots of parts in it, many of which you won't use.  I've provided specific guidance about which options to select below.  For resistors and capacitors, you need to use 0805 parts not the smaller and harder-to-place 0603 parts.  If the resistor you need is not available in 0805, you'll need to create it.

### The Microcontroller

Here's the schematic for a board called the Basic Breakout Board (BBB).  It uses the same microcontroller as your quadocpter, but it does not include the voltage regulator.  It's the reference design for your microcontroller and the radio.  The design also includes the 1x6-pin programming header you can see on the bottom of the FCB.  YOu don't need to include that header in your design. 

Why did I give a picture of what you need to build?  Because reference designs are a very common practice in real PCB designs.  The most reliable way to convey design requirements is to provide a working design.  Why reinvent the wheel?

![Microcontroller schematic](images/microcontroller.png)

You should use the schematic as a guide for constructing the microcontroller portion of your schematic.  Build it from parts from `quadparts_prebuilt` libbrary:

1.  Use one of the `ANT_PCB...` variants for the antenna.  There's a left and right-handed version.  Depending on your ultimate board design, you might want one or the other.
2. `B1` is a 'balun'.  Pay attention to the pin numbers.
3. Use the `0.45x0.45` button.
4. Replace one of the green LEDs with your red LED.
5. You can use either variant for the `AVR_SPI...` header.  The surfacemount one takes up more space (see it on your remote, under the LCD).  The throughole one is more compact.
6. You won't need the FTDI portion of the design.
6. Do not connect the power pin on the ISP programmer/Bootloader header.

You might notice that some of the symbols for the parts seem backwards.  This is because they are 'mirrored'.  There's a mirror tool or your can mirror parts by editing their properties with the `info` tool.

There are some changes you will need to make to this schematic based on what's required by the other components.  This is just a starting point for your circuit.

If you have questions about the parts attached directly to the microcontroller (including the radio), the first place to turn is the microcontroller datasheet.

### Programming Header

Your quad will use a 4-pin programming header to load code into the MCU.  You won't need the FTDI portion of the reference design.  It's a little fancy since it allows you to insert the cable from either top of the board _or_ the bottom.  To this end, use the `-FEMALE-SMD-BOTTOM-ENTRY` part from `quadparts_prebuilt`.  The four signals must appear in this order:

1.  Serial TX
2.  Serial RX
3.  GND
4.  Reset

These are a subset of thesignals that connect to the FTDI header in the microcontroller reference design.  You don't need the FTDI header.  Note that you do need the 0.1uF capacitor between the reset line and the reset pin on the programming header.


### The IMU

The IMU datasheet contains all the information you will need to use connect the IMU to the microcontroller. A few things to keep in mind:

1. The IMU datasheet is not the best.  If something doesn't make sense search the pdf.
2. There are actually two logical devices in this package: the accelerometer/gyroscope (referred to as 'A/G' in the datasheet ) and the magnetometer ('M').
3. Both devices will operate in I2C mode only and connect to microcontroller via I2C, so you can ignore the stuff in the data sheet that refers to SPI.
4. You must follow all the recommendations regarding external capacitors attached the IMU.
5. You will need to take care to configure the IMU's I2C addresses. It has two: One for the gyroscope and accelerometer and another for the magnetometer. The address for the gyro and accelerometer should be set to `1101011`. For the magnetometer it should be `0011110`.  You should read the datasheet to learn how to do this.  Note that there is an inconsistency between Table 2 and Tables 19 and 20.  Tables 18 and 19 are correct.
6. Power supply voltage and IO voltage will be 2.5V in our design, so connect them to `2V5`.
7. We aren't using the interrupt features, so you can leave `INT_M`, `INT2_A/G`, `INT1_A/G`, and `DRDY_M` disconnected.
8. `DEN_A/G` should be connected to `2V5`.

Most of the information you will need is Section 5 of the datasheet. 

A thing to know about datasheets: They almost always (although, frustratingly, not always) tell you everything you need to know.  They don't, however, make it easy.  You need to read carefully and thoroughly.  You can't skim the datasheet and expect to know the details of how to connect each of the pins to configure the IMU properly.  You actually need to read through the tables and the text, there are specific answers to most questions you might have in there.  Most facts appear exactly once in the datasheet -- it will be written in text or a table, but not both.

### The I2C Bus

Your MCU will communicate with the IMU via I2C.  This means you must connect the IMU to the MCU via the `SDA` and `SCL` lines.  You should "pull up" these lines to `2V5` by connecting them to `2V5` using 10kOhm resistors.

### The Motor Driver 

Here's a picture of the motor driver circuit:

![Motor Driver](images/motor_driver.png)

Build four copies to drive the four motors you'll need.  All the parts you need are in `quadparts_prebuilt` or your `custom` libraries.

1. Use the `-SMD-SOD123` diode in the library.
2. Use the `-MOLEX-SMD` variant of the `MOTOR_PADS_GND` device of the motor connector.
3. Use your MOSFET, of course.

The ground pin on the motor pads is not actually connected to the motor.  It just goes to the metal "feet" that hold the connector down.  You can see them on your FCB.

You'll need to connect the PWM control lines to suitable pins on the microcontroller. The suitable pins are marked with "~" on microcontroller's schematic symbol.

You need to include one 47uF decoupling capacitor between `VBAT` and `BAT_GND` (just one; not one per motor).  It's to help absorb switching noise from the motors.  Note that 47uF capacitor in the library is polarized.  In the schematic the curved "plate" on the symbol should be connected to ground.

### The Power Supply

The quadcopter draws power from from a LiPo battery that nominally provides between 3.7 and 4.2V. This voltage is too high for the IMU and the microcontroller.  Also, the motors (which we will power directly from the battery) will create all kinds of noise on both the battery supply and ground rails.  To solve both of these problems, we will use a low-dropout (LDO) voltage regulator to provide a stable 2.5V power supply to the IMU and the microcontroller.

As a result, your quadcopter will have two power rails: An unregulated power rail (called `VBAT`) that provides power to the motors and input of the voltage regulator and is driven directly by the battery, and a regulated supply driven by the voltage regulator (called `2V5`).

The power supply for quadcopter needs to contain the following parts:

1. The battery. This is the `BATTERY` device in `quadparts_prebuilt`.  You need to use the `-SMD-TH` variant.
3. A LP3985-series 2.5V regulator (see device `TPS73633-DBVT`.  Don't use th 3.3V or 3V versions).

Check the votage regulator datasheet (in `Datasheets`) for guidance about what kind of capacitors to connect to the regulator and how.  Wire the enable line to `VBAT` and don't connect anything to `NC/FB`.

You will also incorporate a power switch for the quadcopter.  The switch will connect the `EN` pin of the voltage regulator to `VBAT` when it's turned 'on' and connect `EN` to `GND` when its turned 'off''.  Use the `-SMD-EDGE` variant of `POWER-SWITCH-MFS201N-9-Z` for the switch.

You'll note that the output of the voltage regulator has decoupling capacitors on.  This keeps the voltage regulator stable and filters out noise on the output. Experience shows that quickly turning on the motors can causes the output of voltage regulator to drop enough to reboot the MCU.  Add an additional 47uF decoupling cap (the same one we use for motors) to the output of the voltage regulator between `2V5` and `GND` to prevent this.  Note that the 47uF capacitor is polarized.  The flat plate should connect to the positive voltage, and the curved plate to ground.

To the extent possible, we need to isolate the the IMU and the microcontroller from the noise that the motors will create on the power supply lines.  The motors will cause noise on both their power supply ( `VBAT` ) and ground return lines, so we will provide them with separate power and ground lines.  For the power line, this is easy: Just connect the power supply for the motor drivers directly to the battery's positive terminal.

For the ground line, it is more challenging, since all the devices on the quadcopter must share a common ground reference. The best we can do is to structure our schematic so that we can exercise tight control over how the ground line is laid out on our PCB.  To do this, create a separate ground net that connects the ground terminals of motor controllers to each other and the negative terminal of the battery (call it `BAT_GND` and use the `BAT_GND` device in the `quadparts_prebuilt` ).  Then connect the digital ground (i.e., the ground that connects to other components, aka `GND` ) to the battery ground using a schematic component called a "net bridge" (see below). We will see in the next lab how we can use this structure to isolate the digital components. (This is a very important step, and we added it to fix problems that occurred in all but one of the quadcopters we built in this class the first year it was offered). 

A "net bridge" is a PCB part whose only purpose is to electrically connect two nets in a schematic while keeping the nets separate in schematic (i.e., the two nets keep their own names). To create a net bridge, create a device with a footprint that consists of two SMDs that touch one another and a sensible schematic symbol for what is, in essence, a wire.  Put it in your `custom` library.  The SMDs can be very small (e.g. 0.5mmx0.5mm). Remove the `tStop` and `tCream` on the pads, since we won't be soldering anything to them.  You don't need `tKeepout` anything in `tPlace` for the net bridge.  If eaglint complains, just explain that it's not necessary since it's the net bridge.

Use bridge to connect `BAT_GND` and `GND`.

#### Basic Principle: Decoupling

Your quadcopter is full of transistors (small ones in your microcontroller and big ones in your motor drivers), and as they switch they cause noise on the power and ground planes. Noise on the power line can cause digital circuits to stop working (because 1’s start looking like 0’s) and noise on GND can cause all kinds problems because all voltages are measured relative to GND.

The minimize this noise, we want to increase the capacitance of the power and ground planes. One way to think of capacitance is as a resistance to changes in voltage, so adding more will reduce noise (which is an unwanted change in voltage).  Small capacitors can filter out high-frequency noise, while larger capacitors filter out lower-frequency noise.

There are two ways to add capacitance.  The first is to add capacitors.  The IMU and the microcontroller both describe the number and kind of decoupling capacitors you should incorporate and they tell you to place them as close as possible to the power and ground pins on the device.  This is because, to be most effective, the extra capacitance we add needs to be as close to the source of the noise as possible (to minimize resistance and inductance between the cap and the device).

The second way to add capacitance is to build a capacitor into the board. A capacitor is just two layers of metal separated by an insulator.  We can easily construct this in a PCB by laying down metal in two layers on top of eachother, and connecting one to power and one to ground. The result is a very small capacitor but one that we can put nearly everywhere on the PCB (so it will be a close as physically possible to the devices).  In our design this capacitance is not critical, but in higher-speed design, it is critical to filtering out the higher-frequency switching noise.

### Breakout Headers

You will face a couple challenges in bringing up your board and it's good to plan for them now.  Do this by adding two debugging headers to your design.  "Headers" are exposed connections to signals on your board.  You can attach pins or sockets to them as needed to help in debugging.

#### Signal Breakouts

When your quadcopter comes back from manufacturing and you assemble it, some debugging may be necessary and that may include the need to measure what's going on in different parts of the circuit. To make this easier, I suggest including a debugging header in your design.

A debugging header is a set of pins that connects key signals to pins that you can easily probe during debugging. I suggest including the following signals:

* `GND`
* `BAT_GND`
* `VBAT`
* `2V5`
* The control lines to the four motors
* `SDA`
* `SCL`

There's a 10-pin header in the library you can use for this.  You can also break up the debug header into smaller headers. For instance, you could put a 3 pin header next to each motor with `VBAT`, `BAT_GND`, and the control line. It's always a good idea to include a ground on each debug header.

Debugging headers can be a little dangerous to use, because it can be easy to accidentally create a short circuit between two of the pins when you are debugging (e.g., by touch both pins with a probe).  This is especially dangerous if you connect a power net and a ground net.  To avoid this, intermingle the PWM, SDA, and SCL lines with the power and ground lines, so that no power pin is next to ground pin.

#### IMU Rescue Header

Soldering the IMU is hard enough that it causes a fair number of
quadcopters to fail.  To guard against this, add a header that will
allow you to connect this breakout board
(https://www.adafruit.com/product/3387) to your quadcopter.  You need
four pins: `2V5`,  `SCL`, `GND`, and `SDA` (not necessarily in that order.  Look at the board it must connect to.), which are conveniently
located together on the breakout board.  Use the 4-pin female header
in `quadparts_prebuilt`.

If you feel like being efficient, you can leave `SDA` and `SCL` off the signal breakout header, since they are on the rescue header.

### Some LEDs

You should also add some LEDs to your design. There are several reasons to add LEDs to your design:

1. It'll make it easy to tell which end of your quadcopter is the front.
2. They look cool.
3. They can provide information about what's going on in your flight control software.

There are several options for powering and/or controlling LEDs:

1. You can connect them directly to battery power and battery ground. In this case, you can't turn them off, but they can be very bright.
2. You can connect them to pins on the micro controller.  If you use a digital pin, you can turn them on and off.  If you use a PWM pin, you can control their brightness.  In either case, you must size the resistor properly to limit the current through the LED to 8mA (the limit on the per-pin current on your microcontroller).
3. You connect them to battery power and turn them on and off using a transistor connected to a microcontroller pin.  Depending on the pin you use, you can turn them on and off or vary their brightness. The transistor we use in the motor controller should work fine.  If you do this, you can drive multiple LEDs with the same transistor and pin.

If you drive LEDs with a MOSFET, you should include a 10kOhm pull-down resistor to `GND` on the gate of the MOSFET.

Regardless of which approach you take, you will need to pick out your LED.  To do this, go to http://digikey.com.  And enter LED into the search field.  You'll see a bunch of results.  Likely candidates for smaller LEDs are to be found under "LED Indication - Discrete," while brighter LEDs can be found under "LED Lighting - White", "LED Lighting - Color".

You'll note there are a dizzying array of options (at this moment there are over 20,000 different indicator LEDs available). Digikey presents you with a decent searching interface. Go exploring! Things to keep in mind:

1. Any LED you choose needs to be available in small quantities (the "minimum quantity" column should say "1").
2. The need to be at least 0805 (1.25mm x 2mm).
3. They need to be reasonably cheap: no more than $1 per LED.
5. If you are going to drive the LEDs directly with a microcontroller pin, you must limit current to 8mA and you should make sure that the LED will actually light up with 8mA (many bright LEDs will not).
6. They need to be compatible with the power supply you are going to use: 3.7-4.2V if you use the battery. 2.5V if you are going to drive them from the microcontroller.
7. Their current draw needs to be within the limits of how you are powering them.
	1. The microcontroller limits how much current each pin will supply.
	2. The microcontroller consumes some current, as does the IMU (check the datasheets).
	3. The voltage regulator has limits on how much current it can provide.
	4. Make sure that voltage regulator can handle all your LEDs in addition to the microcontroller and the IMU.
	5. If you are powering them with VBAT, limit total current draw for all your LEDs to 500mA.
8. The current draw depends on forward voltage. The LED datasheets will contain some graphs that relate voltage to current and current to brightness.  Pay attention to them to make sure that a) you aren't drawing too much current and b) your LEDs will light up.
9. There are many different parameters to consider: Color, brightness, viewing angle, etc. You'll need to go learn about these by reading the datasheets, etc.
10. You will probably want surface mount parts, but you can also use through-hole if you want.
11. Digikey lists the typical forward voltage on the web page. The LED will work with larger or smaller voltages (up to a point. See the "absolute maximums" section of the datasheet for limits).
12. If the forward voltage of the LED is much lower than the supply voltage, you'll need a large resistor to limit the current. Alternately, you could put two (or more) LEDs in series. The total voltage drop across the LED(s) and resistor needs to be greater than or equal to the supply voltage.
13. You can use RGB LEDs, too. Checkout the datasheets for details.

You'll need to build the library entries for the LED you want to use and then integrate them into your schematic.  You'll also need to include a current-limiting resistor.  You'll need to use Ohm's law to calculate the correct resistor value (here's a tutorial: http://www.ohmslawcalculator.com/led-resistor-calculator).  You will also need to be sure that resistor can handle the amount of power it will need to dissipate (see the datasheet). If our libraries doesn't include an appropriate resistor, you'll need to add one from the same family of resistors we are already using (check the datasheet for the resistors in `quadparts_prebuilt`).  Make sure it's available in small quantities on Digikey.  Put the new resistors in `custom`.

One thing to keep in mind is that most LEDs are extremely bright when driven at full current. Indicator LEDs can be driven very gently and still be visible.  LEDs added for visual effect can be driven harder, but they can easily become so bright that you can't even look at your quadcopter without being blinded.  For this reason, any LEDs that you want to be bright need to be attached to PWM pins, so you can moderate their brightness.

Once you have picked your LEDs, document your LED design using text in the `Info` layer in your schematic.  For each type of LED, you should note its forward voltage, the resistance of the current limiting resistor,
and the current you expect to flow through the LED. 

Feel free to get creative with the LEDs!  Smilely faces.  Simulated space ship engines.  Aircaft "running lights".  Dance party.  Ground effects.

Put the LEDs devices/footprints you create in a new cloud library called `LEDs`. Reuse the LED symbol from `quadparts_prebulit` or your `custom` libraries. 

The footprints/devices you build need to meet all the standards described in `Building Parts in Fusion360 Lab`.

Add an attribute called `CUSTOM` to the variants you create.  It should be constant but without a value.  This will ensure they get ordered.

### Eaglint 

Your design needs to pass http://eaglint.nvsl.io, so commit your design, submit it, and fix the problems it finds.  Remember, each time you run a full check with the tool it lowers your grade on the lab, so you need to check your design carefully before submitting.

### Things to remember

1. Remember to sync your libraries with your schematic: `Library->Update All`.

### Things to Submit

Include these in your github repo:

1. Your `hardware/quadcopter.sch`.
2. Your `hardware/lbr/LED.lbr`.
3. Your `hardware/lbr/custom.lbr` (maybe renamed to `custom_<name>.lbr` and maybe two of them)
5. Datasheets for your LEDs in `hardware/datasheets/`.

Feel free to consult [Lab 1](https://github.com/NVSL/QuadClass-Resources/tree/master/labs/Introduction-To-Eagle#exporting-files) for export guidelines.

Submit it to Eaglint: http://eaglint.nvsl.io.

For this part of the lab, human review will succeed instantly, if you have no errors or warnings.

Once it passes, create a tag called "initial-schematic" Be sure to make it an "annotated" tag and push it to your repo (https://git-scm.com/book/en/v2/Git-Basics-Tagging). Verify that it is visible on github.

## Turn in Your Work

"Perfect" score: 10

Initial points: 12

Quick checks are free.  Full checks cost 0.5 points.  Submitting for human review costs 0.5 points.  Each day late costs 1 point.
