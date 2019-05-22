# Flight

To be completed in groups.  Due during the final period for the course (see the schedule).

## Tasks to Perform (Software)

You need to implement the following features in your quadcopter firmware

### Complete The Flight Controller

The code you wrote for the test stand should be more or less ready to run on your quadcopter. In theory, the only changes you should need to make to get flying (but maybe not steering) are to update the pin assignments for your motors, re-tune the PID values, and add a PID channel for roll.  For full flight control you’ll need to add a PID channel for and yaw.

### Tuning the PID Values

The process is same as it was for the test stand, with a few small changes, since the mass and balance of your quadcopter is different than on the test stand.  Both of these mean that the correct PID values for your quad are probably different than those for the test stand.

You can tune the values by attaching your quadcopter to the test stand. To do this, you can pull the pivot platform off the axel and attach your quad using tape or zip ties (available in the maker studio).  Or you can use tape (also available in the maker studio).

### Adding the Roll PID Channel

The PID control for roll works the same as for pitch. In theory, if your quad is symmetric the PID values should be the same too. I would check by rotating the quad on the test stand and seeing how stable it is.

Once you have the roll channel added, your quadcopter should be able to fly — i.e., you should be able to increase the throttle and it should leave the ground and fly level. However, it may spin because you don’t have yaw control yet.

I have found it useful to attach the quadcopter to end of a stick (like the pivot from your test stand).  Then it can "fly" while you hold on to it.  With this you can check the general stability of either pitch or roll, and you can also check to make sure that your remote inputs are interpretted correctly (i.e., left on te stick means left on the quadcopter).

### Adding the Yaw PID Channel

The Yaw channel is a little different.  Use the left-right axis of the left controller gimbal to set the rate of rotation.  You should get yaw working reasonably well before attempting flight.  Spinning in the air makes it very hard to tell what's going wrong with pitch and roll.

There are a few things that make yaw easier to deal with:

1.  The gyro gives you yaw rate directly, and it's pretty low noise.
2.  Yaw rate changes pretty slowly because the torque that the motors apply to the yaw axis is much smaller than the torqe the propellers apply to the pitch and roll axes.
3.  Small errors in yaw rate (i.e., rotating slowly) won't hurt quadcopter stabilty.p

The gyro is also pretty low noise, so you probably won’t need to do much filtering.  It's possible that you might want to filter out some of the high-frequency (i.e., reducing cutoff for the gyro's low-pass filter)

The inputs for the yaw controller are different than for pitch and roll.  Since you only get the rate of change for the yaw rate, so there’s no need or use for a complimentary filter.   Instead, use the yaw rate as the input and use PID to keep the yaw rate at zero (i.e., so you quadcopter is not rotating).  You should, eventually, also be able to make your quadcopter spin in a controlled manner using the yaw stick.

Tuning this PID loop is harder, since the test stand doesn’t spin.  An alternative is to suspend the quadcopter with string by it's arms so it hangs level in the air and can spin freely.  The makerspace has string.



