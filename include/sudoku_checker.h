/**
 * @file: checker.h
 * @author: Paul Shen, 576870786, 02, CSCI 360, VIU
 * @version: 1.0.0
 * @modified: 10,14, 2020
 *
 * Defines the functions required for sudoku checker application.
 *
 */



#ifndef __SUDOKU_CHECKER_HEADER__
#define __SUDOKU_CHECKER_HEADER__


#define PUZZLE_SIZE 9 		//sudoku puzzle dimension	
#define NUMBER_OF_THREADS 27	//number of threads that concurrently verify the validity of the sudoku solution
#define LINE_MAX_LENGTH 100	//maximum length of a line in the sudoku solution file


/*
 * Data structure to pass parameters to each worker thread 
 */
typedef struct {
	int thread_no;
	int x;
	int y;
} parameters;



void read_from_file(FILE* sudoku_file);
// Read the solution of a sudoku puzzle line by line from a given FILE pointer
// Parse individual values (separated by comma) from each line and puts at appropriate position
// in an externally difened two dimensional array (global variable) which represents the solution in memory.
// Report error if reading fails


void show_puzzle();
// Show in memory content of the solution of a sudoku puzzle


void* row_worker(void* param);
// Check whether the row of the sudoku puzzle solution referred by the param contains all the digits from 1 to 9
// Set the appropriate status value in status map. The status map is an externally defined one-dimensional array 
// (global variable).


void* col_worker(void* param);
// Check whether the column of the sudoku puzzle solution referred by the param contains all the digits from 1 to 9
// Set the appropriate status value in status map.


void* subgrid_worker(void* param);
// Check whether the subgrid of the sudoku puzzle solution referred by the param contains all the digits from 1 to 9
// Set the appropriate status value in status map.

int check_status_map();
//Loop through the status map, return 1 if all are set, return 0 otherwise.

#endif
