# Part 2: Quadcopter HW debugging and Motors rotation

## 

## Debugging your quadcopter hardware
Before moving to MultiWii is highly recommendable to test the hardware in your quadcopter and see if everything works.

* *Testing IMU:*

    * Some of your designs have the low-order bit of the IMU I2C address set incorrectly. You can change the values the library uses by changing `LSM9DS1_ADDRESS_ACCELGYRO` in `Adafruit_LSM9DS1.h`. For some of you the IMU seems to be reporting the wrong ID as well. You can disable this check in `Adafruit_LSM9DS1.cpp` look for `LSM9DS1_XG_ID`. You’ll probably need to disable the check on `LSM9DS1_MAG_ID` too.

* *Testing Antenna:*
* You can use the code you did for Lab1 or you can move on to Multiwii, install the code and test it with the controller.
* *Testing LEDs:*

    * Make a code for turning on and off the LEDS.

* *Testing* *Motors:*

    * Make a code for testing the motors.

Just for the reference here are the pinouts of the ATmega128RFA1 chip and the numbers in Arduino.

[image:https://lh3.googleusercontent.com/Y-g-L73snOodRgEldgMqoe6ZkE8HG2E9gaV6Dzdi6jYx83d-sB-QP6XNzDjoGwq-7iR392esXOIleYe5_OIb4UZCEGeV_r1Y0PgZhrV2A9kyVv5TjLU=w371]

## 

## Connecting the Motors
The proper way of connecting is the following:

[image:https://lh6.googleusercontent.com/Udl2DeEpNyP6dQ8fEz-RLj-oiEe32Y_gbZe2rgo36ftyuY-uYHG6NjrNH1-W-WyVhS_R_edBquHyBHo3qT8ogQRrjCrvrM5WJWKGY6VzKYvwgfqC9HY=w673]

Depending on your Quadcopter configuration (Quad + or Quad X) connect the motors so that the above picture match.

Check your schematic to figure out which pin of the connector is the positive and which one is negative.

[image:https://lh6.googleusercontent.com/5aGaMqNbBq0CTBH3FEu3-_WgT2El_n9up7iqOvvy34DylCeBS4ww7qkAEeE8xfh9YAnAo2nQiIxwplMkVLGj-BiH08DTkNwuzSFGxCnuPnhBGH9O2TY=w170]

If you switch the polarity of the cables your motor is going to spin in the opposite direction and contrary to the brush inside the motor therefore reducing the life of the motor. That is why there exists two types of motors (CW and CCW).

## 

## Propellers
There are two types of propellers (CW and CCW). When inserting the propellers to the motors just make sure that the motors trow air to down and not up. Also propellers can come in different colors, is common to place different colors at the front and back of your quadcopter to know the orientation when it is flying.

[image:https://lh4.googleusercontent.com/m_oq1LI_hATVSxeVcqnpruCNJ5CESinBkgc32T9WAJ6Aa5gUfhQjtpXtC_OJOs0j954Ys0B-ZLXjJV_FZHb7IjceEdLDrKEXaQAISViopxvt4Z-G0Hg=w673]

# Part 3: Flight Control

## 

## Tasks to Perform (Part Lab06c): Flight Control Features
### 

### Implement Control Features
You need to implement the following features in your quadcopter firmware

Arm

When you power up your quadcopter it should be “disarmed.” This means that it will not respond to the remote. This is safety feature (to prevent the props from running unexpectedly) and an opportunity to calibrate your sensors.

A common way to arm a quadcopter is to hold the throttle at zero and the roll gimbal all the way to one side or the other and wait a few seconds. You can use whatever method you like, but it must include the throttle being at zero.

It’d be nice to indicate when the quad is armed by flashing a light or something.

Calibrate your IMU

When the quadcopter boots, it should calibrate the IMU. You should assume that the quadcopter is sitting on something level and check the measurements from the IMU to account for any offsets. Your quadcopter should refuse to arm itself until it’s calibrated.

It’d be nice to have a light that shows when it’s calibrating and/or when it’s ready to be armed.

## 

## Complete The Flight Controller
The code you wrote for the test stand should be more or less ready to run on your quadcopter. In theory, the only changes you should need to make to get flying (but maybe not steering) are to update the pin assignments for your motors, re-tune the PID values, and add a PID channel for roll (assuming you were working on pitch on the test stand). For full flight control you’ll need to add a PID channel for and yaw.

### 

### Tuning the PID Values
The process is same as it was for the test stand, with a few small changes.

1. Your quadcopter probably has more power than your test stand because the power delivery system is cleaner (your nice big power/ground planes are much better than the skinny wires on the test stand)
2. The mass and balance of your quadcopter is different than the test stand.
Both of these mean that the correct PID values for your quad are probably different than those for the test stand.

You can tune the values by attaching your quadcopter to the test stand. To do this, you can pull the pivot platform off the axel and attach your quad using tape or zip ties (available in the maker studio).

### 

### Adding the Roll PID Channel
The PID control for roll works the same as for pitch. In theory, if your quad is symmetric the PID values should be the same too. I would check by rotating the quad on the test stand and seeing how stable it is.

Once you have the roll channel added, your quadcopter should be able to fly — i.e., you should be able to increase the throttle and it should leave the ground and fly level. However, it may spin because you don’t have yaw control yet.

For your quad’s safety, you may want to attach the prop-guards that came in your crash kit. The prop-guards make it less likely that the props will cut someone and they also help prevent damage to the motor shafts — a hard crash on a prop can bend the shaft and ruin one of your motors.

These are the loopy piece of black plastic. It has four mounting points that attach the motors, but the dimensions won’t quite match your quad. You can cut it into four pieces and attach a piece to each motor.

### 

### Adding the Yaw PID Channel
The Yaw channel is a little different. Use the left-right axis of the left controller gimbal to set the rate of rotation. This is exactly what the gyro gives you. The gyro is also pretty low noise, so you probably won’t need to do much filtering.

Tuning this PID loop is harder, since the test stand doesn’t spin. However, yaw is also not as critical for stable flight so you can probably tune it while the quadcopter is in the air.