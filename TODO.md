## Future Updates for Fusion360

1.  Update Lib01.lbr and associated parts to have 3D models.


## Preclass Tasks


1.  The assembly labs requires us to provide students with part kits.  To do this we provide labeled, pre-cut portions of 
part tapes.  We need part portions for both the practice assembly lab and the quad assembly lab.
2.  Practice assembling a BBB, a FCB, and a remote.  Learn the following:
    1.  How to set up paste station
    2.  How to apply paste
    3.  How to reflow
    4.  How to rework
    5.  How to bring up
3.  Become familiar with part organization.
4.  Run something through eaglint.
5.  Do the first lab.


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

8. Do Lab 1 and update the screen caps.
9. Do Lab 1 and check that git@github.com:NVSL/QuadClass-Eagle-Intro-Solution.git is a solution that matches the lab.  In particular, cam generation has changed significantly.  Have them commit a zip file of their cam file.  Run the solution to eaglint to make sure. 
2. Make labels for each component type with space to write qty.
3. Prepare part strips for BBB assembly.
6. Collect all the data sheets for quadparts_prebuilt.lbr.  Put them in the resources repo.
10. Dismantle old remotes
0. Build a remote
1. Build an FCB


Tasks

1.  Set student count
1.  Laser cut remote 
2.  Laser cut test stands.
2.  Order lots of stuff
3.  Move layer label part into quadparts_prebuilt.  Require it's presence in the design.
5.  Remember to handout research release form at the beginning of class.
6.  include major, year, etc. and demographics on both the pre-survey and the post-survey
7.  Ask the "can you do X" questions on the presurvey.
8.  Do a survey on the first day, and another in two weeks to see who you lost.
9.  Label stencils
10.  

Next Time:

Generate unified BOM:

python ../../Eagle-Lint//server/eaglint/BOM.py --sch controller_board_cheap.sch ../../QuadClass-Quadcopter-Solution/flight_control_board.sch --format csv --out controller_board_cheap.digikey-bom.csv --qty 45 30 --extra 0.2

## Future Years

1. Eliminate the bridge and draw the ground plane to make the ground return from the voltage regulator clean. 
2. Replace the vreg on the remote with a combined charger/LDO. 
3.  Integrate skill inventory into application.  It might help tell whether I could offer this to juniors


