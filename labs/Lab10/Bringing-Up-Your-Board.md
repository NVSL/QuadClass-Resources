# Bringup

"Bringing up" a board means carefully checking that each component of the board works as expected.

There is a tendency to move to quickly during bringup, but take your time.  If you try to run a big piece of software at first, the bugs will be much harder to find.

A purpose-built tester is useful here.  For instance, for the remote, there is `Quadcopter-Remote/src/test_remote/test_remote.ino` and `Quadcopter-Remote/src/test_remote/test_remote_harness.ino`.  `test_remote.ino` runs on the remote and transmits a bunch of data to another device (a working remote or a FCB) running `test_remote_harness.ino`.  It tests all the software-accessible components of the remote.
It doesn't, however, check that the battery charger works.  So, you'll need to verify that mannually.

Your code from the first remote/FCB can also serve as a good starting point.  When bringing up your quadcopter, remember that the pin assignments may be differnt, so you may need to modify the code slightly.



