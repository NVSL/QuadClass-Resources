# # Lab 08: Tape out

To be completed in your groups.

Check the course schedule for due date(s).

Skills to Learn

1. Prepare CAM files for submission to the manufacturer.
## 

## Equipment, Supplies, and Software You will Need
1. Eagle
2. Your design review documents.
3. Your PCB schematic and layout.
## 

## Tasks To Perform
### 

### Finalizes your Design
This is your final chance to fix any problems. You should perform another design review yourself, after reviewing the checklist in [Lab 07: Finalize schematic, Layout and Routing, and Design Review](/a/eng.ucsd.edu/quadcopterclass/labs/lab-6-layout-and-routing).

You should also be on the look out for any moments when a small voice in your head says “hmm… I’m not sure about that.” When that happens, ask about it on Piazza. Include a screen capture of the relevant parts of your board.

Generate your CAMs. Be sure use `QuadClass-Resources/Eagle/DRU/jlcpcb-4layer.dru` for your design rules check and the `QuadClass-Resources/Eagle/jlcpcb-4layer.cam`. The DRU file affects how the autorouter runs, so you may need to re-route your board. Do a pull in your copy of the QuadClass-Resources repo to get the latest versions. To use the DRU file, open your board then select “Tools->DRC…” then click “Load…”.

If there are any errors fix them, or explain why they are OK using comments in the board file (i.e., text in layer `Document` ).

### 

### Commit Your Final Design
Commit your final design to your github repo. This should include

* Your updated quadcopter.sch and `quadcopter.brd`
* Your final quadcopter.cam.zip. Please be _certain_ that this the right cam files. I suggest deleting all cam files in your repo, regenerating them and zipping them up. Be sure to commit.
* A file called freeDFM.pdf that contains the results of your freeDFM check.
* A file called “metadata.txt” that has the following:

    1. Color you want your quadcopter to be. Choices are: Green, red, white, yellow, blue, or black.
    2. Whether you used `QuadClass-Resources/Eagle/DRU/jlcpcb-4layer.dru or QuadClass-Resources/Eagle/DRU/jlcpcb-4layer-5mil`.dru.
    3. The dimensions of your board in mm.

Submit it via Eaglint. You can expect the reviews to be quite stringent.

### 

### The Ordering Process
YOU DO NOT NEED TO ORDER YOUR BOARD. I WILL DO IT.

Some of you have asked about the ordering process. We are using [https://jlcpcb.com/](https://www.google.com/url?q=https%3A%2F%2Fjlcpcb.com%2F&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNH_V0NL6xoHNSQc88ujSOT1OYcHGw) to build the boards. You need to create an account, and then go to cart and “add item” to place an order.

Basically, you just upload the zip file of your cam files, and select some options, and pay with a credit card. Here are the options we will be using:

* 4 layers
* 5 boards (you’ll get 5 copies of your board)
* thickness 1.6mm
* color: based on your color.txt
* Surface finish: LeadFree HASL
* Copper thickness: 1oz
* Gold fingers: no
* Material: FR4
A list of their capabilities is here: https://jlcpcb.com/capabilities/Capabilities. This is what get transcribed into the DRU file.