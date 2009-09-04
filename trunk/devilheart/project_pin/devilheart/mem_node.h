/*******************************************************************

 Title:mem_node.h
 Function:Define some data structor to record the state of memory
 Description:
 Define some data structors to record the state of memory in size of
 4G at most.
 Version: 1.2
 Date and author: 2009.07.16 hsqfire
*******************************************************************/

#ifndef _MEM_NODE_H
#define _MEM_NODE_H

#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include "mem_recorder.h"


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

#endif