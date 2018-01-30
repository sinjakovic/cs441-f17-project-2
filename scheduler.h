/*
 * Brandon Sinjakovic
 * 
 * 09/28/07
 *
 * The header file for scheduler.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


/******************************
 * Defines
 ******************************/


/******************************
 * Structures
 ******************************/
 struct process {
     int identifier;
     int length;
     int priority;
     int wait_time;
     int time;
     int time_left;
 };


/******************************
 * Global Variables
 ******************************/
struct process **processes;
struct process **original_processes;
int quantum;
char * file;
char * scheduler;
int num_processes;
bool has_s = false;
bool is_valid = true;
bool has_q = false;
bool needs_q = false;
/******************************
 * Function declarations
 ******************************/
 
/* 
 * Description:
 *    processess the comand line arguments and checks also chekcs if 
 *    the arguments are valid.
 *
 * Parameters:
 *    argc: an integer value of how many arguments there are
 *    argv: a string array that contain the arguments
 * 
 * Returuns:
 *    Nothing
 */
void process_cmdline(int argc, char **argv);

/* 
 * Description:
 *    reads in the givin text file and makes an array of prcesses 
 *
 * Parameters:
 *    file_name: a string representing the file name
 * 
 * Returuns:
 *    Nothing
 */
void read_file(char *file_name);

/* 
 * Description:
 *    orders the processes based on the given scheduling algorithim 
 *    given by command ine arguments
 *
 * Parameters:
 *    None
 * 
 * Returuns:
 *    Nothing
 */
void order_processes();

/* 
 * Description:
 *    compares twp processes based on their cpu burst times
 *
 * Parameters:
 *    first: a pointer to a process struc
 *    sec: a pointer to a process struc
 * 
 * Returuns:
 *    an integer representing if first is bigger or smaller than sec
 */
int compare_burst(const void *first, const void *sec);

/* 
 * Description:
 *    compares twp processes based on their priority
 *
 * Parameters:
 *    first: a pointer to a process struc
 *    sec: a pointer to a process struc
 * 
 * Returuns:
 *    an integer representing if first is bigger or smaller than sec
 */
int compare_priority(const void *first, const void *sec);

/* 
 * Description:
 *    calculates the wait time and turnaround time for each process
 *    and prints it out. It also calculates and prints out the average 
 *    wait time and turnaround time.
 *
 * Parameters:
 *    None
 * 
 * Returuns:
 *    Nothing
 */
void calculate_time();