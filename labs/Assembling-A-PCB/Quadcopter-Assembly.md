# Assembling Your Quadcopter

Assembling your quadcopter is similar to assembling the charger board, but more involved because there are more components.

## Preparation

Assembling a board (especially your first one) can take a couple hours.  Also, the working time for the solder paste is limited, so you need to work reasonably quickly once you start.

Begin by making sure you have everything you need.  For the quadcopter assemmblies we will, have everything you need set up ahead of time.

## Safety

The solder paste we use (like all solder paste) is potentially toxic (although it's lead-free).  The material safety datasheet is here: [MSDS](../../Datasheets/NP560_SDS_EN_(V3)US.pdf).

You must take the following precautions:

1.  You must wear eye protection while applying the paste or using a soldering iron.  The makerspace has glasses across the hall from our classroom.  Your own glasses are fine.
2.  You must wear gloves while applying paste and placing parts.
3.  You must not eat or drink while working with solder paste.  During assembly labs, no food or drink is allowed in the classroom.
4.  You must wash your hands before eating or drinking after the lab.


## Preparing Your Part Kit

You can think of the part kit for your quadcopter as breaking into three parts:

1.  The parts that are common to all the quadcopter designs.
2.  Additional instances of the parts common parts.
3.  Parts specific to your design.

For the first group, we have part packets prepared for you just as we did with the BBB board.  Grab *one* of each packet.

The second group is usually resistors and mosfets (e.g., to control LEDs).  Take additional packets of these parts to get what you need.

For the third group, we have ordered parts from Digikey for you.  Each part will come in it's own bag with the "customer reference" field containing the list of reference designators that the parts correspond to.

## Part Notes

The quadcopters have a few parts that were not on the BBB.  Here they are (quantities are for the core design.  You may have other parts, depending on your LED design):

### Surface Mounts Parts

| Part              | Picture                                            |
|-------------------|----------------------------------------------------|
| MOSFET            | |   ![Mosfet](images/mosfet.jpg).                    |
| IMU               | ![IMU](images/IMU.jpg).                            | 
| 10KOhm Resistors  | ![Resistor](images/resistors.jpg).                 |
| 220 uF Capacitor   |   ![Caps](images/big_cap_orientation.jpg)          |
| 0.01uF Capacitor   | ![Capacitors](images/capacitors.jpg).              |
| Diode               | ![Diode](images/diode_orientation.jpg).            | 
| MCU.                 | ![MCU](images/MCU_alignment.jpg).                  |
| Crystal              | ![Crystal](images/crystal.jpg).                    |
| Balun                | ![Balun](images/balun_orientation.jpg).            |
| LED Red &Green       | ![LED](images/led_orientation.jpg).                |
| Voltage Regulator    | ![Vgg](images/voltage-regulator.jpg).              |

### Through Hole Parts

| Part              | Qty | Picture                                            |
|-------------------|-----|----------------------------------------------------|
| Screw Terminals   | 1   | ![Screw](images/battery_orientation.jpg).          |



## Assembly Drawings

Eagle provides a simple mechanisms to help you place parts.  Open your `.brd` file.  You need to enable  the "Design Manager" (`View->Design Manager`).

The "Devices" pane shows a list of all the parts in your design.  Sort the list by "value" and hide the other columns (wrench icon).

You can now select all the parts of a given type and Eagle will highlight their location on the board.

## Applying Solder Paste

### What You Need

1. Blue tape
2. Solder stencil
3. 4 scrap PCBs the same thickness as your board. 
4. 1 large putty knife
5. 1 small putty knife
6. Butcher or craft paper
7. Gloves
8. A magnifier
9. Alcohol in a pump dispenser
10. Kimwipes
11. Compressed air
12. Solder paste
13. Gloves

### Preparing Your Space and Aligning Your Stencil

You need a large, clear space to apply solder paste.

1. It can be messy, so cover everything with a big sheet of butcher or craft paper.  Tape down the paper, so it's not sliding around.
2. Tape down some scrap PCBs so they will hold your board still.  The PCB should be oriented so the stencil aligns with it in "portrait" orienation (tall rather than wide).
3. Align your stencil with your board so the wholes line up perfectly with the pads. This must be very precise.
4. Tape down the right edge of your stencil so you can easily lift it on and off your board like a page of a book.  The tape should be on the right, and there should be clear space for the stencil to lay flat.  
5. Check the alignment again
6. Verify your alignment with course staff.


### Apply Paste

1. Use the narrow putty knife to apply a thin (1cm) bead of paste to the edge of the wide putty knife.
2. Hold the wide putty knife at a 45-degree angle and drag it across the stencil, using firm (but not too hard), constant pressure to apply a thin layer of paste across across the stencil.  Press just firmly enough that there is a thin layer of paste left on the stencil (see photo).  If you push too hard, it will force paste through and slightly under the stencil, which is not what you want.  Move smoothly.  Do not stop.  Make sure you align the knife so it will pass over all the pads on the board.  You can only make one pass.
3. Turn the squeegee over and scrape the extra paste off the stencil with the squeegee almost vertical and held gently against the stencil.  There should be very little paste left.  Again, you can only make one pass.
4. Smoothly and in one motion lift up the stencil and fold it back.  Lifting it up and accidentally dropping it back onto the board is means redoing it.
5. Examine the paste pattern with your magnifier.  Look out for
   * Pads with missing paste
   * Indistict or touching -- even slightly -- paste blobs (esp. on the IMU, microcontroller, and balun).
6. Check it with course staff and point out any problems you spotted.
7. If it looks good, carefully remove your board.
8. If something is wrong, you'll need to remove all the paste using Kimwipes and alcohol and start again.  You can do this many times.
9. You need to be very exacting about paste application.  The solder needs to be very crisply defined.  If it doesn't look good, you'll have to redo it.  Redoing it is not hard, and it's good practice, so there's no point in settling for sub-standard paste application.


**A Stencil**

![Stencil](images/stencil.jpg)

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
2. If not (or in doubt), clean them by scraping large blobs of paste back into its container and wiping them with alcohol and kimwipes.
3. Wipe up any stray solder paste on the table, *both* sides of the stencil.
4. Blow any remaining solder paste out of the stencil holes with compressed air.


## Placing Components

### What You'll Need

1. A complete part kit for your board.
2. A pair of tweezers
3. A magnifier.
4. Steady hands.

### Get Organized

You need to place parts carefully and precisely.  You also need to work somewhat quickly.  With practice, you can place a board like the BBB in 10 minutes.  You should not take more than an 45 minutes.  Getting organized will help you meet this goal.

1. Get _everything_ you need together at once.
2. Collect all the parts you will need (see below).  For the BBB assembly, you will need 1 packet of each type of part.  They will be laid out for you.
3. Have a clean work area (preferably with a white surface).  The parts are _tiny_.  The less stuff there is around, the less likely you are to lose anything.
3. Allow adequate time.  
    * Paste has a limited working time, and the course staff are not around forever.    
    * For the BBB, Assembly will take ~0.5 hour.  Reflowing takes ~12 minutes.  Something will go wrong, budget an extra ~15min.  
    * So, you shouldn't start assembly unless you have _at least_ 1 hour left in class.
    * For quadcopter or the remote, allocate 2 hours.
5. Eat something before hand.  You need to patient and steady.

Most of the parts come on paper or plastic tape.  We have cut the tape to the right length for you and labeled them.  There are part portions available in the size required for the BBB and for the typical number of parts needed for your quadcopters.  This means you should take 1 piece of tape for each type of part on your board.

The throughhole parts are mostly loose.  Take just as many as you need.

### Placing Parts

1.  Dump the parts from one a packet out on your work surface.
2.  If a part is upside-down, picking it up and dropping it is a good (if probablistc) way to turn it over.
3.  Place the part gently and as precisely as you can.
4.  Once the part is on the board, move it as little as possible.  Moving the parts smears the paste.  The parts will self-align a bit during reflow, so it doesn't have to be perfect.
5.  Don't pick up the board.  You more likely to bump a part if you pick up the board.
6.  Arrange your pile of parts at your board so you don't have to reach over the board, otherwise, you're more likely to bump parts.
7.  Don't mess up.  If something goes significantly wrong, you have to start again.
8.  Do one type of part at a time (e.g., 1uF caps).  For the BBB, you should have exactly the right number of them, so when they are gone, you're done.
9.  Typing `show C1 C2 C3` in Eagle will highlight where `C1`, `C2`, and `C3` are on the board.   You can also say `show C*` to see where all the caps are.  For the BBB refer to the assembly drawings below.
10.  Place the parts very gently onto the board.  It should almost be like you are dropping them.  Do not press them down.  It'll displace the solder paste.
11.  If you think you've messed things up, get the TA or prof.  They may be able to save you...or not.


### Notes on Particular Parts

I suggest you proceed in this order.  This is roughly from easiest to hardest.

This list covers all the parts on the BBB, your quadcopter, and the quadcopter remote.  Some parts only apply to one or two of those boards.  The parts that are relevant for BBB assembly have a BBB assembly drawing showing where, exactly, those parts should go.

Note that on the remote, there are many parts you will leave unpopulated. Only put parts where there is solder paste.   

In the photos, I've highlighted the polarity markings on the board and the part.

#### Resistors

![Resistors](images/resistors.jpg)

1. These are pretty easy -- a good warm-up.
2. Make sure they are marking-side-up.




#### Capacitors

1.  The small caps are non-polarized, so direction doesn't matter. ![Capacitors](images/capacitors.jpg)
2.  Align the big caps carefully.  If you get it wrong your board will look ugly.

**Good Cap Placement**

![Good cap placement](images/good_cap_placement.jpg)


#### Voltage Regulator and Battery Charger.

![Voltage Regulator](images/voltage-regulator.jpg)

1. Orientation is obvious (there's three pins on one side and 2 on the other)
2. Be sure not to confuse these two if you are assembly a remote.
3. Only the remote has a charger.


#### Button 

![Button](images/button.jpg)

## Button


1. Either orientation is ok.

#### Crystal

![Resistors](images/crystal.jpg)


1.  It seems like orientation should be important, but it's not.  The part is diagonally symetric. 

#### LEDs

1. This is your first polarized component, pay close attention or your board will be doomed to darkness.
2. The green line (yes, there really is one) goes near the dot. 

![LED orientation](images/led_orientation.jpg)


#### Diodes

1. These are  polarized, but the markings are extremely hard to see.  They are printed black on black.
2. If you hold the diode and look at in the light, one end has a faint rectangular bar code on it.  The other has an "8"
3. The barcode goes near the dot.

![Diode orientation](images/diode_orientation.jpg)

#### Balun

1.  The red dot faces up and goes next to the dot.  This means the red dot will be farther from the microcontroller and nearer the antenna.
2.  Pay close attention to the aligment.
3.  Check it with your magnifier.

![Balun orientation](images/balun_orientation.jpg)

#### Microcontroller

1.  Make sure you orient it correctly.  The dot goes next to the dot.
2.  The silkscreen markings fit tightly to the corners of the package, so use them as a guide. 
3.  Once it's down, check the alignment.  If it's not perfect, do not pick it up.  Instead, nudge it every so gently to align it.
4.  The magnifier will help you check alignment.  You can see the pads on the side of the package.  The pins on the package need to be aligned with the patches of solder paste on the board.


**MCU Alignment**

![MCU orientation](images/imu_mcu_orientation.jpg)

**Good MCU Placement**

![Good MCU Placement](images/MCU_alignment.jpg)


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

1.  Similar to the headers, but orientation matters.  The holes on the side should point toward the '+' and '-' on the board.

#### Battery Terminals

![battery orientation](images/battery_orientation.jpg)


#### MOSFETs

![MOSFET](images/mosfet.jpg)

1. The correct orientation is obvious, since the package asymmetrical.
2. You need to align the pins carefully.

#### IMU 

![IMU](images/IMU.jpg)

1.  Similar to the microcontroller.
2.  The dot goes near the dot. (see image above for MCU)
3.  Use the silkscreen markers to align it and the "drop" it on.
4.  The pads are smaller, so alignment is more important.
5.  Don't fiddle!


### Cleaning up Flux Residue

Wire solder has flux in the middle to help the solder flow.  SMD rework requires adding flux manually.  In either case, the result is a yellow-brown, unattractive residue that starts out sticky and hardens over time.

To keep your board looking nice and clean, you should remove it ASAP.  If you have several things to fix, do not wait till the end.  Due it one part at a time.  To clean up the flux, place a kimwipe over the area and squirt rubbing alcohol onto it.  Then, take a hair brush of swap and rub the kimwipe around over the area.  It'll absorb the flux residue.  Repeat once or 
 twice.  Don't be shy with the alcohol, it won't hurt anything.

If you don't have alcohol in a squirt bottle, just get the kimwipe very moist with alcohol and put it on mannually.

### Mounting Throughhole Parts

You'll have to solder the through-hole parts by hand. The process is the same for all of them:

1.  The part goes on the side of the board with the reference designator.
2.  Tape down the part using blue tape. 
3.  The main challenge is getting them straight up and down and not crooked.  Do your best.

We aren't populating the big headers on the BBB to save time in class.

#### ISP Header

![ISP](images/ISP-header.jpg)


## Time Management

Assembling your boards will take longer than the charger, because there are more parts, and class time is limited.  To ensure you have time to apply paste, place parts, and reflow the boards, you must start applying paste **at the beginning of class**.  

We will have stations set up for applying paste at 10am on days we are doing assembly for this purpose.

This means you need to have your part kit completely assembled **the class period before**.  If your part kit is not ready at the starte of class, we will not let you start assembly that day.

You also need to work quickly.  Your quadcopters have between 70 and 100 parts (vs 12 for the charger), and you need to complete assembly at least 1 hour before the end of class (2pm).  This means you need to be placing 1 part ever 30-45 seconds or so.  Keep an eye on the clock.

## Scheduling

On assembly days, the TA will set have parts out by 10am and paste assembly stations ready by 10:30.

On Tuesdays, you must have boards ready for reflow by 1pm. 

On Thursdays, we have to vacate the room by 1pm.  I would suggest starting (and finishing) assembly in the main maker space work area.  Again, you must be ready to reflow by 1pm.

The TA and I both have other obligations after class after on some days.  This means that if you aren't ready to reflow in time, we may not be able to stay after to reflow your board.

The soldering stations are available for hand-soldering the through-hole parts.  You can work on this whenever the maker studio is open.

## Tips, Tricks, Bells, and Whistles

### Attaching the Motors

The spec for the board, should provide a snug fit for your motors, but the board milling process is not perfectly precise.  Also, the motors are subject to significant stress during testing (as your board bangs around the test stand).  To hold the motors in place, hot glue works well.  Position the motors as you like and apply 1-2 _small_ amount of got glue to the corner formed between your PCB and the motor.   You don't need very much and applying alot will make a mess and make it difficult to remove the motors later.

Do not using anything stronger (e.g., super glue or gorilla glue).  It makes a mess, is too brittle, and is very hard to remove.  Hot glue is really the about perfect.

### "Feet" for Your Quadcopter

It's useful to have something for your quadcopter to stand on so it sits level on the ground.  This is especially handy when you are calibrating your IMU.   You have several options:

1.  You can use the motors.  Position them to ride low, so the bottom extends down a ways, and make sure you put them all at the same height.  The draw back is that wires can get banged around.
2.  3D print something.   Go crazy, but remember that weight is an issue.
3.  A piece of light foam would make a pretty good landing pad.  You can even use part of a household sponge.
4.  The battery can also help here if you mount it underneath.

### Attaching the Battery

The battery is awkward, and it's a hard problem to solve.  Many things can work, but few look great:  Blue tape, rubber bands, velcro.  

One thing that might help is shortening the wiring harness that connects to your quadcopter.  Play around until you find a good length and then trim it short.

We also have some plastic "cages" you're welcome to use.




