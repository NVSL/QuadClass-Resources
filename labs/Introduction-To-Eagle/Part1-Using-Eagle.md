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
## 

## Equipment, Supplies, and Software You Will Need
1. A computer with Eagle installed (either in the Maker Studio, the basement CSE labs, or your own laptop).
2. The [starter repo](https://www.google.com/url?q=https%3A%2F%2Fclassroom.github.com%2Fassignment-invitations%2F05a6bde38fa4241f0019fd08db4d1e99&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNHcxQk8qcHy6V96okJCUYvXzNH9Dw) for this lab (Don't clone it until the start of class, last minute changes are likely).
3. The contents of the class materials Github repo: [https://github.com/NVSL/QuadClass-Resources](https://www.google.com/url?q=https%3A%2F%2Fgithub.com%2FNVSL%2FQuadClass-Resources&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNHVwNlEbmPuH7oR6z5efckdrbfGZw)
## 

## Tasks to Perform
### 

### Complete the Responsibility Contract
Go to [http://makerspace.ucsd.edu/access/responsibility.php](http://www.google.com/url?q=http%3A%2F%2Fmakerspace.ucsd.edu%2Faccess%2Fresponsibility.php&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNEXwNjwtI2H0uCvXE6xHgNPGDlSAQ) and follow the instructions. Print the completion page as a pdf called `responsibility.pdf,` commit it to your repo.

### 

### Get set up Github
We are going to use Github classroom for this course. You'll need to [create a Github account](https://www.google.com/url?q=https%3A%2F%2Fgithub.com%2Fjoin&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNG_iOWiAc2pKXLqaa5f5KHf-qDsBw), if you don't already have one. For each part of the project, there will be an assignment setup on Github. You and your teammates will commit your work to the repo in order to turn it in.

First, you'll need to authorize github classroom to access your github account. To do that, visit [classroom.github.com](http://www.google.com/url?q=http%3A%2F%2Fclassroom.github.com&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNF-j15_lWynYBWg6YYG2WxNLoScjA) and sign in with your github account.

Then click on the link for the starter repo listed in the "Equipment, Supplies, ..." section above.

There's also a course repo at [https://github.com/NVSL/QuadClass-Resources](https://www.google.com/url?q=https%3A%2F%2Fgithub.com%2FNVSL%2FQuadClass-Resources&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNHVwNlEbmPuH7oR6z5efckdrbfGZw). It contains a variety of useful files (e.g., the lecture slides and the configuration files for the PCB design tools).

We will be using Github a lot in class. If you aren't familiar with it, there are a bunch of good introductory tutorials. For example, [this one](https://www.google.com/url?q=https%3A%2F%2Ftry.github.io%2Flevels%2F1%2Fchallenges%2F1&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNEh4cCUyx3fETi0Ihh1On6EqQXpOQ).

### 

### Install Eagle (if you are using your laptop)
Sign up here to get an Autodesk Student account: [http://www.autodesk.com/education/free-software/eagle](http://www.google.com/url?q=http%3A%2F%2Fwww.autodesk.com%2Feducation%2Ffree-software%2Feagle&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNHMOEcicQ-PVFwAVu_lYFIMdTmvIA)

Download and install Eagle Premium. You may need to purchase a one month subscription. You can get by without "premium" until Lab 04.

### 

### Make Eagle Easier to Use
By default, Eagle comes configured with a bunch of libraries that can make it hard to find the libraries we are using for this class. This is controlled the directories Eagle is setup to look in for library and other files. You can change the directories by selecting "Window->Control Panel" and the selecting "Options->Directories". I suggest the following settings:

* Libraries: `<path to>/eagle-intro-<gitusername>/lbr`
* Design Rules: `<path to>/QuadClass-Resources/Eagle/DRU`
* CAM Jobs: `<path to>/QuadClass-Resources/Eagle/CAM`
* User Language Programs: `<path to>/QuadClass-Resources/Eagle/ULP`
If you don't want to replace the defaults, you should at least append these to directories already there.

### 

### Do the Button and Light Tutorial
First, go through the [Button and Light Tutorial](/a/eng.ucsd.edu/quadcopterclass/labs/lab-2-using-eagle/button-and-light). You can skip Part 1, but read it over.

### 

### Getting Art onto the Board
Most board designers include a logo or other artwork on the board, and you will too! Getting artwork into a design is a bit complex. Later in the class, you'll design a logo for your quadrotor and be adding it to your board in the same way.

Here are the steps:

1. For this, we will first begin creating a new library (You can also use the library where you are placing all your new components). Call the library "Logos.lbr". Put it in the `lbr` directory in your git repo for this lab.

[image:https://lh6.googleusercontent.com/rzPAc6wsjTAS02QQG1drhE_uw4d4_fyQusRrpcrtqavnj9trzUHvZwMF06gOvFzOQ_lPuzRWfDI5fzvM7zTzP1v8egywi2O0dV9FWouUQfM6wH0MuYQ=w572]

2. Go to Library -> Package and name this new package UCSD_LOGO, then press OK.

[image:https://lh5.googleusercontent.com/WR99y4ElC5kJKnPY0wYwtjm9BtpUrScuztZ0v0gO4miZUhNnfE_Vi-Bi27Ytg8-EWForMdB0XF4Xsofw4-chLgi2BopNm_-yEFCyzYNVnzCiCqGOQ5U=w572]

3. A new blank page will appear. Go then to File->Run UPL... and open the script named "import-bmp.upl".

[image:https://lh3.googleusercontent.com/tAWxH8sCk6kwtZCzK-3KNAm_ZX7Vw3klvc7AxeXIpCXhDvPdeoni_MMwvl5XasNhyp-YevnLi0J8bNHa8gJDM4g8muBn-rIbQban1BB6Co-Q7qYXXh8=w673]

4. After this, a new message will appear. Press OK. Then search for the bmp image you want to transfer, in this case, we will transfer the UCSD logo. It is recommended that you change the image format to "Monochrome bmp" this means that the image will only have two colors, black and white. You can find the UCSD logo in your GitHub eagle-intro repository with the filename of "UCSD-logos-horizontal.bmp".

[image:https://lh6.googleusercontent.com/aShUyUO_aFt5-4NVSYJ2D5Hpj825KwQQjU9yc23kLKqEsHRsuBBy7q-2IH0xThmwl-5eBlMWn3SiS2nMWBoN3cUtEDXqGaRP_mTtXOcb2AiZngWq9A=w773]

5. After selecting the UCSD Logo you will need to choose which color pixels to transfer. For this case select only Black.

[image:https://lh6.googleusercontent.com/Eic3KDOO4t7tdQSvKoVFNot5mhjp0gXq7swwdEB35i3WYQRMzrUo6dA4IdlWqQ0m9OD2yxC7YrYQfAN__p6OtxwV7pkEynQlwJkPKvvD7nHPqsL8lG_Q=w572]

6. Then select the scale and layer of the image to transfer. For this image use the following parameters.

Format: Scaled

Unit: Mil

Scale: 0.5

Layer: 21

[image:https://lh4.googleusercontent.com/Rkm44GjgEVd8XTKb8fq2oJuCRBqth1ZcpwArryLppKLZ6wYuZ-lwORO0-rtSsAyYfZHr3Mzhm2Xz_2cfQqcvUhnt7CSNifO169hwh5HpsOCYCaCDkTc=w572]

7. Select OK, after this a new window will appear, for that windows select “Run script”.

[image:https://lh6.googleusercontent.com/z1pbMQOhT1UlWP72b2AiayJ2mEtuOKy4NkzDJhalQAmDoZSoGvrb86A7_5DztItvEh03K0ulNTMLilqTOkaalu6-ivN-vZr2civCleEfB_dnlo_yPw=w572]

8. Now the image should be transferred. You will notice some text below the image (red circle), this is the path of the image. Zoom to it and delete it.

[image:https://lh3.googleusercontent.com/P8UsZPqqjAMJbeth5acpl2dOqorwr5Y8ggT2JjQ_K89rrjMtekxSOLE6z3XhwaqzTWL4YxTAH4x776yssRLUvuDN95B3XjyNyQRr_IIk4yjgC2VVoBI=w572]

9. Save the library as Logos.lbr (if you are using an existing library just click save).

[image:https://lh5.googleusercontent.com/S41cvS7y_3FPn_bx93r-P9wMZq8DrrfD2vCtrs3-Z1u0FVMM1N5OIIKj4n8Ou9MAPVJzFKyjURzKa-C6xAPg73Dzhlzqbpi2tJcnhdQKQRMgti6te3U=w773]

10. Now open the Button-and-Light schematic and select Library-> use. After this search and open the library Logos.lbr or the library where you saved the logo.

[image:https://lh4.googleusercontent.com/Jw-rI5R63gfvezkVbyCqqAWuRiJ7eXQzFlkftGBSjtDUYmSE7qnX_Y8kUGZjsoSQD7AHy3qz-MTrO-tO2kefWgUYMuix0vigDVM0XPe_upQoLDIFiw=w572]

11. Select “Add” for adding an element and search for the UCSD_LOGO.

[image:https://lh4.googleusercontent.com/7Ya2Tmbcppv61BghzGVNrksNIKOfVR8a11nZrci3mdv70RW_6bWLeOfbTPxBmCyxeX9e2zfbLqxP8yag9xEKEtzGOF45GQ9JDgSqFxyo_D16ETKKOw=w572]

12. Select OK and finally, you should see the UCSD logo on the board.

[image:https://lh6.googleusercontent.com/KZb_u_3CSi2_Wsp82R8TZhIR_ilr-61ppZjom2pX4zcC1w7GglzWQt0MkHXSofRxBtJrE6_kl44DMTOhFZiRYyjIQgiBaJM_7op0Y2VB7R5p2e5oBis8=w572]

## 

## Turn in Your Work
Submit your work via eaglint ( [http://eaglint.nvsl.io](http://www.google.com/url?q=http%3A%2F%2Feaglint.nvsl.io&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNHn3w8dj3XknIOpuPo6FRKP_dkpng) ) and commit all the files list below files to GitHub. Make sure everything is committed to github and visible online. 

Also, create a GitHub Tag for your repository once you’ve done the final commits. Enter this detail in the eaglint submission under “Tag”.

### 

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