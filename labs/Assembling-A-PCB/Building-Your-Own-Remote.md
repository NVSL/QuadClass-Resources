# Building Your Own Remote

The base model of the remote is what we have in class.  There are several options you can add.

You'll need to order the parts that are required for the remote but not for the breakout board.  To do so:

1.  Go to https://www.digikey.com/ordering/shoppingcart?lang=en
2.  Click `Upload a File` select [QuadRemoteExtras.csv](QuadRemoteExtras.csv).
3.  Column B is the Digikey part number.  Column C is the quantity.  Ordering 1 spare of everything is not a bad idea. 
4.  Complete you order.

For each version of the remote, there's a different bill of materials (BOM).  They are cummulative, so the ones listed later contain the parts for the previous ones as well. 

## Base Model

I'll provide the PCB for your remote.

**Digikey BOM:** [boms/remote.digikey-bom.csv](boms/remote.digikey-bom.csv)

## Bells and Whistles

This option adds a power switch and a built in FTDI.

The builtin-FTDI lets you program the remote _and_ lets you use the remote as an FTDI to program your quad.  Very fancy.  

This requires several additional surface mount components.  It increases the complexity of the lab by a fair amount.   You'll need an special cable to connect your remote to your quadcopter.

Adding this option after you've done the inital assembly and reflow is a good way to practice some more advanced soldering techinques. 

**Digikey BOM:** [boms/remote+pwr+ftdi+gim+lcd.digikey-bom.csv](boms/remote+pwr+ftdi+gim+lcd.digikey-bom.csv)

**Part List**

| Desc               |  URL                                               | Qty | 
|--------------------|----------------------------------------------------|-----|
| FTDI cable       |  **Find URL**       | 1 | 
| USB Micro cable  |  You probably have one of these | 1 |

### Instructions

On the back of the board, there are some jumpers that need to be reconfigured.  See the course staff about how to do it.

## An IMU

It's the same IMU that we use on the quadcopter.  It would, in principle, let you control your quadcopter by tilting the remote.
 
**Digikey BOM:** [boms/remote+pwr+ftdi+gim+lcd+IMU.digikey-bom.csv](boms/remote+pwr+ftdi+gim+lcd+IMU.digikey-bom.csv)


## Nicer Gimbals
 
The base model gimbals are decent, but cheap -- $10/pair.  The nicer ones are are $30/pair.  Will you notice the difference?  But they are pretty cool.

**Part list**

| Desc               |  URL                                               | Qty | 
|--------------------|----------------------------------------------------|-----|
| Nice Gimbals       |  **Find URL**       | 2 |
| 600 Ohm resistor   |  I'll provide       | 1 |

## Display

This adds a fancy RGB backlit 2-line LCD display.  This is a little expensive but easy to add.  You need to solder on a header and screw on the display.

**Part list**

| Desc               |  URL                                               | Qty | 
|--------------------|----------------------------------------------------|-----|
| Display            | https://www.sparkfun.com/products/14072            |  1  |
| 1 1/4 scews        | I'll provide | 4  |


### Instructions

Barely insert the male header into the female header and the attach the display to the remote board using the screws.  You'll need 4 donuts between the LCD and the remote board.
 
Position the headers (without soldering them) so the male header connects to the display, and the female header connects to the remote.  Gently squeeze the two boards together and scew in place.

The headers are now perfectly positioned for soldering.  Solder them to the display and the board.

