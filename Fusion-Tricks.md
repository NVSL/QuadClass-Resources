# Eagle Tips and Tricks and Recipes

Here are some useful commands for working in Fusion 360.  For the commands that go in the command line window, pay attention to "@" and ";" -- change the meaning of some commands significantly.

In all cases, you'll either need to click in the command line panel (Above the main part of the window) or (much faster) type `/`.

## Get Help

1. `help info` -- get documentation about `info`
2. `help move` -- get documentation about `move`
3.  etc.

## Finding Parts

1.  `show C1` -- Highlight `C1`
2.  `show C2` -- highlight `C1` and draw a box around it.

## Working with Layers

1.  `display none` -- hide everything.
2.  `display all` -- show everything.
3.  `display none tplace tnames` -- show just `tplace` and `tnames`.
4.  `display all -tplace` -- show everything but `tplace`

## Placing and Moving Parts

1.  `move c1` -- start moving `C1`.
2.  ctrl-click to rotate the part.
3.  `grid mm; grid 1` -- set grid for part placement.
4.  `grid mm; grid 0.5` -- set grid for reference designator and value placement.
5.  `move;`  -- then select parts with `group` tool.  Ctrl-click and select `move: group` to move the group.
6.  command-click (on my mac; not sure on windows) -- snap to grid.
7.  `move` then shift-click -- move a whole polygon.
8.  `grid mm; grid 0.85` -- move items by 0.85mm

## Setting Properties

1.  `change width 10mil` -- change wire widths to 10mil by clicking on them.
2.  `change align center` -- change alignment of text items to 'center'
3.  `display none tplace tdocument tnames`, select all (command-A), `change align center`, right-click select "Change: group" -- change alignment of all reference designators and values.

## Quickly Laying Out SMDs and Pads

Example:  Create a row of 6 SMDs at 0.7mm pitch at 0.8mm above the origin. 

1.  `grid mm`
2.  `grid 0.7`
3.  Place the SMDs in a row starting at (0, 0).
4.  `grid 0.8`
5.  Select all the SMDs.
6.  Group move them up one grid square (0.8mm)
7.  `grid 0.21`
8.  Select all SMDs
9.  Group move them to the lift one grid square (6 * 0.7/2 = 0.21mm).

## Routing 

1.  `route` -- start routing.  Select particular router from tool bar. "walkaround obstacles" is a good default.
2.  `route gnd` -- start routing `GND`
3.  `fanout device U1` -- fanout `U1` by adding stubby wires and vias to the pins on `U1`
4.  `fanout signal GND` -- fanout `GND` by adding stubby wires and vias to all the pins on `GND`
5.  `auto` -- Open the auto router configuration window.
6.  `auto;` -- just run the auto router.
7.  `ripup;` -- ripup (unroute) all nets.
8.  `ripup GND` -- Just ripup `GND`.
9.  `ripup ! GND` -- Ripup everything but `GND`.
10. `ripup @;` -- Draw pours as polygons.
11. `ratsnest` -- Recompute unrouted nets and fill in pours.
12. `ripup ! RFN RFP CLK_POS CLK_NEG; fanout signal GND BAT_GND 3V3 VBAT; auto;` -- Reroute your board (tweak to suit your design.)

## Create a Pour

1. Draw a polygon in the metal layer you want the pour in (e.g., `Top).
2. Set the signal you want the pour to carry (either in the pop-up that appears when you finish drawing the polygon or by `info` to set properties of the polygon).

## Create a Cutout in a Pour

1.  Draw a polygon in the metal laye you want the cutout in.  Use `info` to set the 'Polygon pour' property to `cutout`.

## Checking and Fixing Designs

1. `drc` -- inspect and configure design rule check settings.
2. `drc;` -- Just run DRC.
3. `display none unrounted` -- Just show unrouted nets.
