# Lab 07: Finalize schematic, Layout and Routing, and Design Review

To be completed in your groups.

Check the course schedule for due date(s).

## Skills to Learn
1. Layout out a complex board.
2. Build power and ground planes.
3. Work with layers to control routing.
4. Size traces correctly.
4. Use the autorouter.
5. Protecting analog components from interference.
6. Drawing a logo in Eagle.
7. Perform a design review on the above.

## Equipment, Supplies, Virtues, and Software You will Need

1. Eagle
2. The contents of QuadClass-Resources repo.
3. Patience.
4. Attention to detail.

## Tasks To Perform (Part A)

### Board Shape and Quadcopter Orientation

The first step is to define the size, shape, and orientation of your quadcopter. There are several things you must take into account:

1. You need places to attach four motors. The easiest thing to do is have the board wrap partially around the motor. The motor diameter is 8.5mm (but you should make the holders with an 8.4mm opening so its a firm fit). The “arms” that surround the motors should be at least 3.5 mm thick.  The gap between the arms must be at least 2mm.
2. You should ensure that most of the area the propellers will sweep out as they spin will not be over the board. For instance, putting the motor at the end of an arm will accomplish this. The arm must be long enough, however. The diameter of the propellers is 55mm.
3. Your design must fit with a rectangle whose area is less than 30 sq in (19,354 sq mm).
4. Your design may not contain any internal holes. That is, it must be possible to cut out the board with a single (possibly circuitous) cut.
5. The layout of the motors should be roughly symmetric, but it doesn’t need to be precisely so.
6. I recommend centering your board shape on Eagle’s origin. It will make it easier to place parts symmetrically.

To verify that you have the dimensions correct, please add dimension elements to your board in tDocu. You need these four dimensions (all in mm of course):

1. The width of your board at its widest point.
2. The height of your board at its highest point.
3. The diameter of the opening for your motors (should be 8.4mm). You can also do the radius.
4. The thickness of the thinnest part of the “arm” that goes around your motors (should be > 1.5mm).
5. The width of gap between the tips of the "arms" that go around your motors.


### Configure Eagle
We will be building 4-layer boards. You’ll need to set up Eagle for this. Here are the steps:

1. Select `Edit->Design Rules`
2. Load `jlcpcb-4layer-5mil-small-cream.dru`.  Use this DRU file for the rest of the project.


### Place the Parts
The next stage is to place all the parts on board. Placing most of the parts is straightforward. Here are some things to keep in mind:

1. The location of some components is more important that others. Place these first and use them to guide the overall layout.
	1. The motor controllers should be close to the motors, so the wires will reach the motor pads.
	2. The power jumper and reset button should be out from under the propellers, so you don’t injure yourself while trying turn off the quadcopter.
	3. There needs to space on either the top or the bottom for the battery. There should be a roughly flat area (no big caps no screw terminals) in the way.
	4. The IMU should be at the center of your quad.
	5. Any other LEDs you added should placed in an artistic way (or to achieve whatever effect you are going for).
	6. The FTDI headers need to placed along the edge of the board. The silk screen labels for the pins /must be on the board/. This will ensure that they are oriented correctly and that you can plug in the FTDI serial connector right side up.
	7. The location of the micro-controller is not, in itself, important, but it’s location does drive the location of the antenna and the oscillator.
	8. The antenna needs to be close to the edge of the board and it needs a fair amount of space around it.
1. You should mimic the layout of the FCB in places where signal integrity is important. This includes antenna (see below) and the oscillator.
1. Make your board look good! Align components that are next to each other, make the spacing between components consistent, etc. Board designers appreciate a good-looking board.


### Board Layout Style Guide

Eaglint will warn about most of these.

1.  Align your parts to a 1mm grid.  This will go a long way toward making your board look really good.  The antenna and the the capacitor attached to are excepted.
2.  Align your reference designators and values to a 0.5mm grid.
3.  Allow 1-2mm between parts to make assembly easy.
4.  Orienting all your parts in the same direction makes assembly easier (notice this on the FCB and your remote board).
5.  To be legible, any silkscreen text needs to be at least 0.9mm high, with a 'ratio' of 8%.  You should use the `vector` font.

Boards don't typically include the values of each component.  We do by default because it makes assembly easier.  If you want to turn them off, ask the course staff.

### Logo
Your team may want a logo. Design it and then create a package in Eagle that contains it. Use the techniques you learned in Lab 1. You’ll want to integrate the logo onto your board. You may need to generate different versions with different sizes (there’s no way to scale anything in Eagle).

### The Power Supply

To power your quadcopter, you need provide ample current to the motors and clean 3.3V power to the microcontroller and IMU. The vast, vast majority of bugs I encounter in PCBs like you quadcopter have to do with the power supply. The power supply for the quadcopter is complicated because we have two different power systems that have different requirements: The motors need maximum power — high current and high voltage — while the IMU and microcontroller, need a clean, regulated, consistent voltage and don’t requirement current.

To do this you will need to carefully layout the battery, the voltage regulator, the jumper that connects, them and the connection between `BAT_GND` and GND. You will also need to create a set of “pours” to efficiently regulated and unregulated power to the components that need it.

You have already built your schematic to provide separate power and ground nets to these two sets of components. Now we are going to exploit that separation to physically realize two, mostly separate power distribution systems that will meet these needs.

You have four signal layers (Top, Bottom, and two internal layers). The two internal layers will be a power and ground plane — i.e., dedicated to delivering the power and GND signals across the board. These layers are, for the most part, filled with metal. To create these metal areas, you will create “pours”.

For the 3.3V power supply (`3V3` and `GND`) here are the key considerations:

1. We need to isolate them from the high-voltage supply, both physically and electrically.
2. We need to provide adequate “decoupling capacitance” to minimize noise due to digital switching.
3. We need to provide low-resistance path between the component and `3V3` and the components and `GND`.
4. Correctly layout the voltage regulator.

For the high-current supply (`VBAT` and `BAT_GND`), here are the key considerations:

1. Minimize resistance between the battery and the motor drivers.
2. Minimize resistance on the nets within the motor driver.

#### Basic Principles: Resistance

The resistance of your power and ground connections is important because resistance causes voltage drop.  The voltage drop, `V`, for a current, `I`, flowing through a given resistance, R, is given by [Ohm’s law:](https://www.electronics-tutorials.ws/dccircuits/dcp_2.html) `V = IR`. Power distribution systems carry non-trivial amounts of current so, the voltage drop can be significant.

Our power distribution networks are made of the copper foil that makes up the traces on our PCBs.  Resistance for a sheet of copper (or any conductor) is proportional to sheet’s aspect ratio.  Long, thin wires have higher resistance than short, fat wires. For this reason, sheet resistance is measured in Ohms/square: A square sheet of copper has the same resistance, regardless of its size.

You can calculate the resistance of a wire on PCB using [an online calculator](http://circuitcalculator.com/wordpress/2006/01/24/trace-resistance-calculator). Our wires are 1oz copper.  For instance, a 50mm wire that is 6mils wide has a resistance of 0.127Ohms. If you tried to power one of your motors — which can consume over 1A — using such a wire, the voltage drop would be 0.127V or about 3% of motor power.  Not the end of the world, but still a waste.

The way to minimize resistance is to make wires wider: Increasing the width to 2mm, reduces the resistance to 0.01Ohms or so.

#### Basic Principle: Inductance

The second principle you need to consider is inductance. Inductance is a resistance to change in current. The mathematics are more complicated than they are for resistance, but intuitively, if you suddenly turn on a transistor (i.e., the mosfet in your motor driver or the millions of transistors in your microcontroller), it takes a little while for the current to start flowing.  Likewise, if you turn off a transistor, it take a little while for the current to stop flowing (this is what caused flyback in our motor driver).

There’s a calculator for PCB trace inductance [here](http://chemandy.com/calculators/flat-wire-inductor-calculator.htm). The equation is more complex than Ohm’s law, but the trend is similar: Longer, thinner wires have higher inductance. This resistance to the change in current, can also cause a voltage drop along a wire — the higher the inductance, the larger the drop. Calculating the actually voltage drop is a little complicated because you need to to know the rate of change of the current (dI/dt). You could use one of the oscilloscopes in the maker space to do this for your motor drivers, if you wanted. The important thing, though, is that dI/dt is high, so inductance is a problem.

Fortunately, minimizing inductance and resistance both push us toward making the wires in our power supply networks as short as possible and as wide as possible.

#### Basic Principle: Decoupling

Your quadcopter is full of transistors (small ones in your microcontroller and big ones in your motor drivers), and as they switch they cause noise on the power and ground planes. Noise on the power line can cause digital circuits to stop working (because 1’s start looking like 0’s) and noise on GND can cause all kinds problems between all voltages are relative to GND.

The minimize this noise, we want to increase the capacitance of the power and ground planes. One way to think of capacitance is as a resistance to changes in voltage, so adding more  will reduce noise (which is an unwanted change in voltage).  Small capacitors can filter out high-frequency noise, while larger capacitors filter out lower-frequency noise.

There are two ways to add capacitance.  The first is to add capacitors. The IMU and the microcontroller both describe the number and kind of decoupling capacitors you should incorporate and they tell you to place them as close as possible to the power and ground pins on the device. This is because, to be most effective, the extra capacitance we add needs to be as close to the source of the noise as possible.

The second way to add capacitance is to build a capacitor into the board. A capacitor is just two layers of metal separate by an insulator. We can easily construct this in a PCB by laying down metal in two layers on top of eachother, and connecting one to power and one to ground. The result is a very small capacitor but one that we can put nearly everywhere on the PCB (so it will be a close as physically possible to the devices).

### Building Power and Ground Planes out of Pours

PCBs provide an easy to minimize inductance and resistance while maximizing capacitance in our power distribution system: Power planes. Power planes are entire layers of your PCB dedicated to power or ground. They cover all or most of the PCB and the power and ground planes should overlap as much as possible. This provides:

1. Low resistance and inductance because they planes act as very wide wires.
2. Capacitance because the power and ground planes form two plates of a capacitor.

We will build the power and ground planes out of “pours”.  To create a pour, use the polygon tool.

1. Select the tool and the select the layer you would like the pour to be in. In your case one of the internal layers.
2. Select the area you would like the pour to include. There is a “width” option you can set while drawing the outline. This corresponds to the width of the outline. I recommend using a small value (e.g., 0.5mm).
3. Select the Name tool (Or type name in the command line) and click on an edge of the polygon. Type (e.g., “GND” if the metal should be connected to GND). It may ask if you want to merge nets (yes), what the resulting name should be (e.g., “GND”), and/or whether you want to rename the whole net or just this polygon (just the polygon).

Once the pour is created, you can click the “Ratsnest” tool and Eagle will fill in the pour. Eagle is intelligent about how it fills in the pour. It will carve out areas around pads, SMDs, and traces that are part of the signal assigned to the pour.  For pads, SMDs, and traces that are part of the same signal, Eagle will attach the pour metal to those components.

You can also extend the pours past the edge of your design.  Eagle will trim them to match your board shape. 

The gaps and holes Eagle can divide the pour into multiple pieces that are not directly connected to each other. By default, Eagle will not fill in a pour fragment if there is no connection to the pour’s signal. The unconnected pieces are called “orphans”.

To see the gaps Eagle will create in the pour, the connections it will make to pads and signals, and which portions of the pour are orphans, you can type `ratsnest` in the command line.  If nothing happens, that usually means that no part of the pour is connected to the signal, so the entire thing is an orphan.

The easiest way to ensure that the pour is connected to its signal is to add insert a via in the pour.  You can do this with Via tool.  Select it, make sure it’s set to insert a round via and add one to the pour near the edge. Use the Name tool to set the signal for the Via to the pour’s signal name. Alternately, you can type `via '<pour signal name>'` in the command line and then insert a vias by clicking. Run Ratsnest again, and the pour should fill in. 

To unfill the pours (they can make it hard to see things in your design), you can type `ripup @;` in the command line.

#### Design Your Power and Ground Planes

In our design, we have two power supply signals ( `VBAT` and `3V3` ), so we will use two power planes in layer 15.  How exactly they should be configured will depend on your design, but one reasonable way to start is to draw a polygon around the perimeter of the board (shaped like a “C” if your board is round). It should be no narrower than 4-5 mm at any point. It should pass under all four of your motor drivers and it should also extend to area where your battery terminals, jumper, and voltage regulator are located. This will allow you to void long, high-current wires.

The `3V3` pour should cover the rest of the board (except around the antenna. See below). Set the net for that pour to `3V3`.

There should should be a corresponding ground pour above these two pours (on layer 2). The `GND` pour should be same shape as the `3V3` pour, and the `BAT_GND` pour should be the same shape as the `VBAT` pour.

Note that these pours should not form a complete ring.

The top and bottom layers should have a single, large pour of `GND`.

#### Exploiting Your Power and Ground Planes

The goal of the pours is to provide a low-resistance path for current to and from the battery, but they can only do this if your design uses them.

This means that, wherever possible, you should route your board to use the power and ground planes rather than traces. So, you want the traces that carry `GND`, `BAT_GND`, `3V`, and `VBAT` to be as short and as few as possible.

The easy way to do this is with the `fanout` command.  It'll draw a short wire attached to each pad and put a via at the end.  `fanout SIGNAL GND` will do this for all your ground pins.

It also makes sense to shape your power and ground planes so that the planes are available where the signal is needed. This is why `VBAT` and `BAT_GND` should extend under all the motor drivers, the battery terminals, and the jumper.

#### Laying out the Power Supply

There are three reasons that these components need to be close together:

1. The battery terminals need to be close to the jumper to minimize the length of the high-current trace between them. It should be just a few mm long.
2. The jumper needs to be close to the voltage regulator to minimize the length the high-current trace between them. Just a few mm’s away.
3. The wire bridge needs to be close to the battery’s negative terminal to minimize the length of the trace connect them. Again, a few mm’s.
4. The capacitors for the voltage regulator need to be as close as possible to the regulator.

Section 10 of the voltage regulator data sheet has detailed instruction for layout your power supply. Follow them as closely as possible. Your 0805 caps are not quite small enough to do exactly what they request, but you can come close.

Simultaneously satisfying all these constraints will require careful thought and planning. In particular, these constraint will affect how you layout the power and ground pours.

The traces from the battery to the jumper should be in your high-current net class (see below) as should `BAT_GND` and `VBAT`. 

The design includes a wire bridge that connects `BAT_GND` to `GND`. The reason for this is to ensure that noise from the motors (which are connected to the `BAT_GND)` does not impact the microcontroller. In order for this work, you need to place the bridge as close to both the battery and the voltage regulator as possible. This will ensure that the regulated ground has the shortest possible connection to the negative battery terminal.

### Laying out the Motor Drivers

To maximize thrust and responsiveness, you should keep the high-current (i.e., the mosfet, the motor pads, and flyback diode) components of each motor driver close together. `VBAT` should feed the into the controller directly from the `VBAT` power plane. Since the `VBAT` power plane is in Layer 15, and the pads are on Top, you’ll need at least one via, to connect the two. Consider using more than one via, to provide a wider conduction path. You can add all the vias you want using the via too.

The routing for the low-current components of the motor driver (i.e, the filter cap and resistor, and the pull-down resistor) is less critical.

### Laying out the Radio

The radio is one of the delicate parts of the board because it require special attention for good signal integrity. You should copy the layout on the remote as closely as you can. The key things you’ll need to get right are:

1. Except for the pad that is attached to the circuitry, the antenna should be mounted near the edge of the board without any metal nearby (i.e., there should be no metal in any layer in that area). The one exception is the pad that the other end of the antenna attaches to. 
2. The two capacitors and the balun that make up the antenna driver should not have any other signals near them.
3. The length of the traces from the micro controller, through the capacitors to the balun should be as close as possible to symmetric: Equal length and mirrored geometry.
4. All the wires in the antenna should be as short as reasonably possible. This constraint, combined with the need for the antenna to be near the edge of the board constrains where you can place your microcontroller.
5. The wire between the balun, the antenna, and the capacitor between them should be the same width as the antenna (50mil), and the wire should transition smoothly into the antenna. There should be no sharp corners.

Enforcing all of these requirements will require applying multiple techniques. Begin by laying out the parts to match the layout on the red board. Then read on for tips on how to implement the rest of the requirements.


### Setting Trace Widths

By default, Eagle uses the narrowest wires allowed by the DRU file. For us, that’s 5mil (0.127mm). Narrower wires have higher resistance, and if a trace needs to carry a sensitive signal (e.g., to drive our antenna) or lots of current (e.g., to or from our motors), the trace will need to be wider.

Eagle provides the notion of ‘net classes’ to specify different characteristics for different signals in your design. We will define two new net classes, one for the trace between the balun and the antenna and another for signals within the motor driver (We will deal with `VBAT` and `BAT_GND` separately).

To create or edit a net class, select `Edit->Net Classes`. The dialog box that appears will let you set width of nets in the class as well as the size of vias the class should use and the distance (“clearance”) between nets of different classes.

First, enter “RFSIG” into box next to ‘1’ and enter ‘50mil’ (to match the width of the antenna) for the width. Leave the “drill” and clearance fields at ‘0’ (which mean use the defaults).

Then, enter “HIGHCURRENT” (or something similar) into box 2. This net class is going to be for wires that carry current to the motors, but how wide should those wires be? This depends how much current the wire will carry, how hot we are willing to let it get, how large a voltage drop we can tolerate, how long the wire is, and how thick the copper is. The calculation for this are complex, but fortunately, there are tools online to figure it out for you. [This is a good one](https://www.4pcb.com/trace-width-calculator.html).

Our motors can draw over 1A, so peak current is something over 4 amps.  The batteries we use can deliver up to 9.5.  We are using 1oz copper (which means one square foot of the copper foil weighs 1oz.  THis works out to 0.035mm).  5 degrees Celsius is a reasonable rise in temperature.  Room temperature is 25 degrees C. The traces will be pretty short — probably less than 0.5in (or 12.7mm).

These traces are probably going to be on the top or bottom layers (although you should check this is the case after you’ve routed the board), so we are worried about “external layers in air.” Given all that we, see that a trace 30mils (0.72mm) will work just fine.

There will also be vias carrying these currents.  We can increase the default via size for the next class to match the width of the trace.  The diameter of a via is the drill size (which you can set in the `Net classes` dialog) plus an annular ring (which is the ring of copper you can see around the via).  Our DRU file set the annular ring to be 25% of drill _radius_.  Calculate a drill size that will give an annular ring diameter of 30mil and enter that value for the drill field for the “HIGHCURRENT” class.

Now that we have established the net classes, we need to apply them to some nets. This is easiest in the schematic view using the Change tool. If you click on the Change tool, you’ll get a list options, select “Class” and then select “HIGHCURRENT”. Then, go click on all the wires connecting components of the four motor drivers. You can skip the signals through the pull-up resistor, if you want.

Finally, use the Change tool to put the signal between the balun and the antenna in the “RFSIG” class.

### Laying out the IMU

You need to add some additional bits to the IMU package. We want a solid layer of GND underneath the IMU and we don’t want any wires to run underneath it. You can accomplish this with a combination pours and geometry in `tRestrict` and `bRestrict.`

The IMU datasheet (`datasheets/LSM9DS1.pdf`) and a technical note (`datasheets/LSM9DS1_smd_tech_note.pdf`) provide guidelines for layout the IMU and its associated components. Follow them.

### Laying out and Labeling the Breakout Header

You should label each pin of your breakout header so you’ll know which pin is connected to which signal. The labels should go in `tPlace`.

You should also think about where to put the breakout header. Near the edge of the board is a good choice, since it will provide easy access to the pins. it’s not a bad idea to put silkscreen on the top and bottom for the breakout header.

### Routing the Board

The final step is routing the board. The steps above have given the autorouter most of the information it needs to route your design.  It will set the trace widths correctly and respect all the `t/bRestrict` information that you added.

There are few things you should route by hand.  The most important are the traces between the microcontroller and balun.  Routing the nets from the microcontroller through the crystal to the associated caps is also a good idea.

You will also need to autoroute the connection between the antenna and the balun.  This requires a trick.  If you try to use the semi-automated "follow me" router, it will not work.  This is because the width of the trace (50mil) is so wide that connecting it to one pin of the balun puts the edge of the trace too close to the adjacent pin of the balun.  To avoid this, route as much of the trace as you can at 50mils.  You should be able to get close enough that the trace mostly-engulfs the balun pin.  Then select the "ignore obstacles" option for the routing tool and set the diameter manually to something smaller (like 5mil) and complete the last bit.  The narrower segment should be completely covered by the wider portion of the trace, so it won't make any difference.

Once this is done, in the best case, the autorouter will successfully route your board. However, many things can prevent the autorouter from completing successfully.  If not, you can try hand routing signals that give you trouble.  If you get badly stuck ask the course staff.

 
## Task To Perform (Part B: Design Review)

For this design review, you need to be as careful, meticulous, and demanding as you were on your schematic design review. Everything I said in class about the importance and value of design reviews applies here as well, only more so. There are many more things that can go wrong in the layout phase than in the schematic.

Use the same reviewer/reviewee team pairs listed for [Lab 03: Arduino and Wireless](/a/eng.ucsd.edu/quadcopterclass/labs/lab-98-new-labs/lab-1-github-arduino-and-wireless).

The reviewee needs to provide the following materials to the reviewers:

1. A fully-routed brd file.
2. The corresponding sch file.
3. Copies of the libraries used.
4. A set of gerbers for the same file.
5. A description of any changes they made to standard library parts, whether it autoroutes, and, if not, what what parts of the design require manual routing.
Below is a check list of items you should consider during your design review. The reviewee team should already have used this list as checklist for their design.

* Antenna and Antenna Driver

	* Do all the traces for the antenna driver reside in layer 1?
	* Is the trace between the balun and the antenna extra-thick?
	* Are the other two capacitors close to the balun?
	* Is the trace between the balun and the antenna short (no longer than the corresponding trace on the red board)?
	* Is there a ground pour in layer Top surrounding the antenna driver components?
	* Is there a ground pour in layer 2 surround the antenna driver?
	* Are there vias connecting the two pours and roughly surrounding the antenna driver? are they connected to `GND`?
	* Is one of the antenna’s pads surrounded by the pours?
	* Is there ample space around the antenna that is free of metal on all four layers?
	* Does the layout roughly match the layout on the red board?
	* Are there any traces routed through the antenna driver area that are not related to the driver?

* Power and Ground

	* Does the `VBAT` power plane reach under all four motor drivers?
	* Is the `VBAT` power plane wider than 0.5mm everywhere?
	* Does the `3V` power plane run under microcontroller and near the IMU’s power pins?
	* Does the combination of the `BAT_GND` and `GND` ground plane extend to almost every area of the board (with the exception of the area round the antenna)?
	* Are the `VBAT` and `3V` power pours both in the same metal layer (probably layer 2)?
	* Are there any parts of the power our ground pours that are very narrow? They should be no “necks” narrower than 0.5mm.
	* Does the `VBAT` power plane extend to the battery connector?

* IMU

	* Is the IMU at the center of the board?
	* Are the capacitors specified in the IMU datasheet located as close as is practical to the IMU?
	* Is the IMU oriented so that the X and Y axes are aligned with the pitch and roll axis of the quadcopter?
	* Are there any traces under the IMU? Is there anything other than ground plane under the IMU?

* Headers

	* Are the two FTDI headers oriented so the silkscreen is labels for the pins are on the board and the pins will protrude off the board?

* Microcontroller

	* Is the layout of resonator and the associated caps similar to the layout of those parts on the red board?
	* Do all the traces for the resonator and its associated caps lie in layer Top?
	* Are the decoupling caps for the microcontroller located as close as possible to power pins of the microcontroller?

* Power Supply

	* Are the caps associated with the voltage regulator located near the regulator?
	* Is the voltage regulator located near the battery connector?
	* Does the `3V` power plane run underneath the voltage regulator?

* Motor Drivers

	* Are the traces that carry large currents thick enough?

* Aesthetics

	* Does does the layout look nice?
	* Are nearby parts aligned?
	* Are the reference designators arranged so they don’t overlap eachother or pads?

* Mechanical

	* Given the location of the motors, will the props clear the board (except for the arms)?
	* Is the “cup” for the motors the right diameter?
	* Are there any large internal holes in the board?
	* Is the board roughly symmetrical?

* Checks

	* Does DRC check pass without errors?
	* If DRC doesn’t pass with no errors, does the team have good explanations for why the errors are ok?
	* Does DFM check pass with no show stoppers?
	* Does Eagle Lint pass?

* Gerber Files

	* Are areas around the antenna clear in the gerber files?
	* Are the power planes where you expect them to be in the gerber files?
	* Are there any traces that cross in an unexpected way in the gerber files?
	* Are there any elements that should be in the silkscreen that show up in metal layers?
	* Are there any elements that should be in the metal layers but that show up on the silkscreen?
	* Does the board outline match what was draw in the brd file?
	* Does FreeDFM pass?

## 

## Turn in Your Work
### 

### Rubric Part A
“Perfect” score: 10

Initial points: 12

Submit the following to your github repo (you can leave other files in there. These are the file relevant to this lab):

1. Your `quadcopter.sch.`
2. Your fully-routed quadcopter.brd.
3. Your `lbr/LED.lbr`.
4. Your `lbr/custom.lbr` (maybe renamed to custom_<name>.lbr and maybe two of them)
5. `lbr/quadparts_prebuilt.lbr`.
6. A file called quadcopter.cam.zip that contains the CAM files for the design.
Submit it to [Eaglint](http://www.google.com/url?q=http%3A%2F%2Feaglint.nvsl.io%2F&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNFrH7bQMLjAUWzVGFESRxTQu6D-EQ). The tool will not look at any other libraries, so if you use any other libraries the consistency checks will fail.

For this part of the lab, human review will succeed instantly, if you have no errors or warnings.

Once it passes, create a tag called “Lab07a” Be sure to make it an “annotated” tag and push it to your repo ( [https://git-scm.com/book/en/v2/Git-Basics-Tagging](https://www.google.com/url?q=https%3A%2F%2Fgit-scm.com%2Fbook%2Fen%2Fv2%2FGit-Basics-Tagging&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNGOTg8gwVJ3tdWstD6PfspdhSq1Vg) ). Verify that it is visible on github.

### 

### Rubric Part B
“Perfect” score: 10

Initial points: 14

Commit the following:

* The list of questions your reviewers had about your design as `design_reviews/questions_about_our_board.txt`.
* The list of questions you had about the design you reviewed as `design_reviews/questions_about_their_board.txt`.
* Your changes to your schematic, board, and libraries.
* An updated quadcopter.cam.zip.
Submit it to [Eaglint](http://www.google.com/url?q=http%3A%2F%2Feaglint.nvsl.io%2F&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNFrH7bQMLjAUWzVGFESRxTQu6D-EQ). 

Once it passes and human review, tag your repo: Lab07b.

Grading for the design reviews is in two parts:

1. You will lose points for any problems I find in your reviewee’s design that you should have found.
2. You will lose points for any problems your reviewees found in your design, but you did not fix correctly.
3. You will lose a point for each failed submission to Eaglint and human review.


## Routing

Fanout
design explorer


## Guidelines

1.  Images are basically bit maps and they are stored ineffeciently.  If your drawing is to large or complex, it'll crash eaglint.  Large blocks and shapes are fine.  Lots of fine detail is not good.

## IMU

1.  There should be no metal under the IMU.  You need to create a ''

## Things to Check

1.  The trace from the balun through the cap and to the antenna should be the same width as the antenna trace and the transition should be smooth.
2.  Gap distance in motor holder >=2mm
3.  Do RF diff pairs enter through the center of the pad?

- Antenna layout.
    - symmetrical RFN/RFP
    - short line to antenna
    - metal under the driver (m2)
    - Metal under on separate pour.
    - metal on top
    - vias
