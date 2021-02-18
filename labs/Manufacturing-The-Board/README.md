# Tape out

To be completed in your groups.

Check the course schedule for due date(s).

## Skills to Learn

1. Prepare CAM files for submission to the manufacturer.

## Equipment, Supplies, and Software You will Need

1. Eagle
2. Your design review documents.
3. Your PCB schematic and layout.

## Tasks To Perform

### Finalizes your Design

This is your final chance to fix any problems. You should perform another design review yourself, after reviewing the checklist in the previous lab.

You should also be on the look out for any moments when a small voice in your head says “hmm… I’m not sure about that.” When that happens, ask about it on Piazza. Include a screen capture of the relevant parts of your board.

Follow the guidelines in the board layout lab under the heading "Generating Gerbers" to generate your final cam files.

### Commit Your Final Design

Commit your final design to your github repo. This should include

* Your updated `hardware/quadcopter.sch` and `hardware/quadcopter.brd`
* Your final `hardware/quadcopter.cam.zip`. Please be _certain_ that this the right cam files. I suggest deleting all cam files in your repo, regenerating them and zipping them up. Be sure to commit.
* A file called `hardware/metadata.txt` that has the following:

    1. Color you want your quadcopter to be. Choices are: Green, White, Blue, Black, Red, or Yellow.
    2. Silkscreen colors: White, Blue, Black, Red, Yellow (different than your board color).
    3. The dimensions of your board in mm.

Submit it via Eaglint. You can expect the reviews to be quite stringent.

### The Ordering Process

**YOU DO NOT NEED TO ORDER YOUR BOARD. I WILL DO IT.**

This is just here for your information.

Some of you have asked about the ordering process.  We are using https://www.pcbcart.com/. To build the boards, you need to create an account, and then go to cart and “add item” to place an order.

Basically, you just upload the zip file of your cam files, and select some options, and pay with a credit card. Here are the options we will be using:

* 4 layers
* 5 boards (you’ll get 5 copies of your board)
* thickness 1.6mm
* color: based on your `metadata.txt`
* Surface finish: LeadFree ENIG
* Copper thickness: 1oz
* Gold fingers: no
* Material: FR4

A list of their capabilities is here: https://www.pcbcart.com/pcb-fab/standard-pcb.html. This is what get transcribed into the DRU file.

You can order a stencil as well (based on your `.crm` gerber).  However, I usually order stencils from https://www.oshstencils.com/.  They are smaller and a little easier to work with.

We have also had good results with https://jlcpcb.com/.
