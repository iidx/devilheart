/*******************************************************************

 Title:mem_recorder.h
 Function:Define some data structor to record the state of memory
 Description:
 Define some data structors to record the state of memory in size of
 4G at most.
 Version: 1.1
 Date and author: 2009.07.16 hsqfire
*******************************************************************/

#ifndef _MEM_RECORDER_H
#define _MEM_RECORDER_H

#include <stdlib.h>

/* default size of one page in memory*/
#define DEFALUT_PAGE_SIZE 1024

/* Struct to represent 8 continuous bytes in memory*/
struct MemNode;

struct MemNode{
	/* An unsigned integer to record the state of 32 
	   continuous bytes in memory.
	   Here the lower bit represents the lower byte 
	   of the memory. 
	   Value 0 means this byte of memory is not 
	   tainted and 1 means tainted.                */
	unsigned int state;

	/* Address of the first(the lowest one) byte of
	   the represented memory.                     */
	unsigned int address;

	/* Pointer to next 32 continuous bytes in memory*/
	MemNode *nextNode;
};


/* this class is responsible for recording states of
   all memory                                      */
class MemoryRecorder{

private:
	int amountOfPage;         /* amount of pages   */
	int sizeOfPage;           /* size of a page    */
	unsigned int minAddress;  /* minimun address   */
	unsigned int maxAddress;  /* maximun address   */
	MemNode *(*memoryList);   /* MemNode lists     */

public:
	/* Constructor with no arguments               */
	MemoryRecorder();

	/* Constructor with sizeOfPage argument        */
	MemoryRecorder(int size);

	/* Return whether the memory in this address is
	   tainted or not                              */
	unsigned int isTainted(unsigned int address);

	/* Mark the memroy in the address to be tainted*/
	bool markTaintedMemory(unsigned int address);

	/* Dismark the memroy in this address          */
	bool dismarkTaintedMemory(unsigned int address);

	/* reset the state of memory                   */
	void clearState();
};

#endif