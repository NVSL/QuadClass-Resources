# Sensing and Filtering

To be completed in your groups.

Check the course schedule for due date(s).

## Skills to Learn

1.  Read data from the IMU.
2.  Using the Arduino plotting tool.
3.  Configure the builtin filters.
4.  Implement a complimentary filter in software.
5.  Tune the filters to provide good readings of FCB orientation.

## Equipment, Supplies, and Software You Will Need

1. Test stand
2. Remote control

## Tips

- Your algorithms will have some parameters to tune. The remote's knob and buttons are meant to help tune them. You can use the knobs on your remote control to changes these dynamically, it will make tuning much faster than having to recompile.
- You can use the buttons too. For example, you could use the buttons to switch between parameters and adjust them with the knob.
- Some enterprising groups have also use the gimbals to set parameters too.
- You can send information over the serial port to your laptop to provide feedback to the user.
- If you stall the motors (i.e., hold them still with the throttle on), it may cause either your IMU reset, which will make it stop reporting any data.
- If your FCB resets when you turn on the motors, it's likely your battery is dying.
- Your IMU stops returning sensible numbers, it's likely your battery is dying.

## Tasks to Perform

You cannot control what you cannot measure.

In this lab, you will use the IMU and some software to accurately measure the orientation of the quadcopter. In the next lab, you'll use this measurement as the input to a control algorithm that will keep the quadcopter stable.

### Reading Data from the IMU

Verify that your FCB is working properly and that you can program it and that you can read from the IMU by re-running your code from the previous lab.

The IMU provides a 3-axis accelerometer and a 3-axis gyroscope. You won't use the accelerometer data directly. Instead, your code will use them to compute the pitch and roll angles. You installed the library for this in the previous lab (https://github.com/NVSL/QuadClass_AHRS).

The key function in this library is: `Adafruit_Simple_AHRS::getQuadOrientation()` that fills in a new struct: `quad_data_t` with all the information you'll need: pitch and roll angles and the three axes of the gyro. There is also an example: `File->Examples->QuadClass AHRS->ahrs_quad_lsm6ds0.ino` that will print out these values.

I believe that you should not need to modify any of these libraries. If you find that you do, go ahead, but please let me know (or submit a pull request!).

### Plotting Data

Arduino has a nice data plotting facility built in. You print out numbers on a line, separated by spaces, it will plot each column of numbers in a different color in real time. Just select `Tools->Serial Plotter`. Any non-numeric data is ignored.

For best results, set your serial port bit rate to 115200. This the argument to `Serial.begin()` in your `setup()` function.

I have been having some trouble getting the serial port to work at 115200. For unclear reasons sometimes it will only work up to 19200. 9600 always works, but it's slow, so the graph is not very responsive.

Integrate the code from the example into your code for remote controlled motors from the last lab and have it plot the pitch euler angle (`.pitch` in the `quad_data_t` struct) and the pitch rate (`.pitch_rate`) from your IMU.

### Dealing with Noise

If you turn on the motors, you'll notice the output of the IMU gets noisy due to vibrations from the motorts. If you can't accurately sense the orientation of your quadcopter, you can't hope to control it.

To see the problem, use the sketch you just created. As you move the pivot platform with your fingers, you should see the curve swing back and forth pretty smoothly. Now try increasing the throttle to the motors using the remote control. You'll notice that curve becomes very jagged -- not smooth at all.

This is a big problems because it means that 1) the instantaneous measurements of your orientation are not accurate and 2) the derivative of your orientation is wildly unstable (since it bounces between positive and negative values). We need both the orientation and its derivative to be well-behave in order to stabilize the quadcopter (you'll see why in the next lab).

We will address this problem in two ways:

1. Applying filtering in software using a complementary filter.
2. Using the IMU's built in filters by configuring registers.

### Filtering in Software (Complementary filter)

You can filter out some of the noise in software by combining the readings from the accelerometer and the gyroscope. The AHRS library gives you Euler angles (i.e., degrees) for your quadcopter's orientation. These do not drift over time, but they are quite noisy when your motors are running.

The gyroscope gives you angular acceleration (i.e., the derivative of the Euler angles). The gyroscopes are less noisy than than the accelerometers. You could recover the Euler angles by integrating the gyroscope outputs, but the resulting measurement will drift over time due to accumulated error.

Our goal is to combine these two to use the accelerometer to avoid drift while using the gyroscope to avoid noise. The easiest way to do this is with a [complementary filter](http://www.pieter-jan.com/node/11). The math is simple and it's pretty intuitive.

The filter is weighted average of two terms:

1. The previously measured Euler angle + the integral of the gyroscope measurement since that measurement.
2. The current Euler angles measured from the IMU.

The filter's single parameter (called the _complementary gain_) ranges from 0 to 1 and controls how each of these terms contributes to the output. The higher the gain, the more influence the gyroscope has over the output.

Complementary filter (cf) equation:

```
cf_angle = (gain)*(cf_angle + gyro_raw * RAD_TO_DEG * dt) + (1-gain)*(acc_angle)
```

Where:

- `cf_angle` = Complementary filter angle
- `acc_angle` = Euler angles from `Adafruit_Simple_AHRS::getQuad()`
- `gyro_raw` = Gyroscope measurement from `Adafruit_Simple_AHRS::getQuad()`
- `gain` = Complementary gain
- `dt` = delta time

Notes:

- The `gyro_raw` value is in radians and needs to be converted to degrees.

```
#define RAD_TO_DEG 57.295779513082320876798154814105
```

- For dt (time), use the arduino funcion `millis()`. You want the time between loops, not the time now.

- Is advised to compare `acc_angle` to `gyro_angle` to check if both output a reasonable angle when tilting the FCB. The `gyro_angle` formula is the following:

```
gyro_angle = gyro_angle + gyro_raw * RAD_TO_DEG * dt
```

- When adjusting the gain from 0 to 1 you should see the complementary filter moving either to `acc_angle` or `gyro_angle`, depending on the gain value.
- You need to implement the complementary filter for both `pitch` and `roll`, we won't implement `yaw`.

I recommend watching this video to learn more about complementary filters: https://www.youtube.com/watch?v=6AoJ8wr8G6A

### Filtering using the IMU registers

The IMU has a bunch of settings that control how it collects and reports data. It also has some built in filters that can remove noise from its output. This is great, because it doesn't place any load on the microcontroller. Unfortunately, the documentation is kinda terrible.

Here's some basic terminology:

1. A low-pass filter allows the low-frequency component of a signal to pass through.
2. A high-pass filter allows the high-frequency component of a signal to pass through.

Generally, we would like the low-frequency information from the accelerometers and some part of the higher-frequency information from the gyroscopes.

#### Read Key Sections of the IMU Datasheet

- 6.4
- 9.12
- 9.13
- 9.17
- 9.18
- 9.19

#### Configure the Gyroscope and Accelerometer to Prevent Clipping (Sensitivity)

"Clipping" occurs when a measured value exceeds the range the IMU can handle. For the gyroscope, this means it rotates too quickly.
Clipping will show up as a flat plateau where a maximum should be on a graph of the gyro output. This is bad, because we will be relying on the integral of the gyro data to approximate Euler angles.

Use `lsm.setGyroRange()` to adjust range of values the gyros measure to eliminate the clipping. Use `lsm.setAccelRange()` to adjust the range of values for the accelerometer.

#### Adjust the Output Data Rate (ODR)

Adjust the output data rate (ODR) so it's higher than the rate at which you are sampling the data from the IMU. If the ODR is lower than your sampling rate, you'll read the same value repeatedly.

The AHRS example prints the latency for each trip through the loop at the beginning of each line (usually ~4ms). Your sampling rate is 1/latency (e.g., 250Hz). You can set the ODR for both the gyro and the accelerometer using `lsm.setAccelDataRate()` and `lsm.setAccelDataRate()`. See Table 44 and Table 48 for selecting the ODR.

#### Setup the Low-Pass Filter on the Accelerometer

The accelerometer can be configured as a low-pass filter or high-pass filter, this filter is called composite filter and can be setup using `lsm.setAccelCompositeFilter()`. The composite filter is shown in Figure 16 and 17, and the configuration register in Table 65.

We want the accelerometer to be configured as a low-pass filter to reduce noise, check how do this configuration using the function parameters.

You also need to set the cutoff for the low-pass filter of the composite filter, also referred as `LPF2`, by setting an ORD Ratio. The cutoff is set by dividing the ODR by the ODR ratio. For an ODR of 208 Hz and ODR/4, the low-pass cutoff is 52Hz.

#### Setup Filters On the Gyroscope

You want to let as much of the high-frequency signal from the gyroscope through as possible. Use `lsm.setGyroHPF()` to configure the Gyro HPF, use Table 62 for guidance.

#### Adjust for Offsets

When your FCB is still and level, it will probably not return zero pitch and zero pitch rate. When your FCB starts up (or maybe when you arm it) it should check the values coming from the IMU to see what offsets you are measuring. You should correct for these offsets so that the measured values are correct by subtracting the value measured at calibration, e.g. (`calibrated_angle = acc_angle - offset`). Do this for `acc_angle` and `gyro_raw`. Make the offsets variables global so that you can access them in all functions.

#### Coding Conventions

You can do all this tuning in a function similar to `setupSensor()` from the IMU example program. The example configures the IMU for all the values described above. Make sure you understand how it is working before you proceed.

In your code, you _must_ use the macros and constants defined in [QuadClass_LSM6DSOX.h](https://github.com/NVSL/QuadClass-LSM6DSOX/blob/main/QuadClass_LSM6DSOX.h) and [Adafruit_LSM6DS.h](https://github.com/adafruit/Adafruit_LSM6DS/blob/master/Adafruit_LSM6DS.h). If you show me code with magical hexadecimal values in it, I will tell you to go make your code readable first by using the macros and constants.

### What Your Output Should Look Like

For the completion of this lab, your demo will be you wiggling the airframe on your test stand with your motors going full blast and the plotting curves moving responsively but smoothly in response.

The output of your complimentary filter will be an estimate of your current pitch angle. When you have your IMU filters set properly and your complimentary filter set correctly, you should observe the following:

1. No clipping.
2. With the motors off and the platform still, your estimated pitch angle should not change, even over long periods.
3. With the motors off and the platform moving, the maxima and minima for the pitch angle should align with the zeros of the raw gyro measurement. The pitch angle should change smoothly.
4. With the motors on and the platform still, it should not significantly different than with the motors off.
5. With the motors on and the platform moving, it should not significantly different than with the motors off. The zeros of the raw gyro measurement should align with the maxima and minima of the pitch angle.

The figure below illustrates the layers of filtering at their effect:

1. Top-left: The unfiltered accelerometer and gyro data (motors off). It is noisy, but note that the maxima of the accelerometer curve coincides with the zero of the gyro. This means the two signals are phase-aligned, since the gryo is the derivative of the accelerometer reading.
2. Top-right: The accelerometer data after the IMU's low-pass filter. The noise is gone, but it is out of phase and the amplitude is reduced.
3. Bottom-left: Combining the accelerometer data with the gryo data with the complementary filter preserves the smoothness and corrects the phase alignment.
4. Bottom-right: Turning on the motors doesn't affect the output of the complimentary filter.

![Designed output](images/desired-output.png)

### Tuning Tips

Neither the complimentary filter nor the IMU's filters are sufficient on their own to get what we need: A smooth, non-drifting pitch angle in the presence of motor noise. It will take some trial and error to get the right output. Here are some tips:

1. Our gyroscopes are quite accurate, so integrating doesn't cause very much drift. They are also somewhat immune to vibrational noise. This argues for a high complementary gain.
2. The accelerometer has no drift, but is extremely susceptible to vibrations. This argues for a low cut off frequency for the accelerometer. This is ok especially because the gyroscope will provide good high-frequency data.
3. If your complimentary gain is too high, your measurements will drift. The drift can be very, very slow, but so take time to make sure it's not there.

You'll need to experiment quite a bit to get good measurement. The more tuning you can do without recompiling, the better, so spend some time refining your remote control code so you can tune things with the knob.

### Turn in Your Work

Commit your results:

1. Commit an updated version of `quad_firmware.ino` and `remote_firmware.ino`.

Once you've committed everything, create a tag called "sensing-and-filtering" Be sure to make it an "annotated" tag and push it to your repo (https://git-scm.com/book/en/v2/Git-Basics-Tagging). Verify that it is visible on github.

#### Demo your work:

1. Demo your clean orientation measurements for the TA.
2. Complete the reflection for this lab: https://docs.google.com/forms/d/e/1FAIpQLSfB8XsDV8FtTZYO1mv3FZrd9mUs1hDlFvQxnfAK0K2zptTjxQ/viewform

### Rubric

For the demo be ready with the serial plotter showing the output of your complimentary filter and the raw gyroscope output.  Those are the only signals we need to say to grade the lab.

Possible points: 10

Check list

1.  Motors off, Quadcopter horizontal, your filter outputs should be zeros (1 point)
2.  Moving the motors manually should show smooth output of the filter (1 point)
3.  Quick movement of the FCB should show quick response from filter output (1 point)
4.  Phase alignment should be good (gyro zero matches angle maxima/minima) (2 points)
5.  All of the above must hold at with motors at 75% throttle (5 points)

You will lose one point for each day late your solution is.
