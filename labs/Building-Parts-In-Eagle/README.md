# Building Parts in Eagle

To be completed on your own.
Check the course schedule for due date(s).

## Skills to Learn

1. Learn to create more complex packages, devices, and schematic symbols in Eagle.
2. Learn to interpret device datasheets to ensure that the packages you design meet the requirements of the devices they are for.

## Equipment, Supplies, and Software You will Need

1. Eagle
2. The starter repo: for this lab: https://classroom.github.com/a/AOGppG5g. (Don’t clone it until the start of class, last minute changes are likely)

## Preliminaries

### Make Eagle Easier to Use

Set your grid to mm, you can follow the instructions [here](https://electronics.stackexchange.com/questions/197876/eagle-cad-choosing-mm-as-default). 

A sample eagle.scr is available in this repo under `Eagle/eagle.scr`  It will set the grids to the correct defaults in new schematics, boards, and libraries you create.

### Units of Measure

In a perfect world we would all use mm for everything when designing our boards. Unfortunately, this not always possible. Eagle uses mm internally, but for some reason it wants to use ‘mils’ for some parts of its UI and inches are the default in others. In addition, by convention, Eagle schematic symbols are built on a 0.1” grid. And some board houses specify tolerances in mils or inches.

This means you need to pay close attention to your units. Here’s a simple reference:

* 1 in = 25.4mm
* 1 mm = 0.0387... inches
* 1 mil = 0.001 inches

In eagle, the safe thing to do is write it out. If you type ‘1mm’ or ‘1in’ or ‘5mil’ into a length field in a dialog box, Eagle will do the "right" thing (namely convert it to whatever it wants to display and show that value).

## Building Parts

Create packages, symbols, and devices for the following electrical components.  You'll add these to `lbr/custom.lbr` in the lab repo.   That library contains some examples.  You will be able to use some packages for multiple parts.  Combine similar parts into a single Eagle device. Reuse the examples however you like.

| Description                    | Digikey part number  | Notes                                     |
|--------------------------------|----------------------|-------------------------------------------|
| 0805 0Ohm resistor	         | 311-0.0ARCT-ND       |                                           |
| Red Light emitting diode	     | 160-1178-1-ND        |  Orientation is key                       |
| N-Channel MOSFET               | SI2302CDS-T1-E3CT-ND |  Pay close attention to the pads          | 
| LSM9DS1TR 9-Axis IMU           | 497-14946-1-ND       |  Read the datasheet _and_ tech note       |

You can find information about the part by typing the Digikey part number into google.  There will be a link to the datasheet.

### Guidelines for Building Schematic Symbols

When you design symbols follow these guidelines:

1. Choose a sensible name for the symbol. “Resistor” is a good name for your resistor symbol, since it can be used across all kinds of resistors. “CPU” is a bad name for the symbol for our microcontroller, since the symbol will be very specific to this particular chip, so the symbol name should reflect that.
2. For polarized parts include markings that make the polarization clear.
3. Make certain that your pins are placed with 0.1” grid settings. Failure to do so will cause you no end of pain.
4. For an IC (on anything with simple, rectangular symbol) Almost all your pins should go on the sides. The only exceptions are power pins (which can go on top), and ground pins (which can go on the bottom). Generally, inputs should go on the left and outputs on the right (this is not always easy to follow, but try).
5. Use standard symbols for components like resistors, capacitors, etc. Here are some examples: https://goo.gl/enZ0v0. You can also just google for “resistor schematic symbol” etc.
6. For two terminal, polarized devices, draw the positive terminal on the left (so it matches the packages, see below).
7. For parts with many pins (e.g., the IMU and the microcontroller) arrange the pins on the schematic symbol thoughtfully. For instance, power and ground on the bottom or top, and logically related pins near one another. In general it is not a good idea to mimic the physical arrangement of pins on the physical device. I’ll reject designs that do this for the IMU.
8. Use sensible pin names that will you connect the symbol pins and package pins correctly. For example, ‘1’ and ‘2’ makes sense for a resistor symbol, but “C” and “A” makes more sense for a diode. For parts with many pins (like the IMU) use names from the datasheet. The goal is to make it as easy as possible to check that you have connected things properly.
9. Sizes the symbols sensibly. Discrete components (e.g., resistors and capacitors) should be small, so they don’t take up too much space. Complex parts should be bigger to make them easy to wire up.
10. Include text elements with “>NAME” and “>VALUE” in layers “Names” and “Values” respectively, to show details about the parts. Only include “>VALUE” if the symbol will be used in devices that need a value (see notes below).

### Guidelines for Building Packages

Each of your packages should contain the following elements:

1. Choose a meaningful name: e.g, “0805_RESISTOR” or “RED_LED”. Using the part number your are building for makes sense if there’s only one part that is that size, but for things like resistors, there are many parts that are the same size and you can reuse the package.
2. Draw a box in tDocu that matches the nominal dimensions of the part. For parts with leads that extend from the part’s package (e.g., the MOSFET), you can draw in the leads too, if you want. tDocu doesn’t show up on the board.
3. A text item that displays the reference designator for the part. It should be on layer `tName` and the magic string “>NAME” is replaced with the reference designator.
4. A text item that displays the value of the part. It should be on layer tValues. “>VALUE” is replaced with the value. This will show up in your assembly drawing to help ensure you install the right part.
5. Drawing elements on `tKeepout` showing the area in which other part are not allowed. This should include the physical extent of the device and other other areas that need to be kept clear.
6. The text for the package name should be in the “vector” font and of size at least 0.9mm with a “ratio” of 8. This is not the default for text in the package editor (if you figure how to make it the default, let me know).
7. The text for the reference designator should not overlap with each other or the silkscreen for the device.
8. The text for the reference designator should be aligned to 0.1mm grid.
9. You can optionally include text with “>VALUE” in the the “tValues” layer. Real-world designs don’t usually do this, but it makes hand assembly easier. The remote board has values on the board. If you include them, the same requirements apply to them regarding their size and alignment as applies to “>NAME”.
10. Add lines on `tPlace` that guide the orientation, placement, and alignment of the parts. There are many different styles to consider. Google for “Resistor silkscreen” etc. for inspiration. Follow these guidelines:
    1. For polarized components, draw with the positive terminal on the left.
    2. For polarized components, make the positive terminal the first terminal.
    3. For polarized components, clearly mark positive terminal with a dot or extra line.
    4. When it makes sense, use familiar symbols to represent polarity (e.g., for a diode, you could use an triangle pointed toward the cathode)
11. Make sure that the “>NAME” doesn’t overlap with the elements that show the orientation, placement, and alignment of the parts.
12. Make sure pads and SMDs are of uniform size, unless there’s an good reason not to.
13. Make sure pads and SMDs are aligned vertically and horizontally in rows and columns as makes sense for the package.
14. We may be soldering by hand, so you need to make sure the SMDs extend out from under the part. This especially important for the IMU. The SMDs should extend 0.5mm away from the edge of the package.
15. Eagle includes a package generator.  You are welcome to use it, but the packages it generates do not meet all of our requirements.  You'll need to edit them a bit.

### Guidelines for Building Devices
Devices connect packages to schematic symbols.

Follow these guidelines when creating devices:

1. The device should have a generic name, if it will have many variants. For instance, a “Resistor” or “Capacitor” device will have variants for different package sizes and values.
2. Put the symbol at the origin (in the left-hand pane of the device editing window)
3. Choose a sensible name for the device. The guidelines for symbols generally apply here as well.
4. When you create variants in the device, give them descriptive names. For instance, for 10Ohm, 0805 resistor, “-100R-0805” would be good name. Avoid having an unnamed variant unless there is really only ever going to be one variant (e.g., for the IMU).
5. Make sure to connect the symbol pins to package pins correctly. Check it, check it again, have your partner check it. This is a common source of hard-to-find bugs.
6. Set the “Value” radio button appropriately. Things like resistors and capacitors naturally have a value (i.e., a resistance or a capacitance), others, like the microcontroller, do not.
7. Set the prefix appropriately: “R” for resistor, “Q” for mosfets, “U” for ICs, “D” for diodes, etc. This is what Eagle will start the reference designator with (e.g., “R1”, “Q2”).

You should have one variant for each different physical device you might include in your design. For instance, if you have two 0805 resistors with different resistances, you should one variant for each of them. In this case, you should add attribute (see below) called “VALUE” that specifies the value (e.g., “10R” for 10 Ohms, “1nF” for 1 nanofarad).

You can attach metadata to each variant of your device using “attributes.” (Eagle provides the notion of “technologies” which are different sets of attributes for a device. You should always use the unnamed technology: “”) All your variants should have the following attributes.

* DIST – distributer (For us, this is always “Digikey”)
* DISTPN – Distributer part number. i.e., Digikey’s part number. This is different from the manufacturer’s part number.
* CREATOR – Your name, if you designed the part.

All these attributes should be “constant” which means you can’t change them on a per-part basis in the schematic.

DIST and DISTPN are especially critical, because when we go to order parts for your quadcopter, we will use this information to know what to order.

### Notes on Individual Parts

#### LEDs

* Include “LED” in the name of the device you create (so Eaglint can find them).
* The prefix for your LED device should be “D” for diode.
* Positive terminal on the left on both symbol and package.
* Name the cathode ‘C’ and the anode ‘A’ on both the symbol and the package.
* Make sure SMDs extend 0.5 mm beyond the end of the LED.
* Name the variant so it’s clear it’s a red LED (it is a red LED because it has the DISTPN that corresponds to a red LED)

#### MOSFET

* Include “FET” in the name of the device you create.
* The prefix for your MOSFET device should be “Q” (that’s the conventional prefix for transistors).
* Since we are using an NMOSFET (as opposed to a PMOSFET), current flows from the drain to source, so put the drain on top in the symbol.
* Name the source, drain, and gate, “S”, “D”, and “G”, respectively in both the symbol and the package.
* Read the section in the datasheet about SMD layout starting on page 6.
    * There are two aspects of SMD sizing you you must address in this package. The first is the size of the metal SMD. The second is the hole in the solder mask, called the “stop mask” because it stops the solder mask. Normally, SMDs come with appropriate ‘stop’ by default. You’ll need to remove the default stop and add yours by hand.
    * Create the SMDs according to the guidance in the datasheet.
    * Use the info tool to edit each SMD, and uncheck ‘stop’.
    * Draw in the stop by hand in layer ‘tstop’ with the rectangle tool. The geometry of these rectangles should correspond to the “recommended minimum pads” in the datasheet, except that they should be longer by 0.5mm or to make soldering easier.

#### Resistor

* Include “RES” in the name of the device your create.
* Make sure SMDs extend 0.5 mm beyond the end of the resistor.
* The prefix for your resistor device should be “R” for resistor.
* Name the variant so it’s clear it’s a 0 Ohm resistor. Something like “-0Ohm” would make sense.

#### IMU

The IMU has caused us signficant problems in the past.  Be careful with it.  You should read both the datasheet and the SMD tech note.

* Include “IMU” in the name of the device you create.
* Build the package for the IMU so it has the same orientation as the mechanical drawing in the datasheet.
* Check the orientation. Your view of the package in Eagle is looking “down” on the board.
* Draw your package so it is wider than it is tall.  Otherwise Eaglint will get confused.
* Make sure the SMDs should be 0.85mm wide.  They will extend slightly out from under the package.
* The prefix for your IMU device should be “U” (that’s the conventional prefix for ICs).
* Label the SMDs on the IMU using either the pin numbers or the names used in the datasheet. Some pads same replicated names. Use something like “VCC1”, “VCC2”, etc. to distinguish them.
* The symbol for the IMU should have one VCC pin, one VCCIO pin, and one GND pin. It should not have a RES pin. For instance, in the device for for the IMU, you should connect all of the VCC SMDs to the single VCC pin in the symbol.
* There should be no metal under the IMU.  To enforce this, you should do the following
    1.  Draw a rectangle in `trestrict` that fills in the space in under the package, but does not overlap any of the pins.
    2.  Draw a rectangle in `brestrict` that covers the entire package.
    3.  Draw a rectangle in `vrestrict` that covers the entire package.
* There should be no solder mask under the IMU.  To enforce this, draw a rectangle of `tStop` that covers the area under the packge.
* You need to draw lines of `trestrict` between the pads.  They should be the same length as the pads and not overlap them.
* Be sure to include a pin-1 indicator that will be visible when the IMU is installed.


## Turn in Your Work

### Commit the following:

1. Your `lbr/custom.lbr`
2. Submit it though Eaglint: http://eaglint.nvsl.io.

### Rubric
“Perfect” score: 10

Initial points: 12

You will lose one point for failed full design check or human review.