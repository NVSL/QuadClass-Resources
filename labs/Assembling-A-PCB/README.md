# Assembling PCBs

During this lab you will assemble and "bring up" a PCB.  This is practice for assembling and bringing up your quadcopter.

The default lab has you assemble a simple Arduino-compatible board based on the microcontroller we are using for this course.  It's called the Bare Bones Board (BBB).

Alternately, you can build a board for your own remote control that you can keep after the class is over.  [Read this](Building-Your-Own-Remote.md) for more details.  This will at least double the time spent assembling the board, so keep that in mind when deciding when to start assembling.


folds over to the right.  Keep that space clear
Tools on the left
Put stencil in "portrait" orientation
clean up stencil with alcohol

## Preparation

Assembling a board (especially your first one) can take a couple hours.  Also, the working time for the solder paste is limited, so you need to work reasonably quickly once you start.

Begin by making sure you have everything you need. 

## Applying Solder Paste

### What You Need

1. Blue tape
2. Solder stencil
3. 4 scrap PCBs the same thickness as your board. 
4. 1 large putty knife
5. 1 small putty knife
6. Butcher paper
7. Gloves
8. A magnifier
9. Alcohol in a pump dispenser
10. Kimwipes
11. Compressed air
12. Solder paste

### Preparing Your Space and Aligning Your Stencil

You need a large, clear space to apply solder paste.

1. It can be messy, so cover everything with butcher paper.
2. Tape down your scrap PCBs so they will hold your board still.  The PCB should be oriented so the stencil aligns with it in "portrait" orienation (tall rather than wide).
3. Align your stencil with your board so the wholes line up perfectly with the pads. This must be very precise.
4. Tape down the right edge of your stencil so you can easily lift it on and off your board like a page of a book.
5. Check the alignment again
6. Verify your alignment with course staff.

### Apply Paste

1. Use the narrow putty knife to apply a thin (1cm) bead of paste to the edge of the wide putty knife.
2. Hold the wide putty knife at a 45-degree angle and drag it across the stencil, forcing the paste through the holes.  Press pretty hard and move smoothly.  Make sure you align the knife so it will pass over all the pads on the board.  You can only make one pass. 
3. Carefully and gently and in one motion, lift up the stencil and fold it back.
4. Examine the paste pattern with your magnifier.  Look out for
   * Pads with missing paste
   * indistict or touching paste blobs (esp. on the IMU and microcontrollers)
5. Check it with course staff and point out any problems you spotted.
6. If it looks good, carefully remove your board.
7. If something is wrong, you'll need to remove all the paste using chemwipes and alcohol and start again.
8. You need to be very selective about paste application.  The solder needs to be very crisply defined.  If it doesn't look good, you'll have to redo it.

**Poor Stencil Alignment (some holes are dark)**

![Poor stencil alignment](images/bad_alignment.jpg)

**Good Stencil Alignment (all holes are gold)**

![Poor stencil alignment](images/good_alignment.jpg)

**Poor Paste Application**

![Poor solder paste](images/bad_paste_application.jpg)

![Poor solder paste](images/bad_paste2.jpg)

**Good Paste Application**

![Good solder paste](images/good_paste2.jpg)

![Good solder paste](images/good_imu_paste.jpg)


### Cleanup

1. If someone else is going to use putty knifes immediately, you can leave them.
2. If not (or in doubt), clean them my scraping the paste back into its container and wiping them with alchol and chemwipes.
3. Wipe up any stray solder paste on the table, *both* sides of the stencil.
4. Blow any remaining solder paste out of the stencil holes with compressed air.

## Placing Components

### What You'll Need

1. A complete part kit for your board.
2. A pair of tweezers
3. A magnifier.
4. Steady hands.

### Get Organized

You need to place parts carefully and precisely.  You also need to work somewhat quickly.  With practice, you can place a board like the breakout board in 10 minutes.  You should not take more than an hour.  Getting organized will help you meet this goal.

1. Get _everything_ you need together at once.
2. Have a clean work area (preferably with a white surface).  The parts are _tiny_.  The less stuff there is around, the less likely you are to lose anything.
3. Make sure there are no strong winds blowing (drafts, open doors)
4. Make sure you are unlikely to be bumped.
5. Allow adequate time.  
    * Paste has a limited working time, and the course staff are not around forever.    
    * Assembly will take ~1 hour.  Reflowing takes ~12 minutes.  Something will go wrong, budget ~30min.  
    * So, you shouldn't start assembly unless you have _at least_ 1:45 left in class.
5. Eat something before hand.

### Placing Parts

1.  Dump out all the parts of a particular type on your work surface.
2.  Once the part is down, don't fiddle.  Moving the parts smears the paste.  The parts will self-align a bit during reflow, so it doesn't have to be perfect.
3.  If a part is upside-down, picking it up and dropping it is a good (if probablistc) way to turn it over.
4.  Don't pick up the board.  You more likely to bump a part if you pick up the board.
5.  Arrange your pile of parts at your board so you don't have to reach over the board, otherwise, you're more likely to bump parts.
6.  Don't mess up.  If something goes significantly wrong, you have to start again.
7.  Do one type of part at a time (e.g., 100Ohm resistors).  You have exactly the right number of them, so when they are gone, you're done.
8.  Typing `show C1 C2 C3` in Eagle will highlight where `C1`, `C2`, and `C3` are on the board. 
9.  You are to almost drop the parts onto the board.  Do not press them down.  It'll displace the solder paste.
10.  If you think you've messed things up, get the TA or prof.  They may be able to save you...or not.

**A Stencil**
![Stencil](images/stencil.jpg)

**Good Cap Placement**
![Good cap placement](images/good_cap_placement.jpg)


### Notes Particular Parts

I suggest you proceed in this order.  This is roughly from easiest to hardest.

Note that on the remote, there are many parts you will leave unpopulated. Only put parts where there is solder paste.   

In the photos, I've highlighted the polarity markings on the beard and the part.

#### Resistors

1. These are pretty easy -- a good warm-up.
2. Make sure they are marking-side-up.

#### Capacitors

1.  The small caps are non-polarized, so direction doesn't matter.
2.  The big caps are polarized. The stripe goes near the dot. (Quad/FCB only) ![Big Cap](images/big_cap_orientation.jpg)
3.  Align these carefully.  If you get it wrong your board will look ugly.

#### MOSFETs (Quad Only)

1. The correct orientation is obvious.
2. You need to align the pins carefully.

#### Voltage Regulator and Battery Charger.

1. Orientation is obvious (there's three pins on one side and 2 on the other)
2. Be sure not to confuse these two if you are assembly a remote.
3. Only the remote has a charger.

#### Button 

1. Either orientation is ok.

#### Crystal

1.  It seems like orientation should be important, but it's not.  The part is diagonally symetric. 

#### LEDs

1. This is your first polarized component, pay close attention or your board will be doomed to darkness.
2. The green line (yes, there really is one) goes near the dot. 
![LED orientation](images/led_orientation.jpg)


#### Diodes

1. These are also polarized, but the markings are extremely hard to see.  They are printed black on black.
2. If you hold the diode and look at in the light, one end has a faint rectangular bar code on it.  The other has an "S"
3. The barcode goes near the dot.
![Diode orientation](images/diode_orientation.jpg)

#### Balun

1.  The red dot faces up and goes next to the dot.  This means the red dot will be farther from the microcontroller and nearer the antenna.
2.  Pay close attention to the aligment.
3.  Check it with your magnifier.
![Balun orientation](images/balun_orientation.jpg)

#### Microcontroller

1.  Make sure you orient it correctly.  The dot goes next to the dot.
2.  The silkscreen markings fit tightly to the corners of the package, so use them as a guide. ![MCU orientation](images/imu_mcu_orientation.jpg)

3.  Once it's down, check the alignment.  If it's not perfect, do not pick it up.  Instead, nudge it every so gently to align it.
4.  The magnifier will help you check alignment.  You can see the pads on the side of the package.  the need to be aligned with the patches of solder paste on the board.

**Good MCU Placement**
![Good MCU Placement](images/MCU_alignment.jpg)

#### IMU (Quad only)

1.  Similar to the microcontroller.
2.  The dot goes near the dot. (see image above for MCU)
3.  Use the silkscreen markers to align it and the "drop" it on.
4.  The pads are smaller, so alignment is more important.
5.  Don't fiddle!

#### 6-pin Header (Remote Only)

1.  The surface-mount 6-pin header is not hard to place, but it sticks up and is easy to bump, so do it last.

#### USB Recipcal (Remote Only)

1.  The key point of alignment are the pins on the back and 5 pads on the board.
2.  Check it with the magnifier.

## Reflow

### What You Need

1. A TA or professor.
2. The reflow oven.

## Touch Up and Throughhole Components

### What You Need

1. Soldering station.
2. A syringe of flux.
3. Thin, lead-free solder.
4. Swaps and/or a horse-hair brush.
5. Alcohol in a squirt bottle.
6. kimwipes.
7. Blue tape.

### Checking Soldering

**Good MCU Soldering**
![Good MCU Soldering](images/good_mcu_soldered.jpg)

**MCU Soldering Requiring Touch Up**
![Bad MCU Soldering](images/bad_mcu_soldering.jpg)

### Cleaning up Flux Residue

Wire solder has flux in the middle to help the solder flow.  SMD rework requires adding flux manually.  In either case, the result is a yellow-brown, unattractive residue that starts out sticky and hardens over time.

To keep your board looking nice and clean, you should remove it ASAP.  If you have several things to fix, do not wait till the end.  Due it one part at a time.  To clean up the flux, place a kimwipe over the area and squirt rubbing alcohol onto it.  Then, take a hair brush of swap and rub the kimwipe around over the area.  It'll absorb the flux residue.  Repeat once or twice.

If you don't have alcohol in a squirt bottle, just get the kimwipe very moist with alcohol and put it on mannually.

### Mounting Throughhole Parts

#### Headers

1.  Tape down the power jumper, debug header, FTDI header, and gimbal pins (remote only) using blue tape. 
2.  The main challenge is getting them straight up and down and not crooked.  Do your best.
3.  The white gimbal sockets go on top.  The 6-pin header connectors go on the bottom. (Remote only)
4.  You won't populate the big headers on the breakout board by default.

#### Battery Terminals

1.  Similar to the headers, but orientation matters.  The holes on the side should point toward the '+' and '-' on the board.
![battery orientation](images/battery_orientation.jpg)


#### Motor Recepticals (Quadcopter only)

1.  Orientation is very important.  Removing/replacing these things is really hard. 
2.  The pins are not centered, and part should be oriented so it fits completely inside the silkscreen outline.  If it's backwards it'll protrude on one side.

### Common Reflow Problems

You should inspect all the parts on your board for problems.  

1. Sometimes solder won't reflow on some parts of the board.  You can tell because the solder paste is rough and not shiny.  To fix it, add a _tiny_ amount of flux and touch it with your soldering iron.
2. Parts sometimes get dislodged during reflow (It's actually pretty windy in the oven).  If only one terminal of the device is still connected, melt that side and lift it up.  If two terminal are connected, see course staff.
3.  You realize you forgot a part.  See course staff for a lesson in mannual surface mount assembly.

## What's Next?

Once you've assembled your board you need to [Flash the bootloader and bring up your board](Flashing-The-Bootloader.md)

