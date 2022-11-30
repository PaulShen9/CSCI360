#Makefile for assignment 2


CC = gcc
WFLAG = -Wall
CFLAG = -c
OFLAG = -o
DFLAG = -ggdb
IFLAG = -I


BINARY = bin
OBJECT = build
SOURCE = src
INCLUDE = include
RESOURCE = resource



${BINARY}/sudoku_checker: ${OBJECT}/main.o ${OBJECT}/sudoku_checker.o
	${CC} ${WFALG} ${DFLAG} -lpthread ${OFLAG} ${BINARY}/sudoku_checker ${OBJECT}/main.o ${OBJECT}/sudoku_checker.o


${OBJECT}/main.o: ${INCLUDE}/sudoku_checker.h ${SOURCE}/main.c
	${CC} ${WFLAG} ${CFLAG} ${DFLAG} ${IFLAG} ${INCLUDE} ${OFLAG} ${OBJECT}/main.o ${SOURCE}/main.c


${OBJECT}/sudoku_checker.o: ${INCLUDE}/sudoku_checker.h ${SOURCE}/sudoku_checker.c
	${CC} ${WFLAG} ${CFLAG} ${DFLAG} ${IFLAG} ${INCLUDE} ${OFLAG} ${OBJECT}/sudoku_checker.o ${SOURCE}/sudoku_checker.c



.PHONY: clean run



clean:
	rm -rf ${BINARY}/* ${OBJECT}/*


run: ${BINARY}/sudoku_checker ${RESOURCE}/sudoku_valid.txt ${RESOURCE}/sudoku_invalid.txt
	${BINARY}/sudoku_checker ${RESOURCE}/sudoku_valid.txt
	${BINARY}/sudoku_checker ${RESOURCE}/sudoku_invalid.txt


