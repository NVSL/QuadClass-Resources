#  Sensing and Filtering

To be completed in your groups.

Check the course schedule for due date(s).

## Skills to Learn
1. Filter and combine sensor inputs from an IMU.
2. Implement a PID control loop in Arduino.
3. Tune a PID control loop
4. Implement useful features on an quadcopter.

## Equipment, Supplies, and Software You Will Need

1. Test stand
2. Remote control

## Tips

* Your algorithms will have some parameters to tune.
* The remote's knob and buttons are meant to help tune them.  You can use the knobs on your remote control to changes these dynamically, it will make tuning much faster than having to recompile.
* You can use the buttons too. For example, you could use the buttons to switch between parameters and adjust them with the knob.
* Some enterprising groups have also use the gimbals to set parameters too.
* You can send information over the serial port to your laptop to provide feedback to the user.

## Tasks to Perform

You cannot control what you cannot measure.  In this lab, you will use the IMU and some software to accurately measure the orientation of the quadcopter.  In the next lab, you'll use this measurement as the input to a control algorithm that will keep the quadcopter stable.

### Reading Data from the IMU

Verify that your your FCB is working properly and that you can program it and that you can read from the IMU by re-running your code from the previous lab.

The the IMU provide a 3-axis accelerometer and a 3-axis gyroscope. For the quadcopter, you won't use the accelerometer data directly. Instead, your code will use them to compute the pitch and roll angles.   You installed the library for this in the previous lab (https://github.com/NVSL/QuadClass_AHRS).

The key function in this library is: `Adafruit_Simple_AHRS::getQuad()` that fills in a new struct: `quad_data_t` with all the information you'll need: pitch and roll angles and the three axes of the gyro. There is also an new example: `File->Examples->QuadClass AHRS->ahrs_quad.ino` that will print out these values.

I believe that you should not need to modify any of these libraries. If you find that you do, go ahead, but please let me know (or submit a pull request!).

### Plotting Data

Arduino has a nice data plotting facility built in. You you print out numbers on a line, separated by spaces, it will plot each column of numbers in a different color in real time. Just select `Tools->Serial Plotter`. Any non-numeric data is ignored.

For best results, set your serial port bit rate to 115200. This the argument to `Serial.begin()` in your `setup()` function.

I have been having some trouble getting the serial port to work at 115200. For unclear reasons sometimes it will only work up to 19200. 9600 always works, but it's slow, so the graph is not very responsive.

Integrate the code from the example into your code for remote controlled motors from the last lab and have it plot the pitch euler angle and the pitch gyro outputs from your IMU.

### Dealing with Noise

If you turn on the motors, you'll notice the output of the IMU gets noisy due to vibrations from the motorts.  If you can't accurately sense the orientation of your quadcopter, you can't hope to control it.

To see the problem, use the sketch you just created. As you move the pivot platform with your fingers, you should see the curve swing back and forth pretty smoothly. Now try increasing the throttle to the motors using the remote control. You'll notice that curve becomes very jagged -- not smooth at all.

This is a big problems because it means that 1) the instantaneous measurements of your orientation are not accurate and 2) the derivative of your orientation is wildly unstable (since it bounces between positive and negative values). We need both the orientation and its derivative to be well-behave in order to stabilize the quadcopter (you'll see why in the next lab).

We will address this problem in two ways: Apply filtering in software and use the IMU's built in filters.

### Filtering in Software

You can filter out some of the noise in software by combining the readings from the accelerometer and the gyroscope. The AHRS library gives you Euler angles (i.e., degrees) for your quadcopter's orientation. These do not drift over time, but they are quite noisy when your motors are running.

The gyroscope gives you angular acceleration (i.e., the derivative of the Euler angles). The gyroscopes are less noisy than than the accelerometers. You could recover the Euler angles by integrating the gyroscope outputs, but the resulting measurement will drift over time.

Our goal is to combine these two to use the accelerometer to avoid drift while using the gyroscope to avoid noise. The easiest way to do this is with a [complementary filter](http://www.pieter-jan.com/node/11). The math is simple and it's pretty intuitive.

The filter is weighted average of two terms:

1. The previously measured Euler angle + the integral of the gyroscope measurement since that measurement.
2. The current Euler angles measured from the IMU.

The filter's single parameter (called the complementary gain) ranges from 0 to 1 and controls how each of these terms contributes to the output. The higher the gain, the more influence the gyroscope has over the output.

### The IMU's Filters

The IMU has some built in filters that can remove noise from its output.  This is great, because it doesn't place any load on the microcontroller. Unfortunately, the documentation is kinda terrible. 

Here's some basic terminology:

1. A low-pass filter allows the low-frequency component of a signal to pass through.
2. A high-pass filter allows the high-frequency component of a signal to pass through.
Generally, we would like the low-frequency information from the accelerometers and some part of the higher-frequency information from the gyroscopes.

To make these work, you need to apply information from the IMU datasheet to the code that interfaces with the IMU.

There are three things you need to do:

1. Make sure you you aren't "clipping" your gyroscope values. The gyros have a configurable measurement range. If it is too narrow, high rates of change will get "clipped" (this will show up as a flat plateau where a maximum should be). Use `lsm.setupGyro()` to eliminate the clipping.
2. Adjust the output data rate (ODR) so it's compatible with the rate at which you are sampling the data from the IMU. The ODR should be slightly faster than you can sample. The AHRS example prints the latency for each trip through the loop at the beginning of each line (usually ~4ms). Your sampling rate is 1/latency (e.g., 500Hz). You set the ODR for both the gyro and the accelerometer `CTRL_REG1_G` (Section 7.12) `.`
3. You should "ODR ratio" for the accelerometer to filter out the high-frequency components using the IMU's built-in low-pass filter. The cutoff is set by dividing the ODR by the ODR ratio. For the default ORD (952Hz) and the default ratio (9), the low-pass cutoff is 105Hz. You set this with register `CTRL_REG7_XL` (Section 7.25).
4. You can also set the low-pass cutoff for the gyroscope, although this is less critical. The default is 63Hz. You can control this with `CTRL_REG1_G`. Note that this is also the register that control the ODR. You need to set both of them at the same time.

In your code, you *must* use the macros and constants defined in [Adafruit_LSM9DS1.h](https://github.com/NVSL/QuadClass_LSM9DS1/blob/master/Adafruit_LSM9DS1.h).  If you should me code with magical hexadecimal values in it, I will tell you to go make your code readable first by using the macros and constants.

With the new libraries, you can do all this tuning in a function like `setupSensor()` in the IMU example program. The example configures the IMU for all the values described above. Make sure you understand how it is working before you proceed.

For the completion of this lab, your demo will be you wiggling your pivot platform with your motors going full blast and the plotting curves moving responsively but smoothly in response.

### What Your Output Should Look Like

The output of your complimentary filter will be an estimate of your current pitch angle. When you have your IMU filters set properly and your complimentary filter set correctly, you should observe the following:

1. No clipping.
2. With the motors off and the platform still, your estimated pitch angle should not change, even over long periods.
3. With the motors off and the platform moving, the maxima and minima for the pitch angle should align with the zeros of the raw gyro measurement. The pitch angle should change smoothly.
4. With the motors on and the platform still, it should not significantly different than with the motors off.
5. With the motors on and the platform moving, it should not significantly different than with the motors off. The zeros of the gyro measurement should align with the maxima and minima of the pitch angle.

The figure below illustrates the the layers of filtering at their effect:

1. Top-left: The unfiltered accelerometer and gyro data (motors off). It is noisy, but note that the maxima of the accelerometer curve coincides with the zero of the gyro. This means the two signals are phase-aligned, since the gryo is the derivative of the accelerometer reading.
2. Top-right: The accelerometer data after the IMU's low-pass filter. The noise is gone, but it is out of phase and the amplitude is reduced.
3. Bottom-left: Combining the accelerometer data with the gryo data with the complementary filter preserves the smoothness and corrects the phase alignment.
4. Bottom-right: Turning on the motors doesn't affect the output of the complimentary filter.

![Designed output](images/desired-output.png)

### Tuning Tips

Neither the complimentary filter nor the IMU's filters are sufficient to get with we need: A smooth, non-drifting pitch angle in the presence of motor noise.  It will take some trial and error to get the right output. Here are some tips:

1. Our gyroscopes are quite accurate, so integrating doesn't cause very much drift. They are are also pretty immune to vibrational noise.  This argues for a high complementary gain.
2. The accelerometer has no drift, but is extremely susceptible to vibrations. This argues for an aggressive (i.e., very low) cut off frequency for the accelerometer. This is ok especially because the gyroscope will provide good high-frequency data.
3. If your complimentary gain is too high, your measurements will drift. The drift can be very, very slow, but so take time to make sure it's not there.

### Turn in Your Work

Commit your results:

1. `Commit an updated version of quad_firmware.ino` and `remote_firmware.ino`.
2. Commit any modified libraries you use in your firmware.
3. Include a file called `noise.txt` that describes succintly what settings you used for filtering in hardware and software.

Once you've committed everything, create a tag called "sensing-and-filtering" Be sure to make it an "annotated" tag and push it to your repo (https://git-scm.com/book/en/v2/Git-Basics-Tagging). Verify that it is visible on github.

#### Demo your work:

1. Demo your clean orientation measurements for me or the TA.
