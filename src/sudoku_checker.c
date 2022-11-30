/**
 * @file: sudoku_checker.c
* @author: Paul Shen, 576870786, 02, CSCI 360, VIU
 * @version: 1.0.0
 * @modified: 10,14, 2020
 *
 * Implements the functions required for sudoku checker application.
 *
 */

/*
 * Include all the header files.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "../include/sudoku_checker.h"

//typedef struct {
//	int thread_no;
//	int x;
//	int y;
//} parameters;

extern int puzzle[PUZZLE_SIZE+1][PUZZLE_SIZE+1]; 	// Im memory solutiona of a sudoku puzzle
extern int status_map[NUMBER_OF_THREADS];       	// Status maps updated by corresponding worker thread
int array[LINE_MAX_LENGTH][LINE_MAX_LENGTH];
//use flag for each number
//each flag present one number, for example, once a one is read, the R1 flag will set 
int R1_flag = 0;
int R2_flag = 0;
int R3_flag = 0;
int R4_flag = 0;
int R5_flag = 0;
int R6_flag = 0;
int R7_flag = 0;
int R8_flag = 0;
int R9_flag = 0;

void read_from_file(FILE* sudoku_file){
    
    // Read the solution of a sudoku puzzle line by line from a given FILE pointer
    // Parse individual values (separated by comma) from each line and puts at appropriate position
    // in an externally difened two dimensional array (global variable) which represents the solution in memory.
    // Report error if reading fails
    
    //use 4 values to build a array,also
    int j2 = 0;
	int j = 0;
	int k = 0;
	int k2 = 0;
	int input;
	printf("Inseat the sukudo to the array \n");
	while( j2 < 9 ){
        //since one number and one ",", so we need actually 18 space
		while(j<18){
			fscanf(sudoku_file,"%d",&input);
		    fgetc(sudoku_file);
            array[j2][k] = input;
            k++;	
			j= j + 2;
		}
		j = 0;
		k = 0;
		k2 ++;
		j2++;
	}
    //now the array should contain the sudoku
}

void show_puzzle(){
    // Show in memory content of the solution of a sudoku puzzle
    int row = 0;
    int col = 0;
    while( row < 9 ){
        while ( col < 9 ){
            printf("%d, ", array[row][col]);
            col++;
        }
        printf("\n");
        //reset the col and start the next row
        col = 0;
        row++;
    }
}

void* row_worker(void* param){
// Check whether the row of the sudoku puzzle solution referred by the param contains all the digits from 1 to 9
// Set the appropriate status value in status map. The status map is an externally defined one-dimensional array 
// (global variable).
    parameters *pa =(parameters*) param;
	printf("This is thread %d , it is checking row %d\n ",pa->thread_no,pa->x);
	int i = 0;
	while(i < 9){
		if(array[pa->x][i] == 1){
			R1_flag++;
		}
		else if(array[pa->x][i] == 2){
			R2_flag++;
		}
		else if(array[pa->x][i] == 3){
			R3_flag++;
		}
		else if(array[pa->x][i] == 4){
			R4_flag++;
		}
		else if(array[pa->x][i] == 5){
			R5_flag++;
		}
		else if(array[pa->x][i] == 6){
			R6_flag++;
		}
		else if(array[pa->x][i] == 7){
			R7_flag++;
		}
		else if(array[pa->x][i] == 8){
			R8_flag++;
		}
		else if(array[pa->x][i] == 9){
			R9_flag++;
		}
		i++;
	}
	//check all the flag is set or not, if one flag is not set, it means it is not valid
	if(R1_flag ==1 && R2_flag ==1 && R3_flag ==1 && R4_flag ==1 &&  R5_flag ==1 &&  R6_flag ==1 &&  R7_flag ==1 &&  R8_flag ==1 &&  R9_flag ==1){
		status_map[pa-> thread_no] = 1;
	}
	else{
		status_map[pa-> thread_no] = 0;
	}
	//reset flag
	R1_flag = 0;
	R2_flag = 0;
	R3_flag = 0;
	R4_flag = 0;
	R5_flag = 0;
	R6_flag = 0;
	R7_flag = 0;
	R8_flag = 0;
	R9_flag = 0;
	pthread_exit(NULL);
}
    
void* col_worker(void* param){
    // Check whether the column of the sudoku puzzle solution referred by the param contains all the digits from 1 to 9
    // Set the appropriate status value in status map.
   parameters *pa =(parameters*) param;
	printf("This is thread %d , it is checking col %d\n ",pa->thread_no,pa->y);
	int i = 0;
	while(i < 9){
		if(array[i][pa->y] == 1){
			R1_flag++;
		}
		else if(array[i][pa->y] == 2){
			R2_flag++;
		}
		else if(array[i][pa->y] == 3){
			R3_flag++;
		}	
		else if(array[i][pa->y] == 4){
			R4_flag++;
		}
		else if(array[i][pa->y] == 5){
			R5_flag++;
		}
		else if(array[i][pa->y] == 6){
			R6_flag++;
		}
		else if(array[i][pa->y] == 7){
			R7_flag++;
		}
		else if(array[i][pa->y] == 8){
			R8_flag++;
		}
		else if(array[i][pa->y] == 9){
			R9_flag++;
		}
		i++;
	}
	if(R1_flag ==1 && R2_flag ==1 && R3_flag ==1 && R4_flag ==1 &&  R5_flag ==1 &&  R6_flag ==1 &&  R7_flag ==1 &&  R8_flag ==1 &&  R9_flag ==1){
		status_map[pa-> thread_no] = 1;
	}
	else{
		status_map[pa-> thread_no] = 0;
	}
	R1_flag = 0;
	R2_flag = 0;
	R3_flag = 0;
	R4_flag = 0;
	R5_flag = 0;
	R6_flag = 0;
	R7_flag = 0;
	R8_flag = 0;
	R9_flag = 0;
	pthread_exit(NULL);
  
}

void* subgrid_worker(void* param){
    // Check whether the subgrid of the sudoku puzzle solution referred by the param contains all the digits from 1 to 9
    // Set the appropriate status value in status map.
    parameters *pa =(parameters*) param;
	printf("This is thread %d , it is checking row %d , col %d \n ",pa->thread_no,pa->x, pa->y);   
	printf("\n");
	int col = pa->y;
	int row = pa->x;
	//because it is a 3x3, so need 2 loop to check a 3x3
	for(int x = row; x < row+3;x++){
		for(int y = col; y <col+3;y++){
			if(array[x][y] == 1){
			R1_flag++;
			}
			else if(array[x][y] == 2){
				R2_flag++;
			}
			else if(array[x][y] == 3){
				R3_flag++;
			}
			else if(array[x][y] == 4){
				R4_flag++;
			}
			else if(array[x][y] == 5){
				R5_flag++;
			}
			else if(array[x][y] == 6){
				R6_flag++;
			}
			else if(array[x][y] == 7){
				R7_flag++;
			}
			else if(array[x][y] == 8){
				R8_flag++;
			}
			else if(array[x][y] == 9){
				R9_flag++;
			}
		}
	}
	
	if(R1_flag ==1 && R2_flag ==1 && R3_flag ==1 && R4_flag ==1 &&  R5_flag ==1 &&  R6_flag ==1 &&  R7_flag ==1 &&  R8_flag ==1 &&  R9_flag ==1){
		status_map[pa-> thread_no] = 1;
	}
	else{
		status_map[pa-> thread_no] = 0;
	}
	R1_flag = 0;
	R2_flag = 0;
	R3_flag = 0;
	R4_flag = 0;
	R5_flag = 0;
	R6_flag = 0;
	R7_flag = 0;
	R8_flag = 0;
	R9_flag = 0;
	pthread_exit(NULL);

}

int check_status_map(){
//Loop through the status map, return 1 if all are set, return 0 otherwise.
    int returnValue = 1;//it will become 0 if falg is not set
	int o = 0;//a varrible use to go through the array
	while(o < 27){
		if(status_map[o] != 1){
			returnValue = 0;
		}
		o++;
	}
    return returnValue;
}