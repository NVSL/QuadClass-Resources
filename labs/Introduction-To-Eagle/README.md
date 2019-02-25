# Introduction to Eagle
# Lab 01: Using Eagle

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
2. The [starter repo](https://www.google.com/url?q=https%3A%2F%2Fclassroom.github.com%2Fassignment-invitations%2F05a6bde38fa4241f0019fd08db4d1e99&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNHcxQk8qcHy6V96okJCUYvXzNH9Dw) for this lab (Don't clone it until the start of class, last minute changes are likely).
3. The contents of the class materials Github repo: [https://github.com/NVSL/QuadClass-Resources](https://www.google.com/url?q=https%3A%2F%2Fgithub.com%2FNVSL%2FQuadClass-Resources&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNHVwNlEbmPuH7oR6z5efckdrbfGZw)
## Tasks to Perform

### Complete the Responsibility Contract

Go to [http://makerspace.ucsd.edu/access/responsibility.php](http://www.google.com/url?q=http%3A%2F%2Fmakerspace.ucsd.edu%2Faccess%2Fresponsibility.php&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNEXwNjwtI2H0uCvXE6xHgNPGDlSAQ) and follow the instructions. Print the completion page as a pdf called `responsibility.pdf,` commit it to your repo.

### Get set up Github

We are going to use Github classroom for this course. You'll need to [create a Github account](https://www.google.com/url?q=https%3A%2F%2Fgithub.com%2Fjoin&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNG_iOWiAc2pKXLqaa5f5KHf-qDsBw), if you don't already have one. For each part of the project, there will be an assignment setup on Github. You and your teammates will commit your work to the repo in order to turn it in.

First, you'll need to authorize github classroom to access your github account. To do that, visit [classroom.github.com](http://www.google.com/url?q=http%3A%2F%2Fclassroom.github.com&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNF-j15_lWynYBWg6YYG2WxNLoScjA) and sign in with your github account.

Then click on the link for the starter repo listed in the "Equipment, Supplies, ..." section above.

There's also a course repo at [https://github.com/NVSL/QuadClass-Resources](https://www.google.com/url?q=https%3A%2F%2Fgithub.com%2FNVSL%2FQuadClass-Resources&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNHVwNlEbmPuH7oR6z5efckdrbfGZw). It contains a variety of useful files (e.g., the lecture slides and the configuration files for the PCB design tools).

We will be using Github a lot in class. If you aren't familiar with it, there are a bunch of good introductory tutorials. For example, [this one](https://www.google.com/url?q=https%3A%2F%2Ftry.github.io%2Flevels%2F1%2Fchallenges%2F1&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNEh4cCUyx3fETi0Ihh1On6EqQXpOQ).

### Install Eagle (if you are using your laptop)

Sign up here to get an Autodesk Student account: [http://www.autodesk.com/education/free-software/eagle](http://www.google.com/url?q=http%3A%2F%2Fwww.autodesk.com%2Feducation%2Ffree-software%2Feagle&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNHMOEcicQ-PVFwAVu_lYFIMdTmvIA)

Download and install Eagle Premium. You may need to purchase a one month subscription. You can get by without "premium" until Lab 04.

### Make Eagle Easier to Use

By default, Eagle comes configured with a bunch of libraries that can make it hard to find the libraries we are using for this class. This is controlled the directories Eagle is setup to look in for library and other files. You can change the directories by selecting "Window->Control Panel" and the selecting "Options->Directories". I suggest the following settings:

* Libraries: `<path to>/eagle-intro-<gitusername>/lbr`
* Design Rules: `<path to>/QuadClass-Resources/Eagle/DRU`
* CAM Jobs: `<path to>/QuadClass-Resources/Eagle/CAM`
* User Language Programs: `<path to>/QuadClass-Resources/Eagle/ULP`
If you don't want to replace the defaults, you should at least append these to directories already there.

### Do the Button and Light Tutorial

First, go through the [Button and Light Tutorial](/u/0/s/1IuX0W0yU927FV17T9oKIwSXL3K-6dO6n/p/0B48GsO9wiGeRU3RqWmxZRFVkNHM/preview). You can skip Part 1, but read it over.

### Getting Art onto the Board

Most board designers include a logo or other artwork on the board, and you will too! Getting artwork into a design is a bit complex. Later in the class, you'll design a logo for your quadrotor and be adding it to your board in the same way.

Here are the steps:

1. For this, we will first begin creating a new library (You can also use the library where you are placing all your new components). Call the library "Logos.lbr". Put it in the `lbr` directory in your git repo for this lab.

[image:https://lh3.googleusercontent.com/yogVKtX_fl8D8PYwQQH_y6pyT3k7hCxwaS0_CXHTdFoTotD2dgxNPQiGFI_YALiG]

2. Go to Library -> Package and name this new package UCSD_LOGO, then press OK.

[image:https://lh6.googleusercontent.com/HzGifHWif79r9UZnyhm4harlHuZrFk_1HUl2CnQIB7x473Z-oE_iqziHu8UdqW5o]

3. A new blank page will appear. Go then to File->Run UPL... and open the script named "import-bmp.upl".

[image:https://lh5.googleusercontent.com/7l5qxFfsD5h64A-vQ24krSrhOKWD_Pg-tsgx2vee1TzJQTS8T0PegrJALkwidvfl]

4. After this, a new message will appear. Press OK. Then search for the bmp image you want to transfer, in this case, we will transfer the UCSD logo. It is recommended that you change the image format to "Monochrome bmp" this means that the image will only have two colors, black and white. You can find the UCSD logo in your GitHub eagle-intro repository with the filename of "UCSD-logos-horizontal.bmp".

[image:https://lh4.googleusercontent.com/HFNWhrL5a3LEAn481lHemXrNea6LoNmWRCW3vCY-hfiTyJQ8dZYL0TU67hCKp3yE]

5. After selecting the UCSD Logo you will need to choose which color pixels to transfer. For this case select only Black.

[image:https://lh6.googleusercontent.com/FsPl_cyucdFZ3J1No3QNWDPjR2Q3q20VKWk09krEDMbkICw7FAG-Wo--3poI0tfU]

6. Then select the scale and layer of the image to transfer. For this image use the following parameters.

Format: Scaled

Unit: Mil

Scale: 0.5

Layer: 21

[image:https://lh6.googleusercontent.com/oINvXeLDQip8IDNW6MiEbOzPJ5m_mh4SEoeIWxFfhHq1n-zfWXG1dsjD-zEqLJmV]

7. Select OK, after this a new window will appear, for that windows select “Run script”.

[image:https://lh3.googleusercontent.com/YcdkkNKLKyJf67RqU08ilv-10IL8KpCXNO1J4E0Z_Hy3fwpQgy9Nw7ImLgUAhKLY]

8. Now the image should be transferred. You will notice some text below the image (red circle), this is the path of the image. Zoom to it and delete it.

[image:https://lh5.googleusercontent.com/bv6WMgqiO8uh3_UNrJ4ABKDbug3Aq37dIJjW9_f_67QAYSY-26Vin4EjAgnsDIV1]

9. Save the library as Logos.lbr (if you are using an existing library just click save).

[image:https://lh5.googleusercontent.com/viAqgFCMj6kxfknu0HYWxfD1jw-P5-DjMNXcGI9TUOSwc2gUrqzz7t40MV_sr1m6]

10. Now open the Button-and-Light schematic and select Library-> use. After this search and open the library Logos.lbr or the library where you saved the logo.

[image:https://lh4.googleusercontent.com/7FVMqc-6-QXwX9wlOVs_u2-Hdd9gG3ec4bxzFi3v3BuE5ScupVF95Poh1DXT676t]

11. Select “Add” for adding an element and search for the UCSD_LOGO.

[image:https://lh3.googleusercontent.com/Wtf-XJJghD6nucEdiOmO9lv6hrw0jmQ_T98ZEnagCXV1Ew5_dYVT_3lTvqirg93o]

12. Select OK and finally, you should see the UCSD logo on the board.

[image:https://lh5.googleusercontent.com/RAENfU8HvXGa3UK9xrQe-DYr9UiH9gCj9mxXWCPSYCgHeTw83KMqidie3aFonrMr]

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
5. A PDF of the report from FreeDFM showing that your design passed called `freedfm.pdf`.
6. Your `responsibility.pdf`.
You will lose one point for each day late your solution is and one point for each rejected submission to eaglint.

