# Flight

To be completed in groups.  Due during the final period for the course (see the schedule).

## Tasks to Perform

This lab should get your quadcopter flying!  

In the best case, you would complete this lab with your quadcopter, but you should start with the FCB+airframe from your test stand.  There are several reasons for this:

1.  It's symmetric, so pitch and roll should be have the same.
2.  It's easy to repair (and we have lots of spare parts) -- you will crash a lot.  Better on the test stand than your board.
3.  It has holes etc. that make it easy to attach tuning aids (like sticks for it to balance on.)

Once your fligh control software works on the test stand, it should just be a matter of tweaking the PID values for your quadcopter. 

### Tweaks to the Airframe

To make the airframe more robust to crashes, it helps to add some supports between the corners of the FCB and the airframe.  Use a small amount of hot glue to add two "donut" spacers at each corner.  Like this:

![Airframe spacers](images/airframe-spacers.jpg)

You need to firmly attach the motors to your airframe.  Hot glue is the best way to do this.  Carefully position your motors so that motors extend down far enough to support the quadcopter (i.e., be its feet) so it sits level. Then apply as _small_ amount of hot glue:

![An appropriate amount of hot glue](images/hot-glue.jpg)

You'll need to securely attach your batteries to your quadcopter.  Velcro works well for this, and we have some.  The soft, fuzzy side goes on the quadcopter.  It can be on the top or bottom, but it needs to be near the center.  For the FCB place it as shown below.  The hard, rough side goes on the battery:

![Velcro'd battery](images/velcro-on-battery.jpg)

Here it is installed:

![Velcro'd battery](images/velcroed-battery.jpg)

You can also put some soft velcro on your remote somewhere to hold its battery.

You may want to shorten the battery cable on your quad.  For the FCB, 1-2inches is pretty good.  THe right value for your quadcopter will vary according to its design.


### Complete The Flight Controller

The code you wrote for the test stand should be more or less ready to run on your quadcopter. In theory, the only changes you should need to make to get flying (but maybe not steering) are to update the pin assignments for your motors, re-tune the PID values, and add a PID channel for roll.  For full flight control you’ll need to add a PID channel for and yaw.

### Tuning the PID Values

The process is same as it was for the test stand, with a few small changes, since the mass and balance of your quadcopter is different than on the test stand.  Both of these mean that the correct PID values for your quad are probably different than those for the test stand.

You can tune the values by attaching your quadcopter to the test stand. To do this, you can pull the pivot platform off the axel and attach your quad using tape or zip ties (available in the maker studio).  Or you can use tape (also available in the maker studio).

### Adding the Roll PID Channel

The PID control for roll works the same as for pitch. In theory, if your quad is symmetric the PID values should be the same too. I would check by rotating the quad on the test stand and seeing how stable it is.

I have found it useful to attach the quadcopter to end of a stick (like the pivot from your test stand).  Then it can "fly" while you hold on to it.  With this you can check the general stability of either pitch or roll, and you can also check to make sure that your remote inputs are interpreted correctly (i.e., left on te stick means left on the quadcopter).

### Adding the Yaw PID Channel

The Yaw channel is a little different.  Use the left-right axis of the left controller gimbal to set the rate of rotation.  You should get yaw working reasonably well before attempting flight.  Spinning in the air makes it very hard to tell what's going wrong with pitch and roll.

There are a few things that make yaw easier to deal with:

1.  The gyro gives you yaw rate directly, and it's pretty low noise.
2.  Yaw rate changes pretty slowly because the torque that the motors apply to the yaw axis is much smaller than the torqe the propellers apply to the pitch and roll axes.
3.  Small errors in yaw rate (i.e., rotating slowly) won't hurt quadcopter stabilty.p

The gyro is also pretty low noise, so you probably won’t need to do much filtering.

The inputs for the yaw controller are different than for pitch and roll.  Since you only get the rate of change for the yaw rate, so there’s no need or use for a complimentary filter.   Instead, use the yaw rate as the input and use PID to keep the yaw rate at zero (i.e., so you quadcopter is not rotating).  You should also be able to make your quadcopter spin in a controlled manner using the yaw stick.

Tuning this PID loop is both harder and easier that roll and pitch.  It's harder since the test stand doesn’t spin.  You can get around this by tying string to the four arms of your quadcopter so it  hangs level in the air and can spin freely.  The makerspace has string and I have monofiliment fishing line.  Make sure they don't get caught in the propellers.  It will look something like this:

![suspended to tune yaw](images/suspended-quad.jpg)

Tuning yaw is easier because it's more forgiving, since the amount of force yours can apply to the yaw axis is relatively small.  You probably don't need an D term, and I find the P and I terms are pretty forgiving.

### Trim

The calibration of your IMU is never perfect, and you will probably find that your quadcopter tends to drift/flop to one side.  Adding a trimming mechanism can help with this.  "Trimming" means adding a small, fixed offset to the controls (or the sensor readings) that can be adjusted in real time from the remote.  The D-pad of buttons is great for (actually built for) this.  It needs to be very easy to use -- it's not unusual to adjust trim while the quadcopter is airborne.  You probably only need to trim pitch and roll, and the D-pad is very intuitive for them.  If you want to be able to trim yaw as well, use the knob.

### Testing in All Together

Two test all your PID axes together, you'll need to abandon the test stand.  A good first step is to instal two wooden dowels as stabilizers:  One through the zip ties on the airframe and another through the holes between the spacers/screws that connect the FCB to the airframe:

![stabilizers](images/stablilzers.jpg)

The one stabilizer between the spacers maybe need a couple of layers (but no more) of blue tape to fit snuggly. 

This will let you  fly the quadcopter against a table:

![flying against the table](images/flying_against_the_table.jpg)

It makes it easier to switch from pitch to roll and lets you check whether the controls affect the quadcopter like you would expect.  

Once things seems pretty stable, you can put the quadcopter the floor with the stabilizers.  They  will reduce the likelihood of your quadcopter flipping over (a common failure mode).  Flight with the stabilizers is not recommended.  They break easily.

### Common Flight Pathologies

Lots of things go wrong during flight testing.  Here are some common problems.

#### Instable Flight

* When your quadcopter starts to leave the ground, it should not slip sideways across the floor.  If it does, adjust the trim until it takes off evenly.
* Your quadcopter's trim may change as the battery drains.  Re-trim frequently if flight becomes more difficult.
* Watch how your quadcopter's props slow down.  If one stops significantly before the others, it might be rubbing on something, which will make it ineffective.
* After a crash, it's common for your prop guards to move up and sometimes touch the propellors, reducing lift.  Push down on the prop guard to reseat.
* high-frequency occilations (2-3/sec) -- decrease D coefficient for that axis.
* Low frequency occsilations (0.5/sec, which will manifest as the quadcopter swinging back and forth in the air) -- increase P.
* Crashes immediately and repeatedly -- put it back on the test stand and tune some more.
* Check your battery frequently.

#### Crashes 

You are going to crash alot. Crashes can damage your motors and propellers, causing your quadcopter to suddenly become unflyable.

If things are working pretty well, you crash, and then nothing seems to work, check the following:

1.  **Check your battery** Weak batteries can't fly a quadcopter.
2.  **Propellers** Bent propeller tips can reduce thrust enough to making the quadcopter uncontrollable.  Try replacing any that look damaged.
3.  **Motors** If one side of your quad seems weak and the propellers are good, try a new motor.  If it helps, cut the wires on the motor that was bad.  You never want to use it again.

#### Trouble Getting Airborne

You may also find that you have trouble getting your qudacopter off the ground cleanly.  Near the ground, the ground interferes with the propellers, causing the quadcopter to misbehave.

The bottom of the quadcopter may catch on the ground, causing it to tend to flip over.

A (sometimes) solution to both of these problems is to give it a quick boost to get it off (and away from) the ground.  You can also try launching from your hand.  The downside is that both of these techniques will increase the severity of crashes.

### The Big Push

Your quadcopter will hopefully make a lot of progress between the last class period and the final meeting time.  In order to work on your quadcopter successfully over the weekend, you'll need some equipment:

1.  Several sets of propellers.
2.  Several charged batteries.
3.  3 feet of monofiliment (if you haven't already tuned your yaw loop)
4.  An extra set of motors.
5.  Some zip ties to hold your quadcopter to a stick.
6.  A length of masking tape.

I'll set up all the battery charger next to the reflow oven in the maker studio.  If need batteries and the maker studio is open, come in, take some charged batteries, and start your batteries charging.  **For the big red chargers, you need to push the button until the light turns red to start them charging).


