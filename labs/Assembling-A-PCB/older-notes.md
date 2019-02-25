# Lab 09: Board Assembly

## 

## Skills to Learn
1. Soldering practice.
2. Board assembly.
3. Patience.
## 

## Equipment, Supplies, and Software You will Need
1. Your manufactured PCB.
2. All the parts for you quadcopter.
3. Some double-stick tape
4. Tweezers
5. Solder paste in a syringe w/tip (1 syringe per group)
6. Patience
7. Flux in a syringe (1 syringe per group)
8. Soldering iron (in maker studio)
9. Heat gun (in maker studio)
10. Protective eye-wear
11. uController programmer (one or two for the whole class)
## 

## Tasks To Perform
### 

### Board Testing
The first thing to do is test your board for manufacturing defects. There are a few ways to do this:

1. Visually inspect the board looking for things like

    1. Vias and through-hole pads that are blocked by solder mask.
    2. Holes in the solder mask
    3. Visible bridges between traces. Holding the board up to the light can help, but the power and ground planes limit where you can see problems.
    4. Anything else that looks amiss.

* Electrically check the boards using a multimeter in continuity mode.

    * Probe pairs of pins that you know should be connected. If they aren’t, investigate.
    * Probe other pairs of pins. If you find a connection, check the schematic to see if it should be there.

### 

### Prepare Your Assembly Aids
A little preparation before assembling your quadcopter will make the task much easier. You should prepare two things before you begin:

A Printed Bill of Materials/Part holder

Create a printed bill of materials. This is a list of all the parts on your quadcopter. You can create one by opening your schematic in Eagle, and selecting “File->Export->BOM”. It’ll open a dialog box that contains a list of all your parts and their attributes. Make sure “list attributes” is checked and select the radio button “values”.

Select “CSV” as the output format, click Save… and put the file somewhere easily accessible.

For some reason, the CSV — comma-separated values — file ends up being semi-colon separated. To open it, fire up Excel and open a new document. Select File->Import and click on CVS, find the file you just saved and open it. You should get the Excel import dialog box and import the file as a text file. Select “delimited” and click “Next”. Then select ‘semicolon’ as your delimiter. Click “Finish”

The most important columns are “QTY”, “Parts”, “DISTPN”, and “VALUE”. QTY will remind you how many you should have. Part will tell where on the board it goes and DISTPN and VALUE will help you find the part you need among your several bags of parts. Drag the columns titles around so that Part and DISTPN are the first and second columns.

Delete everything except those three columns. Print it. You should have something that looks like this:

[image:https://lh4.googleusercontent.com/f30pJYOc3ei804LWWZyqWqbus7NU3ZoT0ehAJnCAXCZhxQKlNxWzb_ifdwzTsmZkhP8AYlVOxStcEY-BtWFtFRcX2JdfF8Xd3ajUJBM_tQHRyIEA35I=w271]

Your parts will come in a bunch of small bags — one type of part per bag. You can match up the parts on the list with the parts in the bags. You can also tell the parts are for your quadcopter because in the “customer reference” field on the label they will have something like “<yourteam>_R1_R5” which means the contents of the bag are the parts for R1 and R5 on your board.

Many of the parts will come in short strips. You can attach these strips to the printout (with the parts facing up) with double stick tape, and this will make them easy to extract, one at a time. If they don’t come in strips, leave them in the bag.

For the parts that are shared across all the quadcopters, you will have exactly enough parts for two quadcopters (I have many extras of these). For your custom parts (E.g., your LEDs and any associated resistors), you will have 1 spare. Don’t lose your parts!!!

Assembly Drawing

Another items that is useful is an assembly drawing. This is larger-than-real life drawing of your board that will make it easier to find where particular parts go. These files are generated automatically by our CAM pass. They are called `<designname>.tasm.ps` (for the top) and `<designname>.basm.ps` for the bottom.

Print it out larger enough to fill a page or just look at them on your computer. You can also just use eagle to look at your board layout.

### 

### Assembly
This process takes a while. You should start early in the class period and expect not to finish until the end of the lab period.

Assemble Your Board

I will do a demo for your group about applying solder paste.

You need to apply paste to all the pads on your boards except the following:

* The pads for your motors.
* The pads for your antenna.
Here’s a video that gives you the basic idea. You need to move reasonably quickly otherwise the paste can dry out. Don’t use too much!

Pay close attention to the orientation of your parts. The trickiest ones are the LEDs and the diodes in your motor drivers and the large 220uF capacitors. The LEDs won’t work if you put them in backwards, but the big caps will explode/burn up if you get them wrong.

Two parts require special attention: The IMU and the microcontroller. Please find me or Jorge when it comes time to apply paste to these parts and places them on the board.

Here’s a video showing placement with tweezers. Your solder paste won’t look as tidy since the paste in the video was dispensed with a stencil rather than by hand. It also shows up close what happens during reflow.

Solder Your Board

Once you’ve placed everything, we will reflow your board. The reflow oven will take run your board through a pre-programmed temperature profile that gently heats the board and its components and melts the solder. It takes about 10 minutes.

The reflow process will probably handle everything perfectly except your IMU and the microcontroller. This video show how to touch up the soldering on these parts, and it shows clearly why we make the pads for those parts stick out so far. You should watch this, but when it comes time to do it, you should ask me or Jorge for help.

The antenna needs to be soldered by hand because it can’t handle the heat of the reflow oven. The video below shows how to easily solder SMD parts by hand. Be generous (but not too generous!) with the flux. The video also illustrates crazy small parts can get.

Finally, you need to solder on your headers. You’ll need the 2x3 header, the FTDI (1x6) header, and the jumper for certain. You can leave off your debug header for now and add it later if/when you need it. Here’s a video shows how to solder headers:

Another useful trick is removing parts once they are down. This is hard for a couple reasons: 1) you need to get both terminals hot at the same time, but you only have one soldering iron 2) If you pull too hard on the parts before the solder is melted, you will pull up the pad, ruining the board (usually, Sometimes we can fix it). This video shows how, counterintuitively, the solution is to add /more/ solder to each end of the part and the use the side of the soldering iron to get both sides melted at once. The most common cause of needing to remove parts is getting an LED in backward. LED case are plastic, and you should generally assume that removing them will ruin them. Get a new one rather than trying to reuse the one you removed.