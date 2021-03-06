# Part 1: Creating the Schematic in Eagle

This tutorial will take you through the steps of creating a schematic, creating a board, creating new devices, and preparing the board for manufacturing. It's broken into four parts.

We are going to design a PCB to with a light controlled by a button.

The course style guidelines for schematics are in the "General Schematic Style Guidelines" section of https://github.com/NVSL/QuadClass-Resources/blob/master/labs/Building-The-Quadcopter-Schematic/README.md.  Read and follow them.  Eaglint will complain if you don't.

You will need the `Lab01.lbr` file available in the lab starter repo.

## Making the Schematic

Next, we will create the schematic for our circuit. This video walks through the process, and detailed instructions are below.

Open up Eagle, and select File->New->Schematic. It will open up the schematic editor window:

![](images/schematic1_new.png)

We need to load the Eagle Library that describes the components we are going to use. From your eagle-intro repository move the Lab01.lbr file (located in /lbr) to the Eagle/libraries/.. folder on your computer (check Documents folder ?). Back in the schematic window, select Library->Open Library…, navigate to `Eagle/lbr/Lab01.lbr` and select it.


## Adding the Parts

Now you are ready to build your schematic. Start by selecting the “Add” tool from the tool palette at left:

![](images/schematic2_new.png)

This will open up the library browser:

![](images/schematic3_new.png)

Click on the triangle next to “Lab01” to expand it. You’ll see four “devices” inside it. Go read [this page](http://goo.gl/HJtIzp) of the [Adafruit Eagle Parts Tutorial](http://goo.gl/GcM04V) to understand the difference between a schematic “symbol”, a “package”, and a “device.”

A schematic should have a “frame” around it to contain the size. The frame also include space for documentation about the version and author. To add the frame select “FRAME_B_L” and click “OK”. You can then place your frame

![](images/schematic4_new.png)

Select “2.1MMJACKTHM” and press “OK.” You’ll return to the schematic editor with the schematic symbol for the power jack attached to your mouse. Click to put it down somewhere:

![](images/schematic5_new.png)

Save your schematic, so you don’t lose your work. Call the file “throughhole.sch”.

Select the “Add” tool again, and choose the “BUTTON-TACTILE-SQUARE” device. Place it to the right of the power jack.

Next, we’ll add the LED. Choose the “LED5MM” device. Place the LED to the left of the power jack.
Finally, add the resistor. Use the device “RESISTORTH-1/4W-CARBON.”

![](images/schematic6_new.png)

Unfortunately, the schematic symbol for the switch is a bit sideways. To fix this, select the “rotate” tool from the palette:

![](images/schematic7_new.png)

And click the symbol for the switch a few times. You can do the same for the LED if you want it horizontal:

![](images/schematic8_new.png)


## Connecting the Parts
Next, we need to wire up the components. Let’s start by connecting the resistor to the switch. Notice that the switch’s symbol gives a clear picture of how it operates: There is a pair of connected terminals on each side (“P” and “P2” on the left and “S” and “S2” on the right), and when we press the button the two pairs will be connected. We need to connect the resistor to one of the pairs. Select the “wire” tool:

![](images/schematic9_new.png)

Then draw a connection between one terminal of the resistor and one of the terminals of the switch:

![](images/schematic10_new.png)

Next, connect the other end of the resistor to the cathode of the led (the cathode is at the tip of the triangle in the LED symbol).

![](images/schematic11_new.png)

Finally, we need to connect everything to the power supply. The symbol for the power jack has three connection pins. The top pin will be connected to the tip of the power plug. The other two will be connected to the barrel. So, if the power supply is tip-positive, the top connector will be 5V and the bottom two will be ground (0V).

Connect the anode on the LED to the 5V pin and then connect the pin on the other side of the switch to the ground pin. Just be sure to wire both of the ground pins together (see below). Also rename and label the power and ground nets by typing ‘name GND’ into the command line box above the drawing and then clicking on the ground net. A label will appear. Make sure you place it so it’s touching part of the net it labels. Do the same for the positive side of the power plug, naming it “5V”.

![](images/schematic12_new.png)

Now, think through how the schematic will operate and convince yourself that this matches what we build on the breadboard.

## Running Electrical Rules Check (ERC)
Eagle provides a mechanism to do a sanity check on your schematic. It’s called Electrical Rules Check (ERC). Select “Tools->ERC”. A window will appear with a list of errors and warnings broken into three categories.

![](images/schematic13.png)

1. Errors: Potentially serious errors
2. Warnings: Potential problems
3. Approved: These are errors and warnings that you have marked as “ok” using the “Approve” button.
The warning and error names are a little cryptic, but you can usually figure out what they are getting at. Look at each error and warning and determine if it’s actually a problem. For instance, it may tell that a pin is not connected. If you did not intend to connect the pin, then it’s not an issue. For errors and warnings that are not a problem, click “Approve.” Eagle will remember this when you re-run ERC. Fix the errors and warnings that represent real issues.
