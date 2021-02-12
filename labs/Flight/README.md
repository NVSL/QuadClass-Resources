# Flight

To be completed in groups.  Check schedule for due date.

## Tasks to Perform

This lab should get your quadcopter flying!  

In the best case, you would complete this lab with your quadcopter, but you should start with the FCB+airframe from your test stand.  There are several reasons for this:

1.  It's symmetric, so pitch and roll should be have the same.
2.  It's easy to repair (and we have lots of spare parts) -- you will crash a lot.  Better on the test stand than your board.
3.  It fits easily on the test stand.

Once your fligh control software works on the test stand, it should just be a matter of tweaking the PID values for your quadcopter. 

### The Last Axis

You need to add another PID controller for roll.  This will give you control over all three axes.  On the FCB, the pitch and roll axes should use roughly the same tuning pramaters, since our quadcopters are symetric.  You'll need to make sure that mixes is updated to pay attention to pitch too.

### Porting Your Code to Your Quad

Porting the code to your quadcopter should be easy.  The main thing you may need to change is the pin assignments for the motors.  You may also need to add code to control your LEDs.

### Tuning the PID Values

The process is same as it was for the test stand, with a few small changes, since the mass and balance of your quadcopter is different than on the test stand.  Both of these mean that the correct PID values for your quad are probably different than those for the test stand.

You can tune the values by attaching your quadcopter to the test stand. To do this, you can pull the pivot platform off the axel and attach your quad using tape or zip ties (available in the maker studio).  Or you can use tape (also available in the maker studio).

### Tuning the Roll PID Channel

The PID control for roll works the same as for pitch. In theory, if your quad is symmetric the PID values should be the same too. I would check by rotating the quad on the test stand and seeing how stable it is.

I have found it useful to attach the quadcopter to end of a stick (like the pivot from your test stand).  Then it can "fly" while you hold on to it.  With this you can check the general stability of either pitch or roll, and you can also check to make sure that your remote inputs are interpreted correctly (i.e., left on te stick means left on the quadcopter).

### Testing in All Together

To test all your PID axes together, you'll need to abandon the test stand.  A good first step is to leverage the two wood dowels installed on the FCB.

![stabilizers](images/stablilzers.jpg)

This will let you  fly the quadcopter against a table:

![flying against the table](images/flying_against_the_table.jpg)

It makes it easier to switch from pitch to roll and lets you check whether the controls affect the quadcopter like you would expect.  

Once things seems pretty stable, you can put the quadcopter the floor with the stabilizers.  They  will reduce the likelihood of your quadcopter flipping over (a common failure mode).  

### Common Flight Pathologies

Lots of things go wrong during flight testing.  Here are some common problems.

#### Instable Flight

* When your quadcopter starts to leave the ground, it should not slip sideways across the floor.  If it does, adjust the trim until it takes off evenly.
* Your quadcopter's trim may change as the battery drains.  Re-trim frequently if flight becomes more difficult.
* Watch how your quadcopter's props slow down.  If one stops significantly before the others, it might be rubbing on something (e.g., a prop guard), which will make it ineffective.
* After a crash, it's common for your prop guards to move up and sometimes touch the propellors, reducing lift.  Push down on the prop guard to reseat.
* high-frequency occilations (2-3/sec) -- decrease D coefficient for that axis.
* Low frequency occsilations (0.5/sec, which will manifest as the quadcopter swinging back and forth in the air) -- increase P.
* Crashes immediately and repeatedly -- put it back on the test stand and tune some more.
* Check your battery level frequently.

#### Crashes 

You are going to crash alot. Crashes can damage your motors and propellers, causing your quadcopter to suddenly become unflyable.

If things are working pretty well, you crash, and then nothing seems to work, check the following:

1.  **Check your battery** Weak batteries can't fly a quadcopter.
2.  **Propellers** Bent propeller tips can reduce thrust enough to making the quadcopter uncontrollable.  Try replacing any that look damaged.
3.  **Motors** If one side of your quad seems weak and the propellers are good, try a new motor.  If it helps, cut the wires on the motor that was bad.  You never want to use it again.

**Note for COVID**: for the last two, check with the staff to verify what's wrong. 

#### Trouble Getting Airborne

You may also find that you have trouble getting your qudacopter off the ground cleanly.  Near the ground, the ground interferes with the propellers, causing the quadcopter to misbehave.

The bottom of the quadcopter may catch on the ground, causing it to tend to flip over.

A (sometimes) solution to both of these problems is to give it a quick boost to get it off (and away from) the ground.  You can also try launching from your hand.  The downside is that both of these techniques will increase the severity of crashes.

