# Part 4: Creating Surface Mount Components

The design we have so far for the flashlight uses "through hole" parts. This means that the pins for the part protrude through the board and are soldered into place by filling the hole with solder. Through hole parts are easy to work with, but they are bulky and drill so many holes through the board makes it harder to route more complex boards since the parts effectively occupy space on all the layers of the board (front, back, and any internal wiring layers).

Most modern PCBs use "surface mount" (also called SMD) parts that more compact and only require connections to one side of the board. They are also harder to solder. Many of the components we will use are only available as surface mount, and many components are available as both surface mount and through hole.

The course style guidelines for libraries are in the "Guidelines for Building..." section of [this lab](https://github.com/NVSL/QuadClass-Resources/blob/master/labs/Building-Parts-In-Eagle/README.md).  Read and follow them.  Eaglint will complain if you don't.

## Creating a Surface Mount Device

We will replace the through hole button with a surface mount version. We will use part number 1301.9315 from this [datasheet](http://www.google.com/url?q=http%3A%2F%2Fwww.schurter.ch%2Fbundles%2Fsnceschurter%2Fepim%2F_ProdPool_%2FnewDS%2Fen%2Ftyp_6x6_mm_tact_switches.pdf&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNHtExOlXG7xE7EsTttPKfa7a4eS0w). It's the one that looks like this:

![](images/smd1.jpg)

Adafruit has a very nice [tutorial about building new schematic symbols, packages, and devices in Eagle](https://www.google.com/url?q=https%3A%2F%2Flearn.adafruit.com%2Fktowns-ultimate-creating-parts-in-eagle-tutorial%2Fintroduction&amp;sa=D&amp;sntz=1&amp;usg=AFQjCNGsUFLtnS_nmz4ra63XcImFHoVf9A). However, since this tutorial's release, Eagle has been ported over to Fusion360. Autodesk has released several tutorials on how to design custom parts, which can be found [here (~15 min)](https://www.youtube.com/watch?v=zqar0XWtFaY) and [here (~45 min)](https://www.youtube.com/watch?v=xNIEXCimRSg&list=PLmA_xUT-8UlKE-U-eEqrkNEI7rd1fUnLY).


Go through any tutorial using our desired tactile button. We recommend the more recent ones from Autodesk, but should you choose the written tutorial, some Fusion360 notes can be found below. The datasheet required is present in your Lab 01 repository. Make a copy of `Lab01.lbr` called `Lab01_smd.lbr` and create the button there. Create a new footprint, device, and symbol for the button.

### Adafruit Tutorial Fusion360 Updates

#### Creating a New Package

The editors for creating devices, symbols, footprints and packages can be found in the `Create` tab of the library editor. Once you open `Lab01_smd.lbr` in Fusion360, you should be able to see these options:

![](images/adafruit1.png)

Creating packages in Fusion360 is completely different from Eagle; because Fusion360 is a 3D modeling software, packages have now been upgraded to utilize this. **You should not create a package for this lab**, instead create a footprint by hand using the help of one of the tutorials (see below for Adafruit updates).

#### Creating a Footprint

Footprint editing in Fusion360 is similar to what is detailed in the Package section of the Adafruit tutorial. The important tools you need have all been added to the toolbar at the top of the screen, and should you be unable to find a particular tool you can always use the command line. For more information on editing a footprint in Fusion360 check out [this video](https://www.youtube.com/watch?v=8-tJZHFzWXo&list=PLmA_xUT-8UlKE-U-eEqrkNEI7rd1fUnLY&index=3).

To add a footprint to a device, click on the device in the library editor, select `New->Local Package` and locate your footprint in the list. (The footprint in this screenshot has several style errors, your footprint will look different)

![](images/adafruit3.png)


#### Creating a Symbol

Symbol editing in Fusion360 is mostly the same as what is detailed in the Adafruit tutorial, and just like the footprint, the crucial tools are in the header. However, once you have finished creating your symbol, connecting it to the device is a little different. If you go back to the library editor and examine the device, you should find that you can add a part to the symbol layer on the left. Locate the symbol you just created to add it to the device!

![](images/adafruit2.png)

#### Creating a Device

The device editor, just like the other steps have mostly gotten a cosmetic refresh. Important buttons are outlined above and below, and otherwise the Adafruit tutorial is good to go through for final steps!

### Reading Datasheets
Interpreting datasheets takes some practice. Here are some tips:

* The datasheet includes data on many switches. Make sure you are looking at the correct part of the sheet.
* There are several mechanical drawings. For creating a footprint, you are interested in solder pad layout (in the "Drilling diagrams" section, since most of the drawings are for throughhole parts).
* Don't assume drawings are for scale. Instead, use the numerical values given.
### 

### Additional Requirements for Your Footprint
The footprint should be called `SCHURTER-1301.9315`, the symbol should be called `TACTILE-BUTTON`, and the device should be called `TACTILE-BUTTON`, and the variant should be called `SHURTER-1301.9315`.

Name the pins to match the PCB layout drawing in the data sheet, and orient your footprint to match the drawing as well. This is a good practice because it makes it easy to see that your footprint matches the drawing.

Make sure that the length of your smds in the long dimension, and the width is the shorter dimension.

### 

### Additional Requirements for Your Symbol
Your symbol should have just two pins (whereas the symbol you used in your throughhole schematic had 4). They should be called `A` and `B`, and pressing the button should connect them electrically.

Note that your footprint has four SMDs. You'll need to connect two SMDs from the footprint to a single pin in symbol. You do this in the "Connect" dialog. Just select one pin and two pads, and click connect.

![](images/symbol.png)

### 

### Additional Requirements for Your Device
There are a few other things you'll need to be sure of in the footprint you build:

* You need two add three "attributes" to the new variant you created, which can be edited using the `Attribute` button on the device screen (see below screenshot):

	* "DIST" for distributer. This is where we buy the part from. You can put "NA"
	* "DISTPN" for distributor part number. You can put "NA"
	* "CREATOR" This should be your name, since you created the variant.
	* You can add attributes by clicking on "attributes" in the device editor window:

![](images/smd2_f360.png)

* You also need to be sure to draw a box around your footprint in layer ‘tKeepout’.
* You need to add a text item in layer “tName” that contains “>NAME”. This will be replaced with the parts name. To render clearly, the next needs to be at least 0.9 mm high, have a weight of 8% and be in the “vector” font. You can set these parameters in the tool bar at the top of the window or by using the “info” tool to change the attributes of the text after you create it.
## 

## Replacing the Through-hole Component
You can use your new SMD button just like our own through-hole button. Just delete the old button and replace it with your new button.

## 

## Fixing up the Board
Since you just changed the footprint for the button, the board will need to be updated. Traces will probably be crossed, etc.:

![](images/sm3_f360.png)

To fix this, we’ll rip up all the old traces and reroute the board. Use the “group” tool: To select everything on the board.

![](images/sm4_f360.png)

Next, select the `Ripup` tool. Everything will appear to be deselected, that’s ok. Now, right-click on the board, and select “Ripup: Group”. All of the routed traces will disappear:

![](images/sm5_f360.png)

Now, you need to re-route the board using the `Autorouter` tool:

![](images/sm6_f360.png)

which will result in a nice, fully-routed board!

![](images/sm7_f360.png)

## Re-running the CAM Processor
Follow the instructions for running the CAM processor given above. In the Gerber viewer, you can find the pads for the SMD button the in the GTL layer. If you check the GBL layer, you’ll notice that while the pins for all the through hole parts appear on the bottom of the board, the pads for the surface mounted component does not.    

Once you've done everything, you're ready for the [final steps](README.md#getting-art-onto-the-board): adding artwork and exporting!
