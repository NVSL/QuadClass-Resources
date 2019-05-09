# Assembling Your Quadcopter

Assembling your quadcopter is similar to assembling the BBB board, but more involved because there are more components.

You should re-read the [BBB assembly lab](Readme.md).  Everything there applies here as well, including the suggested order for assembly.  Below are just the differences.

If you want to build a remote to keep, here are [the instructions](Building-Your-Own-Remote.md).

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

| Part              | Qty | Picture                                            |
|-------------------|-----|----------------------------------------------------|
| MOSFET            | 4   | ![Resistor](images/resistors.jpg).                 |
| Polarized Caps    | 5   |                                                    |
| IMU               | 1 | | 
| 10KOhm Resistors | 6 | |
| 0.01uF Capacitor | 1 | |
| Diode            | 4 | | 

### Through Hole Parts

| Part              | Qty | Picture                                            |
|-------------------|-----|----------------------------------------------------|
| Motor Sockets     | 4   | |


## Assembly Drawings

Eagle provides a simple mechanisms to help you place parts.  Open your `.brd` file.  You need to enable  the "Design Manager" (`View->Design Manager`).

The "Devices" pane shows a list of all the parts in your design.  Sort the list by "value" and hide the other columns (wrench icon).

You can now select all the parts of a given type and Eagle will highlight their location on the board.

## Time Management

Assembling your boards will take longer than the BBB, because there are more parts, and class time is limited.  To ensure you have time to apply paste, place parts, and reflow the boards, you must start applying paste **at the beginning of class**.  

We will have stations set up for applying paste at 10am on days we are doing assembly for this purpose.

This means you need to have your part kit completely assembled **the class period before**.  If your part kit is not ready at the starte of class, we will not let you start assembly that day.

You also need to work quickly.  Your quadcopters have between 70 and 100 parts (vs 30 for the BBB), and you need to complete assembly at least 1 hour before the end of class (2pm).  This means you need to be placing 1 part ever 30-45 seconds or so.  Keep an eye on the clock.

## Scheduling

On assembly days, the TA will set have parts out by 10am and paste assembly stations ready by 10:30.

On Tuesdays, you must have boards ready for reflow by 1pm. 

On Thursdays, we have to vacate the room by 1pm.  I would suggest starting (and finishing) assembly in the main maker space work area.  Again, you must be ready to reflow by 1pm.

The TA and I both have other obligations after class after on some days.  This means that if you aren't ready to reflow in time, we may not be able to stay after to reflow your board.

The soldering stations are available for hand-soldering the through-hole parts.  You can work on this whenever the maker studio is open.

