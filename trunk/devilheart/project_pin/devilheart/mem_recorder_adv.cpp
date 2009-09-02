/*******************************************************************

 Title:mem_recorder_adv.cpp
 Function:To implement functions of class MemoryRecorderAdv
 Description:
 Source file to implement functions of class MemoryRecorder
 Version: 1.0
 Date and author: 2009.08.07 hsqfire
*******************************************************************/

#include "mem_recorder_adv.h"
#include <math.h>   


/******************************************************************
 Title:MemoryRecorderAdv
 Function:Constructor to initial all the variables of the class
 Input:
 Output:
******************************************************************/
MemoryRecorderAdv::MemoryRecorderAdv()
{
	this->minAddress = DEFAULT_MIN_ADDRESS;
	this->maxAddress = DEFAULT_MAX_ADDRESS;

	hashcode = DEFAULT_HASHCODE;
	amountOfPage = DEFAULT_HASHCODE;
	int sizeOfMemory = this->maxAddress-this->minAddress;
	if(sizeOfMemory%DEFAULT_HASHCODE==0)
		sizeOfPage = sizeOfMemory/DEFAULT_HASHCODE;
	else
		sizeOfPage = sizeOfMemory/DEFAULT_HASHCODE+1;
	memoryList = (MemNode**)malloc(sizeof(MemNode*)*amountOfPage);
	for(int i=0;i<amountOfPage;i++){
		memoryList[i]=NULL;
	}
}

/******************************************************************
 Title:MemoryRecorderAdv
 Function:Constructor to initial all the variables of the class
 Input:
 int code:The hash code.
 Output:
******************************************************************/
MemoryRecorderAdv::MemoryRecorderAdv(int code)
{
	this->minAddress = DEFAULT_MIN_ADDRESS;
	this->maxAddress = DEFAULT_MAX_ADDRESS;

	hashcode = code;
	amountOfPage = code;
	int sizeOfMemory = this->maxAddress-this->minAddress;
	if(sizeOfMemory%code==0)
		sizeOfPage = sizeOfMemory/code;
	else
		sizeOfPage = sizeOfMemory/code+1;
	memoryList = (MemNode**)malloc(sizeof(MemNode*)*amountOfPage);
	for(int i=0;i<amountOfPage;i++){
		memoryList[i]=NULL;
	}
}

/******************************************************************
 Title:MemoryRecorderAdv
 Function:Constructor to initial all the variables of the class
 Input:
 int code:The hash code
 int minAdd:The min address of the memory
 int maxAdd:The max address of the memory
 Output:
******************************************************************/
MemoryRecorderAdv::MemoryRecorderAdv(int minAdd,int maxAdd,int code)
{
	this->minAddress = minAdd;
	this->maxAddress = maxAdd;

	hashcode = code;
	amountOfPage = code;
	int sizeOfMemory = this->maxAddress-this->minAddress;
	if(sizeOfMemory%code==0)
		sizeOfPage = sizeOfMemory/code;
	else
		sizeOfPage = sizeOfMemory/code+1;
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
unsigned int MemoryRecorderAdv::isTainted(unsigned int address)
{
	if(address<minAddress||address>maxAddress){
		return FAULTADDRESS;
	}
	int location=address%hashcode;
	MemNode* node = memoryList[location];
	if (node==NULL){
		return 0; //The node does not exist
	}
	while( node!=NULL && (address!=(node->address)))
		node=node->nextNode;
	if (node==NULL)
		return 0; //The node containing this address does not exist
	if( node->state ==1)
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
bool MemoryRecorderAdv::markTaintedMemory(unsigned int address)
{	
	if(address<minAddress||address>maxAddress){
		return false;
	}
	int location=address%hashcode;
	MemNode *current = memoryList[location];
	if(current==NULL){
		memoryList[location] = (MemNode*)malloc(sizeof(MemNode));
		memoryList[location]->address = address;
		memoryList[location]->nextNode = NULL;
		memoryList[location]->state = (unsigned int)1;
		return true;
	}else{
		MemNode *pre = current;
		current = current->nextNode;
		while(current!=NULL){
			if(address>=current->address){
				if(address=current->address){
					if(current->state==0){
						current->state = 1;
						return true;
					}else{
						return false;
					}
				}else{
					pre->nextNode = (MemNode*)malloc(sizeof(MemNode));
					pre->address = address;
					pre->nextNode = current;
					pre->state = 1;
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
bool MemoryRecorderAdv::dismarkTaintedMemory(unsigned int address)
{
	if(address<minAddress||address>maxAddress){
		return false;
	}
	int location=address%hashcode;
	MemNode *current = memoryList[location];
	if(current==NULL){
		return false;
	}else{
		MemNode *pre = current;
		current = current->nextNode;
		while(current!=NULL){
			if(address>=current->address){
				if(address=current->address){
					int state = current->state;
					if(state==0){
						return false;
					}else{
						current->state = 1;
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
bool MemoryRecorderAdv::markTaintedBlock(unsigned int address, int length)
{
	if(address<minAddress||(address+length)>maxAddress){
		return false;
	}
	int location = 0;
	int currentAdd = address;
	MemNode *currentNode = NULL;
	MemNode *preNode = NULL;
	for(location=0;location<amountOfPage;location++){
		int num = address/hashcode;
		if(address%hashcode>location && (address+length)<(num+1)*hashcode+location)
			continue;
		else if(address%hashcode<location && (address+length)<num*hashcode+location)
			continue;
		else{
			currentAdd = address-address%hashcode+location;
			if(memoryList[location]==NULL){
				memoryList[location] = (MemNode*)malloc(sizeof(MemNode));
				if(minAddress%hashcode<location)
					memoryList[location]->address = minAddress-minAddress%hashcode+location;
				else
					memoryList[location]->address = minAddress+location;
				memoryList[location]->nextNode = NULL;
				
				if(memoryList[location]->address==currentAdd){
					memoryList[location]->state = 1;
					currentAdd += hashcode;
				}else {
					memoryList[location]->state = (unsigned int)0x0;
				}
				location --;
			}else{
				preNode = memoryList[location];
				currentNode = memoryList[location]->nextNode;
				if(preNode->address==currentAdd){
					preNode->state = 1;
					currentAdd += hashcode;
				}
				while(currentAdd<= maxAddress && currentAdd<=address+length-1){
					if(currentNode==null){
						preNode->nextNode = (MemNode*)malloc(sizeof(MemNode));
						currentNode = preNode->nextNode;
						currentNode->address = currentAdd;
						currentNode->nextNode = NULL;
						currentNode->state = 1;
						currentAdd += hashcode;
						preNode = currentNode;
						currentNode = currentNode->nextNode;
					}else{
						if(currentNode->address<currentAdd){
							preNode = currentNode;
							currentNode = currentNode->nextNode;
						}else if(currentNode->address==currentAdd){
							currentNode->state = 1;
							currentAdd += 32;
							preNode = currentNode;
							currentNode = currentNode->nextNode;
						}else{
							preNode->nextNode = (MemNode*)malloc(sizeof(MemNode));
							preNode->nextNode->address = currentAdd;
							preNode->nextNode->nextNode = currentNode;
							preNode->nextNode->state = 1;
							currentAdd += hashcode;
							preNode = preNode->nextNode;
						}
					}
				}
			}
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
bool MemoryRecorderAdv::dismarkTaintedBlock(unsigned int address, int length)
{   
	if(address<minAddress||(address+length)>maxAddress){
		return false;
	}
	int location=address%hashcode;
	int currentAdd = address;
	MemNode *currentNode = NULL;
	MemNode *preNode = NULL;
	for(location=0;location<amountOfPage;location++){
		int num = address/hashcode;
		if(address%hashcode>location && (address+length)<(num+1)*hashcode+location)
			continue;
		else if(address%hashcode<location && (address+length)<num*hashcode+location)
			continue;
		else{
			currentAdd = address-address%hashcode+location;
			if(memoryList[location]==NULL){
				continue;
			}else{
				preNode = memoryList[location];
				currentNode = memoryList[location]->nextNode;
				if(preNode->address==currentAdd){
					memoryList[location]=NULL;
					continue;
				}
				while(currentNode!=NULL){
					if(currentNode->address<address){
						preNode = currentNode;
						currentNode = currentNode->nextNode;
					}else if(currentNode->address>address){
						break;
					}else{
						preNode->nextNode = currentNode->nextNode;
						currentNode = currentNode->nextNode;
					}
				}
			}
		}
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
bool MemoryRecorderAdv::dismarkTaintedBlock(unsigned int address, int length,int state)
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
void MemoryRecorderAdv::clearState()
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
void MemoryRecorderAdv::printState(FILE *output)
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