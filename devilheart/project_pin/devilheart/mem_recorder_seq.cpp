/*******************************************************************

 Title:mem_recorder_seq.cpp
 Function:To implement functions of class MemoryRecorderSeq
 Description:
 Source file to implement functions of class MemoryRecorder
 Version: 1.0
 Date and author: 2009.08.07 hsqfire
*******************************************************************/

#include "mem_recorder_seq.h"
#include <math.h>   


/******************************************************************
 Title:MemoryRecorderSeq
 Function:Constructor to initial all the variables of the class
 Input:
 Output:
******************************************************************/
MemoryRecorderSeq::MemoryRecorderSeq()
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
 Title:MemoryRecorderSeq
 Function:Constructor to initial all the variables of the class
 Input:
 int size:The size of a page in memory
 Output:
******************************************************************/
MemoryRecorderSeq::MemoryRecorderSeq(int size)
{
	
	if(size%32==0)
	     sizeOfPage = size;
	else{
	     if(size%32<16)
			 sizeOfPage=size-size%32;
		 else
			 sizeOfPage=size-size%32+32;
	
	}

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
 Title:MemoryRecorderSeq
 Function:Constructor to initial all the variables of the class
 Input:
 int size:The size of a page in memory
 int minAdd:The min address of the memory
 int maxAdd:The max address of the memory
 Output:
******************************************************************/
MemoryRecorderSeq::MemoryRecorderSeq(int minAdd,int maxAdd,int size)
{
	if(size%32==0)
	     sizeOfPage = size;
	else{
	     if(size%32<16)
			 sizeOfPage=size-size%32;
		 else
			 sizeOfPage=size-size%32+32;
	
	}
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
unsigned int MemoryRecorderSeq::isTainted(unsigned int address)
{
	if(address<minAddress||address>maxAddress){
		return FAULTADDRESS;
	}
	int location=(address-minAddress)/sizeOfPage;
	MemNode* node = memoryList[location];
	if (node==NULL){
		return 0; //The node does not exist
	}
	while( node!=NULL && address>(node->address+31))
		node=node->nextNode;
	if (node==NULL||node->address>address)
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
bool MemoryRecorderSeq::markTaintedMemory(unsigned int address)
{	
	if(address<minAddress||address>maxAddress){
		return false;
	}
	int location=(address-minAddress)/sizeOfPage;
	MemNode *current = memoryList[location];
	int section = address%32;
	if(current==NULL){
		memoryList[location] = (MemNode*)malloc(sizeof(MemNode));
		memoryList[location]->address = address - address%32;
		memoryList[location]->nextNode = NULL;
		memoryList[location]->state = (unsigned int)(1<<section);
		return true;
	}else{
		if(current->address<=address&&address<(current->address+32)){
			int state = current->state&((unsigned int)(1<<section));
			if(state==0){
				current->state = current->state|((unsigned int)(1<<section));
				return true;
			}else{
				return false;
			}
		}
		MemNode *pre = current;
		current = current->nextNode;
		while(current!=NULL){
			if(address>=current->address){
				if(address<=(current->address+31)){
					int state = current->state&((unsigned int)(1<<section));
					if(state==0){
						current->state = current->state|((unsigned int)(1<<section));
						return true;
					}else{
						return false;
					}
				}else{
					pre->nextNode = (MemNode*)malloc(sizeof(MemNode));
					pre->address = address - address%32;
					pre->nextNode = current;
					pre->state = (unsigned int)(1<<section);
					return true;
				}
			}else{
				pre = current;
				current = current->nextNode;
			}
		}
		return false;
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
bool MemoryRecorderSeq::dismarkTaintedMemory(unsigned int address)
{
	if(address<minAddress||address>maxAddress){
		return false;
	}
	int location=(address-minAddress)/sizeOfPage;
	MemNode *current = memoryList[location];
	int section = address%32;
	if(current==NULL){
		return false;
	}else{
		MemNode *pre = current;
		current = current->nextNode;
		while(current!=NULL){
			if(address>=current->address){
				if(address<=(current->address+31)){
					int state = current->state&((unsigned int)(1<<section));
					if(state==0){
						return false;
					}else{
						current->state = current->state&((unsigned int)(0xffffffff-(1<<section)));
						return true;
					}
				}else{
					return false;
				}
			}else{
				pre = current;
				current = current->nextNode;
			}
		}
		return false;
	}
}

/******************************************************************
 Title:markTaintedBlock
 Function:Mark the memroy in the address to be tainted
 Input:
 unsigned int address:The first address of the block.
 int length:The length of the block.
 Output:
 bool
 Return value:true is successful, false means exception
******************************************************************/
bool MemoryRecorderSeq::markTaintedBlock(unsigned int address, int length)
{   
	if(address<minAddress||(address+length)>maxAddress){
		return false;
	}
	int location=(address-minAddress)/sizeOfPage;
	unsigned int currentAdd = address;
	MemNode *currentNode = NULL;
	MemNode *preNode = NULL;
	while(currentAdd<=address+length-1){
		if(memoryList[location]==NULL){
			memoryList[location] = (MemNode*)malloc(sizeof(MemNode));
			memoryList[location]->address = minAddress+sizeOfPage*location;
			memoryList[location]->nextNode = NULL;
			int tmp;
			if((currentAdd+31)>(address+length-1)){
				tmp = address+length-currentAdd;
			}else{
				tmp = 32;
			}
			if(memoryList[location]->address<=currentAdd && memoryList[location]->address+32>currentAdd){
				memoryList[location]->state = (unsigned int)(0xffffffff>>(32-tmp))<<(currentAdd-memoryList[location]->address);
				currentAdd += 32;
				continue;
			}else if(memoryList[location]->address+32<=currentAdd){
				memoryList[location]->state = (unsigned int)0x0;
				continue;
			}
		}else{
			preNode = memoryList[location];
			currentNode = memoryList[location]->nextNode;
			if(preNode->address<=currentAdd && preNode->address+32>currentAdd){
				int tmp;
				if((currentAdd+31)>(address+length-1)){
					tmp = address+length-currentAdd;
				}else{
					tmp = 32;
				}
				preNode->state = preNode->state|((unsigned int)(0xffffffff>>(32-tmp))<<(currentAdd-preNode->address));
				currentAdd += 32;
			}else if(preNode->address>currentAdd){
				memoryList[location] = (MemNode*)malloc(sizeof(MemNode));
				memoryList[location]->address = minAddress+sizeOfPage*location;
				memoryList[location]->nextNode = preNode;
				int tmp;
				if((currentAdd+31)>(address+length-1)){
					tmp = address+length-currentAdd;
				}else{
					tmp = 32;
				}
				if(memoryList[location]->address<=currentAdd && memoryList[location]->address+32>currentAdd){
					memoryList[location]->state = (unsigned int)(0xffffffff>>(32-tmp))<<(currentAdd-memoryList[location]->address);
					currentAdd += 32;
				}else if(memoryList[location]->address+32<=currentAdd){
					memoryList[location]->state = (unsigned int)0x0;
				}
				currentNode = preNode;
				preNode = memoryList[location];
			}
			while(currentAdd<memoryList[location]->address+sizeOfPage && currentAdd<=address+length-1){
				if(currentNode==NULL){
					preNode->nextNode = (MemNode*)malloc(sizeof(MemNode));
					currentNode = preNode->nextNode;
					currentNode->address = currentAdd-currentAdd%32;
					currentNode->nextNode = NULL;
					int tmp;
					if((currentAdd+31)>(address+length-1)){
						tmp = address+length-currentAdd;
					}else{
						tmp = 32;
					}
					currentNode->state = (unsigned int)(0xffffffff>>(32-tmp))<<(currentAdd-currentNode->address);
					currentAdd += 32;
					preNode = currentNode;
					currentNode = currentNode->nextNode;
				}else{
					if(currentNode->address+31<currentAdd){
						preNode = currentNode;
						currentNode = currentNode->nextNode;
					}else if(currentNode->address<=currentAdd){
						int tmp;
						if((currentAdd+31)>(address+length-1)){
							tmp = address+length-currentAdd;
						}else{
							tmp = 32;
						}
						currentNode->state = currentNode->state|((unsigned int)(0xffffffff>>(32-tmp))<<(currentAdd-currentNode->address));
						currentAdd += 32;
						preNode = currentNode;
						currentNode = currentNode->nextNode;
					}else{
						preNode->nextNode = (MemNode*)malloc(sizeof(MemNode));
						preNode->nextNode->address = currentAdd-currentAdd%32;
						preNode->nextNode->nextNode = currentNode;
						int tmp;
						if((currentAdd+31)>(address+length-1)){
							tmp = address+length-currentAdd;
						}else{
							tmp = 32;
						}
						preNode->nextNode->state = (unsigned int)(0xffffffff>>(32-tmp))<<(currentAdd-preNode->nextNode->address);
						currentAdd += 32;
						preNode = preNode->nextNode;
					}
				}
			}
			location++; //change to next list
		}
	}
	return true;
}


/******************************************************************
 Title:dismarkTaintedBlock
 Function:Dismark the memroy in the address to be not tainted
 Input:
 unsigned int address:The first address of the block.
 int length:The length of the block.
 Output:
 bool
 Return value:true is successful, false means exception
******************************************************************/
bool MemoryRecorderSeq::dismarkTaintedBlock(unsigned int address, int length)
{   
	if(address<minAddress||(address+length)>maxAddress){
		return false;
	}
	int location=(address-minAddress)/sizeOfPage;
	int currentAdd = address;
	MemNode *currentNode = NULL;
	MemNode *preNode = NULL;
	while(sizeOfPage*location+minAddress<address+length){
		if(memoryList[location]!=NULL){
			preNode = memoryList[location];
			currentNode = memoryList[location]->nextNode;
			if(preNode->address<=address+length && preNode->address+32>address){
				int tmp;
				if(preNode->address<=address){
					preNode->state = preNode->state-((unsigned int)(0xffffffff)<<(address-preNode->address));
				}else{
					preNode->state = 0;
				}
				if(preNode->state==0){
					memoryList[location]=NULL;
					continue;
				}
			}
			while(currentNode!=NULL&&currentNode->address<address+length){
				if(currentNode->address+31<address){
					preNode = currentNode;
					currentNode = currentNode->nextNode;
				}else if(currentNode->address<address){
					currentNode->state = currentNode->state-((unsigned int)(0xffffffff)<<(address-currentNode->address));
					preNode = currentNode;
					currentNode = currentNode->nextNode;
				}else{
					preNode->nextNode = currentNode->nextNode;
					currentNode = currentNode->nextNode;
				}
			}
		}
		location++; //change to next list
	}
	return true;
}

/******************************************************************
 Title:markBlock
 Function:Mark the memroy in the address to be tainted or not
 Input:
 unsigned int address:The first address of the block.
 int length:The length of the block.
 int State:1 means is marked tainted. 0 means is marked untainted.
 Output:
 bool
 Return value:true is successful, false means such exception
******************************************************************/
bool MemoryRecorderSeq::dismarkTaintedBlock(unsigned int address, int length,int state)
{   
	
    if(state==1)
		return markTaintedBlock(address,length);
	else if(state==0)
		return dismarkTaintedBlock(address,length);
	else
		return false;

}

/******************************************************************
 Title:clearState
 Function:Reset the state of memory
 Input:
 Output:
 void
******************************************************************/
void MemoryRecorderSeq::clearState()
{
	int length=amountOfPage;
	for(int i=0;i<length;i++){
	  memoryList[i]=NULL;
	}
}


/******************************************************************
 Title:printState
 Function:Print the state of memory to the output file
 Input:
 FILE *output:Pointer to the output file
 Output:
 void
******************************************************************/
void MemoryRecorderSeq::printState(FILE *output)
{
	for(int i=0;i<amountOfPage;i++){
		MemNode *node = this->memoryList[i];
		while(node!=NULL){
			fprintf(output,"taint at 0x%x to 0x%x\n",node->address,node->address+31);
			for(int j=0;j<32;j++){
				unsigned int tmp = 1;
				if((node->state&(tmp<<j))!=0){
					fprintf(output,"0x%x ",node->address+j);
				}
			}
			node = node->nextNode;
			fprintf(output,"\n");
		}
	}
}