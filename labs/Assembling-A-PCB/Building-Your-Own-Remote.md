# Building Your Own Remote


The base model of the remote is what we have in class.  There are several options you can add.

## Electrical Components

You'll need to order the parts that are required for the remote but not for the breakout board.  To do so:

1.  Go to https://www.digikey.com/ordering/shoppingcart?lang=en
2.  Click `Upload a File` select [remote.digikey-bom.csv](boms/remote.digikey-bom.csv).
3.  Column B is the Digikey part number.  Column C is the quantity.  Ordering 1 spare of everything is not a bad idea. 
4.  Complete you order.

## Mechanical Components

Items with a "*" I can provide, since I buy them in bulk.

| Desc               |  URL                                               | Qty | 
|--------------------|----------------------------------------------------|-----|
| FTDI cable       |  https://www.adafruit.com/product/206       | 1 | 
| USB Micro cable  |  You probably have one of these | 1 |
| Display            | https://www.sparkfun.com/products/14072            |  1  |
| LCD mount screws	1 1/4 in | 	https://www.mcmaster.com/90272a087 | 4 *| 
| Gimbal screws	1 1/2 in |	https://www.mcmaster.com/90272a088 | 8 *|
| Nuts for gimbals and PCB	|	https://www.mcmaster.com/90480a003 | 12 *| 
| Servo cable 	| https://www.amazon.com/gp/product/B01J81HQ9Y | 2 *|
| 3/8" spacer | https://www.mcmaster.com/94639a709 | 4 * |
| 1/2" spacer | https://www.mcmaster.com/94639a713 | 4 * |
| 1" spacer |  https://www.mcmaster.com/94639a667 | 8 * |
| Battery cable | https://www.alibaba.com/product-detail/Wholesales-explosion-proof-2-pin-Molex_60813679908.html?spm=a2700.7724838.2017115.357.357674c1etkkOn | 1 *|
| Baseplate | na | 1 * |

## Gimbals

These are a little harder.  They are frequently out of stock.  They are also different than the ones on the remote I loaned you.  Unfortunately, those gimblas have been discontinuned.

| Desc | URL | Qty | 
|------|-----|-----|
|Gimbal (L) |https://hobbyking.com/en_us/turnigy-9x-9ch-transmitter-replacement-throttle-rudder-gimbal-1pc.html|	hobbyking|
|Gimbal (R) |https://hobbyking.com/en_us/turnigy-9x-9ch-transmitter-replacement-elevator-aileron-gimbal-1pc.html|	hobbyking|


## Assembling the Display

The remote includes a female header on the board that connects to a male header on the display.  Soldering the headers so they align is tricky, but there's a trick:

Barely insert the male header into the female header and the attach the display to the remote board using the screws.  You'll need 4 donuts between the LCD and the remote board.
 
Position the headers (without soldering them) so the male header connects to the display, and the female header connects to the remote.  Gently squeeze the two boards together and scew in place.

The headers are now perfectly positioned for soldering.  Solder them to the display and the board.

