# Introduction to Eagle

To be completed on your own. Time is especially short for this lab, please try to work through it before the first day of class.

Check the course schedule for due date(s).

Skills to Learn

1. How to complete the Envision Maker Studio Responsibility Contract.
2. Github basics.
3. Installing Eagle.
4. Creating a schematic in Eagle.
5. Generating a board from a schematic.
6. Designing eagle packages.
7. Designing eagle symbols.
8. Connecting packages and symbols using devices.
9. Modifying an existing schematic.
10. Incorporating new devices into a design.
11. Defining new eagle layers.
12. Adding graphics to a PCB design.

## Equipment, Supplies, and Software You Will Need

1. A computer with Eagle installed (either in the Maker Studio, the basement CSE labs, or your own laptop).
2. The [starter repo](https://classroom.github.com/a/l4ET6aPa) for this lab (Don't clone it until the start of class, last minute changes are likely).
3. The contents of the class materials Github repo: https://github.com/NVSL/QuadClass-Resources

## Tasks to Perform

### Complete the Responsibility Contract

Go to http://makerspace.ucsd.edu/access/responsibility.php and follow the instructions. Print the completion page (it says something like "YOU PASSED!") to a pdf called `responsibility.pdf,` commit it to your repo.

### Fill Out The Self Evaluation

Login to your __@ucsd.edu__ gmail account and fill out [this survey](https://docs.google.com/forms/d/e/1FAIpQLSdY2ymtVFEI_7CQra3eP1GEthNj2aCQCzFrduqjD7a3Ln4OEA/viewform).  You will receive
a copy of your responses via email.  Print it to a pdf and include it in your repo as `survey.pdf`.

### Get set up Github

We are going to use Github classroom for this course. You'll need to [create a Github account](https://github.com/), if you don't already have one. For each part of the project, there will be an assignment setup on Github. You and your teammates will commit your work to the repo in order to turn it in.

First, you'll need to authorize github classroom to access your github account. To do that, visit https://classroom.github.com and sign in with your github account.

Then click on the link for the starter repo listed in the "Equipment, Supplies, ..." section above. (Not able to verify this!)

We will be using Github a lot in class. If you aren't familiar with it, there are a bunch of good introductory tutorials. For example, [this one](http://try.github.io/).

### Install Eagle

Sign up here to get an Autodesk Student account: http://www.autodesk.com/education/free-software/eagle

Download and install Eagle Premium. You may need to purchase a one month subscription.  You can get by without "premium" until you need to layout your board.

### Make Eagle Easier to Use

By default, Eagle comes configured with a bunch of libraries that can make it hard to find the libraries we are using for this class. This is controlled the directories Eagle is setup to look in for library and other files. You can change the directories by selecting `Window->Control Panel` and the selecting `Options->Directories`. I suggest the following settings:

* Libraries: `<path to>/eagle-intro-sp19-<gitusername>/lbr`
* Design Rules: `<path to>/QuadClass-Resources/Eagle/DRU`
* CAM Jobs: `<path to>/QuadClass-Resources/Eagle/CAM`

For instance, for me, the values might be:

* Libraries: `/Users/swanson/cse176/eagle-intro-sp19-stevenjswanson/lbr`
* Design Rules: `/Users/swanson/cse176/QuadClass-Resources/Eagle/DRU`
* CAM Jobs: `/Users/swanson/cse176/QuadClass-Resources/Eagle/CAM`

You should restart Eagle after maring these changes.

### Do the Button and Light Tutorial

Work through these four tutorials on designing and building schematic, boards, and parts in Eagle:

* [Part 1: Creating a Schematic](Creating-A-Schematic.md)
* [Part 2: Creating a board ](Creating-A-Board.md)
* [Part 3: Preparing a board for manufacturing](Preparing-The-Board-For-Manufacturing.md)
* [Part 4: Creating surface-mount parts](Creating-Surface-Mount-Parts.md)

### Getting Art onto the Board

Most board designers include a logo or other artwork on the board, and you will too! Getting artwork into a design is a bit complex. Later in the class, you'll design a logo for your quadrotor and be adding it to your board in the same way.

Here are the steps:

1. For this, we will first begin creating a new library (You can also use the library where you are placing all your new components). Call the library `Logos.lbr`. Put it in the `lbr` directory in your git repo for this lab.

![](images/artwork1_new.png)

2. Go to `Library -> Manage Package` and name this new package UCSD_LOGO, then press OK.

![](images/artwork2_new.png)

3. A new blank page will appear. Go then to `File->Run UPL...` and open the script named `import-bmp.upl`.

![](images/artwork3_new.png)

4. After this, a new message will appear. Press OK. Then search for the bmp image you want to transfer, in this case, we will transfer the UCSD logo. It is recommended that you change the image format to "Monochrome bmp" this means that the image will only have two colors, black and white. You can find the UCSD logo in your GitHub eagle-intro repository with the filename of `UCSD-logos-horizontal.bmp`.

![](images/artwork4_new.png)

5. After selecting the UCSD Logo you will need to choose which color pixels to transfer. For this case select only Black.

![](images/artwork5_new.png)

6. Then select the scale and layer of the image to transfer. For this image use the following parameters.

Format: Scaled

Unit: Mil

Scale: 0.5

Layer: 21

![](images/artwork6_new.png)

7. Select OK, after this a new window will appear, for that windows select `Run script`.

![](images/artwork7_new.png)
![image:https://lh3.googleusercontent.com/YcdkkNKLKyJf67RqU08ilv-10IL8KpCXNO1J4E0Z_Hy3fwpQgy9Nw7ImLgUAhKLY]

8. Now the image should be transferred. 
<!--
You will notice some text below the image (red circle), this is the path of the image. Zoom to it and delete it.
-->
![](images/artwork8_new.png)

9. Save the library as Logos.lbr (if you are using an existing library just click save).

![](images/artwork9_new.png)

10. Click on the ``Add Part`` on the left and select ``Logos.lbr``.
<!--
Now open the Button-and-Light schematic and select `Library-> use`. After this search and open the library Logos.lbr or the library where you saved the logo.
-->
![](images/artwork10_new.png)

<!--
11. Select “Add” for adding an element and search for the UCSD_LOGO.
-->
11. Select OK and finally, you should see the UCSD logo on the board
![](images/artwork11_new.png)

<!--
12. Select OK and finally, you should see the UCSD logo on the board.
![](images/artwork12.png)
-->

## Turn in Your Work

Submit your work via eaglint ( [http://eaglint.nvsl.io](http://www.google.com/url?q=http%3A%2F%2Feaglint.nvsl.io&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNHn3w8dj3XknIOpuPo6FRKP_dkpng) ) and commit all the files list below files to GitHub. Make sure everything is committed to github and visible online. 

Also, create a GitHub Tag for your repository once you’ve done the final commits. Enter this detail in the eaglint submission under “Tag”.

### Rubric

“Perfect” score: 10

Initial points: 15

Checklist:

1. The schematic, board, and CAM files for your through-hole design ( `throughhole.sch, throughhole.brd, throughhole.cam.zip` ). With the artwork.
2. The schematic, board, and CAM files for your surface mount design ( `smd.sch, smd.brd, smd.cam.zip` ).
3. Your modified version of `Lab01.lbr, i.e, Lab01_smd.lbr.`
4. Your `lbr/Logos.lbr`.
5. Your `responsibility.pdf`.
6. Pour `survey.pdf`

You will lose one point for each day late your solution is and one point for each rejected submission to eaglint.  Note that the maximum possible points in 10, but you get start out with 15.  This lets you submit a few full checks to get used to what eaglint is expecting.

