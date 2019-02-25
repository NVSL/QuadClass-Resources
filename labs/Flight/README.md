# Flight

## Tasks to Perform (Hardware)

Complete assembly of your quadcopter.

Make sure that the propellers you attach push air in the right direction.

## Tasks to Perform (Software)

You need to implement the following features in your quadcopter firmware

## Arm

When you power up your quadcopter it should be “disarmed.” This means that it will not respond to the remote. This is safety feature (to prevent the props from running unexpectedly) and an opportunity to calibrate your sensors.

A common way to arm a quadcopter is to hold the throttle at zero and the roll gimbal all the way to one side or the other and wait a few seconds. You can use whatever method you like, but it must include the throttle being at zero.

It’d be nice to indicate when the quad is armed by flashing a light or something.

## Calibrate your IMU

When the quadcopter boots, it should calibrate the IMU. You should assume that the quadcopter is sitting on something level and check the measurements from the IMU to account for any offsets. Your quadcopter should refuse to arm itself until it’s calibrated.

It’d be nice to have a light that shows when it’s calibrating and/or when it’s ready to be armed.

## Complete The Flight Controller

The code you wrote for the test stand should be more or less ready to run on your quadcopter. In theory, the only changes you should need to make to get flying (but maybe not steering) are to update the pin assignments for your motors, re-tune the PID values, and add a PID channel for roll (assuming you were working on pitch on the test stand). For full flight control you’ll need to add a PID channel for and yaw.

### Tuning the PID Values

The process is same as it was for the test stand, with a few small changes.

1. Your quadcopter probably has more power than your test stand because the power delivery system is cleaner (your nice big power/ground planes are much better than the skinny wires on the test stand)
2. The mass and balance of your quadcopter is different than the test stand.
Both of these mean that the correct PID values for your quad are probably different than those for the test stand.

You can tune the values by attaching your quadcopter to the test stand. To do this, you can pull the pivot platform off the axel and attach your quad using tape or zip ties (available in the maker studio).

### Adding the Roll PID Channel

The PID control for roll works the same as for pitch. In theory, if your quad is symmetric the PID values should be the same too. I would check by rotating the quad on the test stand and seeing how stable it is.

Once you have the roll channel added, your quadcopter should be able to fly — i.e., you should be able to increase the throttle and it should leave the ground and fly level. However, it may spin because you don’t have yaw control yet.

For your quad’s safety, you may want to attach the prop-guards that came in your crash kit. The prop-guards make it less likely that the props will cut someone and they also help prevent damage to the motor shafts — a hard crash on a prop can bend the shaft and ruin one of your motors.

These are the loopy piece of black plastic. It has four mounting points that attach the motors, but the dimensions won’t quite match your quad. You can cut it into four pieces and attach a piece to each motor.

### Adding the Yaw PID Channel

The Yaw channel is a little different. Use the left-right axis of the left controller gimbal to set the rate of rotation. This is exactly what the gyro gives you. The gyro is also pretty low noise, so you probably won’t need to do much filtering.

Tuning this PID loop is harder, since the test stand doesn’t spin. However, yaw is also not as critical for stable flight so you can probably tune it while the quadcopter is in the air.

