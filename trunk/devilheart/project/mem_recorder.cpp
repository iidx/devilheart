/*******************************************************************

 Title:mem_recorder.cpp
 Function:To implement functions of class MemoryRecorder
 Description:
 Source file to implement functions of class MemoryRecorder
 Version: 1.0
 Date and author: 2009.07.16 hsqfire, Jiang Bo
*******************************************************************/

#include "mem_recorder.h"


/******************************************************************
 Title:MemoryRecorder
 Function:Constructor to initial all the variables of the class
 Input:
 Output:
******************************************************************/
MemoryRecorder::MemoryRecorder()
{
}

/******************************************************************
 Title:MemoryRecorder
 Function:Constructor to initial all the variables of the class
 Input:
 int size:The size of a page in memory
 Output:
******************************************************************/
MemoryRecorder::MemoryRecorder(int size)
{
	sizeOfPage=size;
}

/******************************************************************
 Title:docount
 Function:Return the result of whether the memory in this address is
 tainted or not
 Input:
 unsigned int address:The address of the memory of one byte.
 Output:
 unsigned int
 Return value:0 is not tainted, 1 is tainted.
******************************************************************/
/* Return whether the memory in this address is
   tainted or not                              */
unsigned int MemoryRecorder::isTainted(unsigned int address)
{
	

	while((*memoryList)->address!=address)
		(*memoryList)=(*memoryList)->nextNode;
	
	
	
	if((*memoryList)->state==1)
			return 1;//1 is taited
		if((*memoryList)->state==0)
			return 0;//0 is not taited
	
	
	}



/******************************************************************
 Title:markTaintedMemory
 Function:Mark the memroy in the address to be tainted
 Input:
 unsigned int address:The address of the memory of one byte.
 Output:
 bool
 Return value:true is successful, false means such memory is already
 tainted.
******************************************************************/
bool MemoryRecorder::markTaintedMemory(unsigned int address)
{
	
	while((*memoryList)->address!=address)
		(*memoryList)=(*memoryList)->nextNode;
	
	
	
	if((*memoryList)->state==1)
			return false;//The memory in the address is already tainted
		if((*memoryList)->state==0)
		{  
			(*memoryList)->state=1;
			return true;//Mark the memory in the address tainted successfully

		}
}


/******************************************************************
 Title:dismarkTaintedMemory
 Function:Dismark the memroy in the address to be tainted
 Input:
 unsigned int address:The address of the memory of one byte.
 Output:
 bool
 Return value:true is successful, false means such memory is not
 tainted.
******************************************************************/
bool MemoryRecorder::dismarkTaintedMemory(unsigned int address)
{

	while((*memoryList)->address!=address)
		(*memoryList)=(*memoryList)->nextNode;
	
	
	
	if((*memoryList)->state==0)
			return false;//The memory in the address is not tainted
		if((*memoryList)->state==1)
		{
			(*memoryList)->state==0;
			return true;//Dismark the memory in the address tainted successfully

		}
}


/******************************************************************
 Title:clearState
 Function:Reset the state of memory
 Input:
 Output:
 void
******************************************************************/
void clearState()
{
}