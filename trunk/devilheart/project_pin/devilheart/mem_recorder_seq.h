/*******************************************************************

 Title:mem_recorder_seq.h
 Function:Define some data structor to record the state of memory
 Description:
 Define some data structors to record the state of memory in size of
 4G at most.
 Version: 1.2
 Date and author: 2009.08.07 hsqfire
*******************************************************************/

#ifndef _MEM_RECORDER_SEQ_H
#define _MEM_RECORDER_SEQ_H

#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include "mem_recorder.h"

/* this class is responsible for recording states of
   all memory                                      */
class MemoryRecorderSeq{

private:
	int amountOfPage;         /* amount of pages   */
	int sizeOfPage;           /* size of a page    */
	unsigned int minAddress;  /* minimun address   */
	unsigned int maxAddress;  /* maximun address   */
	MemNode *(*memoryList);   /* MemNode lists     */

public:
	/* Constructor with no arguments               */
	MemoryRecorderSeq();

	/* Constructor with sizeOfPage argument        */
	MemoryRecorderSeq(int size);

	/* Constructor with 3 arguments                */
	MemoryRecorderSeq(int minAdd,int maxAdd,int size);

	/* Return whether the memory in this address is
	   tainted or not                              */
	unsigned int isTainted(unsigned int address);
	/* Mark the memroy in the address to be tainted*/
	bool markTaintedMemory(unsigned int address);

	/* Dismark the memroy in this address          */
	bool dismarkTaintedMemory(unsigned int address);

	/* Reset the state of memory                   */
	void clearState();

	/* Mark a block of continuous memory           */
	bool markTaintedBlock(unsigned int address, int length);

	/* dismark a block of continuous memory           */
	bool dismarkTaintedBlock(unsigned int address, int length);

	/* Mark a block of continuous memory with the state*/
	bool dismarkTaintedBlock(unsigned int address, int length,int state);

	/* Print the state of memory to the output file*/
	void printState(FILE *output);
};

#endif