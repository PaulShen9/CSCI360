/**
 * @file: main.c
 * @author: Paul Shen, 576870786, 02, CSCI 360, VIU
 * @version: 1.0.0
 * @modified: 10,14, 2020
 *
 * Sudoku Checker application.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "sudoku_checker.h"


int puzzle[PUZZLE_SIZE+1][PUZZLE_SIZE+1]; 	// In memory solutiona of a sudoku puzzle
int status_map[NUMBER_OF_THREADS];       	// Status maps updated by corresponding worker thread

parameters* worker_params[NUMBER_OF_THREADS]; 	// Array of worker thread parameter pointers
pthread_t workers[NUMBER_OF_THREADS];		// Array of worker threads


int main(int argc, char** argv) {
	//Read the sudoku solution from	the file specified by command line argumant
    //first test the number of command line argument is right or not
    if(argc != 2){
		printf("You have enter wrong numbers of input \n");	
		return 0;
	}
    //open the file
    FILE *ptr;
     ptr = fopen(argv[1],"rw");
    //make sure we can find the file
	if (ptr == NULL){
		printf("cannot find the file \n");
		return 0;
	}
    //pass the ptr to the function
    read_from_file(ptr);
    
    
	//Display the solution to the scree.
    show_puzzle();
    
    int index = 0;//hold the current thread number ,from 0 to 26
    parameters para[50];//the struct 
    
    //Create and run all the row threads with appropriate thread parameters to verify the rows of the solution.
    pthread_t row_thread[9];//create the row thred
    for ( index = 0; index < 9; index++){
		para[index].thread_no = index;
		para[index].x = index;
		if (pthread_create(&row_thread[index],NULL,row_worker,&para[index])){
			printf("somethign is wrong with creating \n");
		}
	}
    //at this point, roll should finished
    
    //Create and run all the col threads with appropriate thread parameters to verify the cols of the solution.
    pthread_t col_thread[9];//create the col thread;
    int colCount = 0;
	for ( colCount = 0; colCount < 9; colCount++){
		para[index].thread_no = index;
		para[index].y = colCount;
		if (pthread_create(&col_thread[colCount],NULL,col_worker,&para[index])){
			printf("somethign is wrong with creating \n");
		}
		index ++;
	}

   //at this point, col should finish
    
	//Create and run all the subgrid threads with appropariate thread parameters to verify the subgrids of the solution.
    pthread_t sub_thread[9];
    
    int subCount = 0;
	int xray = 0;
	int yray = 0;
	while(yray < 7){ 
		while(xray < 7){
			para[index].thread_no = index;
			para[index].y = yray;
			para[index].x = xray;
			if (pthread_create(&sub_thread[subCount],NULL,subgrid_worker,&para[index])){
				printf("somethign is wrong with creating \n");
			}
			subCount ++;
			index ++;
			xray = xray + 3; //since it is a 3X3, so should +3
		}
		xray = 0;
		yray = yray + 3;
	}
	//at this point, sub should finish
	//Wait for all thread to complete.
    //row first
    pthread_join ( row_thread[0], NULL);
    pthread_join ( row_thread[1], NULL);
    pthread_join ( row_thread[2], NULL);
	pthread_join ( row_thread[3], NULL);
    pthread_join ( row_thread[4], NULL);
    pthread_join ( row_thread[5], NULL);
	pthread_join ( row_thread[6], NULL);
    pthread_join ( row_thread[7], NULL);
    pthread_join ( row_thread[8], NULL);
    //col next
    pthread_join ( col_thread[0], NULL);
    pthread_join ( col_thread[1], NULL);
    pthread_join ( col_thread[2], NULL);
	pthread_join ( col_thread[3], NULL);
    pthread_join ( col_thread[4], NULL);
    pthread_join ( col_thread[5], NULL);
	pthread_join ( col_thread[6], NULL);
    pthread_join ( col_thread[7], NULL);
    pthread_join ( col_thread[8], NULL);
    //sub fina
    pthread_join ( sub_thread[0], NULL);
    pthread_join ( sub_thread[1], NULL);
    pthread_join ( sub_thread[2], NULL);
	pthread_join ( sub_thread[3], NULL);
    pthread_join ( sub_thread[4], NULL);
    pthread_join ( sub_thread[5], NULL);
	pthread_join ( sub_thread[6], NULL);
    pthread_join ( sub_thread[7], NULL);
    pthread_join ( sub_thread[8], NULL);
    
	//Check the results from all threads through status map.
	//Display whether the solution is valid or not.
    int returnValue = check_status_map();
    if (returnValue == 1){
        printf("This is a valid sudoku \n.");
    }
    else{
        printf("Sorry, it is not a valid sudoku \n");
    }
    
	return 0;
}
	
