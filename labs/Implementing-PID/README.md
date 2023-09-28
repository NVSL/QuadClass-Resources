# Implementing PID

To be completed in your groups.

Check the course schedule for due date(s).

## Skills to Learn



## Equipment, Supplies, and Software You Will Need

1. Test stand
2. Remote control


### Turn in Your Work

#### Commit your results:

1. Commit an updated version of `quad_firmware.ino` and `remote_firmware.ino`.
2. Updated version of `noise.txt` with updates filter configuration parameters
   (if you changed them), and the your PID and values for each axis.

Once you’ve committed everything, create a tag called “PID-test-stand-2” Be sure to make it an “annotated” tag and push it to your repo (https://git-scm.com/book/en/v2/Git-Basics-Tagging). Verify that it is visible on github.

#### Demo your work:

1. Demo your clean orientation measurements for the TA.
2. Complete the reflection for this lab: https://docs.google.com/forms/d/e/1FAIpQLSfB8XsDV8FtTZYO1mv3FZrd9mUs1hDlFvQxnfAK0K2zptTjxQ/viewform

### Rubric

Possible points: 13

Check list (for each axis):

Yaw:

1. Non-spin with yaw neutral.
3. No visible oscillation
4. Trim functional.
5. Crisp, sharp start and stop.
6. Constant yaw rate with increasing throttle.

Pitch:

1. Level "flight" with pitch at neutral.
2. Only moderate oscillation at neutral.
3. Almost no oscillation at neutral.
4. Trim functional.
5. Symmetric movement pitching forward and back (pitch stick at 10degree position gives 10 degree tilt)
6. Same amount of oscilation when pitched as when level.
7. Moderate overshoot
8. Almost on overshoot.

You will lose one point for each day late your solution is. 
