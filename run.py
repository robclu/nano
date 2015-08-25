# Simple script for running the tests

from subprocess import call

call(["clear"])                     # Make space on screen
call(["sudo", "make", "install"])   # Make sure the nano files are in the correct place
call(["make", "-j6"])               # Build and run
