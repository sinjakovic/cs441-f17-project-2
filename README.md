# CS441/541 Project 1

## Author(s):

Brandon Sinjakovic


## Date:

09/28/2017


## Description:

This is an implementation of a CPU scheduling simulator. It can simulate First-come, First-served,
shortest job first, priority, and round-robin with information of the jobs given though a text file.
Then statistics are printed out that show the wait time and turnaround for each process and there averages

## How to build the software

To build the software, use the given makefile.
make compliles the software.


## How to use the software

Run the sofware through the command line and 
give the following arguments in any order:

    -s #: where the number must be between 1-4 (required)
    
    txtfile: the text file with the info of the processes (required)
    
    -q #: required only for round robin and the number must be greater than 0
    
## How the software was tested

this software was tested with the given tests and a number of extra tests made
by the authors

## Test Suite

look at tests/README.md


## Known bugs and problem areas

none 