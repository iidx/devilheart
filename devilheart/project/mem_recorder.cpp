/*******************************************************************

 Title:mem_recorder.cpp
 Function:To implement functions of class MemoryRecorder
 Description:
 Source file to implement functions of class MemoryRecorder
 Version: 1.0
 Date and author: 2009.07.16 hsqfire, Jiang Bo
*******************************************************************/

#include "mem_recorder.h"
#include <math.h>   


/******************************************************************
 Title:MemoryRecorder
 Function:Constructor to initial all the variables of the class
 Input:
 Output:
******************************************************************/
MemoryRecorder::MemoryRecorder()
{

    sizeOfPage = DEFAULT_PAGE_SIZE;
	this->minAddress = DEFAULT_MIN_ADDRESS;
	this->maxAddress = DEFAULT_MAX_ADDRESS;

	if((maxAddress-minAddress)%sizeOfPage==0)
	    amountOfPage = (maxAddress-minAddress)/sizeOfPage;
	else
        amountOfPage = (maxAddress-minAddress)/sizeOfPage+1;
	memoryList = (MemNode**)malloc(sizeof(MemNode*)*amountOfPage);
	for(int i=0;i<amountOfPage;i++){
		memoryList[i]=NULL;
	}

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
	sizeOfPage = size;
	this->minAddress = DEFAULT_MIN_ADDRESS;
	this->maxAddress = DEFAULT_MAX_ADDRESS;
	if(((unsigned int)size)>maxAddress-minAddress)
		sizeOfPage = DEFAULT_PAGE_SIZE;
	if((maxAddress-minAddress)%sizeOfPage==0)
	    amountOfPage = (maxAddress-minAddress)/sizeOfPage;
	else
        amountOfPage = (maxAddress-minAddress)/sizeOfPage+1;
	memoryList = (MemNode**)malloc(sizeof(MemNode*)*amountOfPage);
	for(int i=0;i<amountOfPage;i++){
		memoryList[i]=NULL;
	}
}

/******************************************************************
 Title:MemoryRecorder
 Function:Constructor to initial all the variables of the class
 Input:
 int size:The size of a page in memory
 int minAdd:The min address of the memory
 int maxAdd:The max address of the memory
 Output:
******************************************************************/
MemoryRecorder::MemoryRecorder(int minAdd,int maxAdd,int size)
{
	sizeOfPage = size;
	this->minAddress = minAdd;
	this->maxAddress = maxAdd;
	if(((unsigned int)size)>maxAddress-minAddress)
		sizeOfPage = DEFAULT_PAGE_SIZE;
	if((maxAddress-minAddress)%sizeOfPage==0)
	    amountOfPage = (maxAddress-minAddress)/sizeOfPage;
	else
        amountOfPage = (maxAddress-minAddress)/sizeOfPage+1;
	memoryList = (MemNode**)malloc(sizeof(MemNode*)*amountOfPage);
	for(int i=0;i<amountOfPage;i++){
		memoryList[i]=NULL;
	}
}


/******************************************************************
 Title:iaTainted
 Function:Return the result of whether the memory in this address is
 tainted or not
 Input:
 unsigned int address:The address of the memory of one byte.
 Output:
 unsigned int
 Return value:0 is not tainted, 1 is tainted, -1 is wrong address
******************************************************************/
unsigned int MemoryRecorder::isTainted(unsigned int address)
{
	if(address<minAddress||address>maxAddress)
		return FAULTADDRESS; //wrong memory address
	int location=(address-minAddress)/sizeOfPage;
	MemNode* node = memoryList[location];
	while( ((address>(node->address+31)) | (address<(node->address)))&&
		node!=NULL)
		node=node->nextNode;
	if (node==NULL)
		return 0; //The node containing this address does not exist
	int section=address-(node->address);
	if( ((node->state>>section)&0x1) ==1)
			return 1; //1 is taited
	else  //((node->state>>section)&0x1) ==0
			return 0; //0 is not taited
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
	if(address<minAddress||address>maxAddress)
		return false; //wrong memory address
	int location=(address-minAddress)/sizeOfPage;
    MemNode* node = memoryList[location];
	//The list is empty
    if (node==NULL){
		MemNode n;    
		int _address=address-address%32;
		int _state=0|(int)(pow(2.0,address%32-1.0));
		n.address=_address;
		n.state=_state;	 
		n.nextNode = NULL;
		memoryList[location]=&n;
		return true;
	}
	MemNode* a=node; //Pre node of the current node
	//Find the memory node in the address	
	while( (node!=NULL) && ((address>(node->address+31)) | (address<(node->address)))  ){ 	
		a = node;
		node=node->nextNode;
		//node=a;
	} 
	//The memory node in the address is not existed
	if( node==NULL ){      
		 MemNode n;    
		 int _address=address-address%32;
		 int _state=0|(int)(pow(2.0,address%32-1.0));
		 n.address=_address;
		 n.state=_state;
		 n.nextNode = NULL;
		 a->nextNode=&n;
		 return true;
	}
	else{	
		int section=address-(node->address);
		if( ((node->state>>section)&0x1) ==1)
			return false;//The memory in the address is already tainted.
		else{ // ((node->state>>section)&0x1) ==0	
			node->state=node->state|(int)(pow(2.0,section-1.0));
			return true;//Mark it tainted successfully
		}
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
	if(address<minAddress||address>maxAddress)
		return false; //wrong memory address
	int location=(address-minAddress)/sizeOfPage;
	MemNode* node = memoryList[location];
	if (node==NULL){
		return false; //The node does not exist
	}
	MemNode* a=node; //Pre node of the current node
	//Find the memory node in the address
	while( (node!=NULL) & ((address>(node->address+31)) | (address<(node->address)))  ){ 
		a = node;
		node = node->nextNode;
	}
	//The memory node in the address is not existed
	if( node==NULL ){       
		return false;
	}
	else{	
		int section=address-(node->address);	
		if( ((node->state>>section)&0x1) ==0)
			return false;//The memory in the address is not tainted.	
		else{ // ((node->state>>section)&0x1) ==1         
			node->state=node->state&(0xFFFFFFFF-(int)(pow(2.0,section-1.0)));
			if(node->state!=0)
				return true;//Dismark it successfully
			else{ //state is 0,delete this node
				a->nextNode=node->nextNode;
				delete node;
				return true;
			}
		}
	}
}

/******************************************************************
 Title:clearState
 Function:Reset the state of memory
 Input:
 Output:
 void
******************************************************************/
void MemoryRecorder::clearState()
{
	int length=amountOfPage;
	for(int i=0;i<length;i++){
	  memoryList[i]=NULL;
	}
}
