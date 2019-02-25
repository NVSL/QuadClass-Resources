

IMU and mosfets missing from FCB bom
Notes about orientation of Balun and diodes and LEDs
Use your magnifier
Solder is a little spares on MOSFET pads
Drop your parts to get them oriented right

folds over to the right.  Keep that space clear
Tools on the left
Put stencil in "portrait" orientation
clean up stencil with alcohol

assembly equipment

blue tape
tweezers
putty knives
alcohol
chem wipes
butcher paper
gloves
scissors
spray adhesive
magnifire
compressed air

Soldering equipment

blue tape
alcohol
brushes
swabs
solder
flux
chemwipes


TA Tasks

0. Build a remote
1. Build an FCB
2. Make labels for each component type with space to write qty.
3. Prepare part strips for remote control assembly.
4. Take inventory.
5. Cut bulk components into strips of ~100 and label.  Put into bags.
6. Collect all the data sheets for quadparts_prebuilt.lbr.  Put them in the resources repo.
7. Assemble the gimbals + wiring harnesses
8. Do Lab 1 and update the screen caps.
9. Do Lab 1 and check that git@github.com:NVSL/QuadClass-Eagle-Intro-Solution.git is a solution that matches the lab.  In particular, cam generation has changed significantly.  Have them commit a zip file of their cam file.  Run the solution to eaglint to make sure. 


Tasks

1.  Set student count
1.  Laser cut remote kits
2.  Order lots of stuff
3.  Move layer label part into quadparts_prebuilt.  Require it's presence in the design.
5.  Remember to handout research release form at the beginning of class.
6.  include major, year, etc. and demographics on both the pre-survey and the post-survey
7.  Ask the "can you do X" questions on the presurvey.
8.  Do a survey on the first day, and another in two weeks to see who you lost.

Next Time:

Generate unified BOM:

python ../../Eagle-Lint//server/eaglint/BOM.py --sch controller_board_cheap.sch ../../QuadClass-Quadcopter-Solution/flight_control_board.sch --format csv --out controller_board_cheap.digikey-bom.csv --qty 45 30 --extra 0.2

## Future Years

1. Eliminate the bridge and draw the ground plane to make the ground return from the voltage regulator clean. 
2. Replace the vreg on the remote with a combined charger/LDO. 
3.  Integrate skill inventory into application.  It might help tell whether I could offer this to juniors


