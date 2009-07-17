/*******************************************************************

 Title:mem_recorder.cpp
 Function:To implement functions of class MemoryRecorder
 Description:
 Source file to implement functions of class MemoryRecorder
 Version: 1.0
 Date and author: 2009.07.16 hsqfire, Jiang Bo
*******************************************************************/

#include "mem_recorder.h"
#include   <math.h>   


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
	
	int location=(address-minAddress)/sizeOfPage;
	
	MemNode* node = memoryList[location];
  
	if (node==NULL)
		return 0;
	
	else{
    
	while( (address>(node->address+31)) | (address<(node->address)))
		node=node->nextNode;

	int section=address-(node->address);
	
	if( ((node->state>>section)&0x1) ==1)
			return 1;//1 is taited
	if( ((node->state>>section)&0x1) ==0)
			return 0;//0 is not taited
	
	
	}

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
	
	int location=(address-minAddress)/sizeOfPage;
	
	MemNode* node = memoryList[location];

   while( (address>(node->address+31)) | (address<(node->address)))
		node=node->nextNode;

	int section=address-(node->address);
	
	if( ((node->state>>section)&0x1) ==1)
			return false;//The memory in the address is already tainted.
	
	if( ((node->state>>section)&0x1) ==0){
		
		    node->state=node->state|(int)(pow(2.0,section-1.0));
			return true;//
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

	int location=(address-minAddress)/sizeOfPage;
	
	MemNode* node = memoryList[location];

    while( (address>(node->address+31)) | (address<(node->address)))
		node=node->nextNode;

	int section=address-(node->address);
	
	if( ((node->state>>section)&0x1) ==0)
			return false;//The memory in the address is not tainted.
	if( ((node->state>>section)&0x1) ==1)
			return true;//
	
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