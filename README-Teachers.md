# The Quadcopter Class

This repo is the starting point for everything about the quadcopter class at UCSD.

The course web page is here:

https://sites.google.com/a/eng.ucsd.edu/quadcopterclass/

The entry point for students is in `README.md`.

The information about project (write ups, labs, etc) is all in this repo:

* `labs` has all the labs. The write ups reference the starter repos they use (via github classroom).  The slide are in there as well.
* `Eagle` has the pre-built parts library, CAM files, and design rule files to use with Eagle.

A paper describing the class is here:

https://arxiv.org/abs/1810.07646

## Accessing Solutions

The solutions to the labs and parts of the autograde are only open to educators.

I created a GitHub group with read-only access to all the repos for the course, including the solution:

If you would like access, please email swanson@cs.ucsd.edu.

## Autograder

We use an autograder to grade the assignments.  It includes both generic style checks and correctness for the course
assignments.

The generic lint for Eagle files is here:

https://github.com/NVSL/EagleLint

The modules for checking the course assignments are here:

https://github.com/NVSL/QuadClass-QuadLint.git


## Course Equipment

* The remote control is here: https://github.com/NVSL/Quadcopter-Remote
* The test stand is here: https://github.com/NVSL/PID-Test-Stand

## Using Github Classroom

Here's one way to use github classroom to run this course.

1.  Create an organization for the course.  Reuse the same org year-to-year.
2.  Create new assignments for each year (e.g., "Building eagle Parts 2018").  Student repos are grouped by assignment, so if you reuse last year's you'll see all their repos too.
3.  When you create new assignments for a year, disable the invitation link for the old assignments so students don't accidently use them.
4.  You can download the zip files for the submissions and run the autograder on it.

