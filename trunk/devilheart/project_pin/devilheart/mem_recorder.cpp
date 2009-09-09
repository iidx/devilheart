/*******************************************************************

 Title:mem_recorder.cpp
 Function:To implement functions of class MemoryRecorder
 Description:
 Source file to implement functions of class MemoryRecorder
 Version: 1.2
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
	memoryList=new List[amountOfPage];
	for(int i=0;i<amountOfPage;i++){
		memoryList[i].MakeEmpty();
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
	memoryList=new List[amountOfPage];
	for(int i=0;i<amountOfPage;i++){
		memoryList[i].MakeEmpty();
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
	memoryList=new List[amountOfPage];
	for(int i=0;i<amountOfPage;i++){
		memoryList[i].MakeEmpty();
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
	List list=memoryList[location];
	ListItr it(list);
	if(list.IsEmpty()){
		return 0;
	}
	int a=it.Find(address);
	if(a==0) return 0;
	else{
		int section=address-(it.Current->address);
		if( ((it.Current->state>>section)&0x1) ==1)
		return 1; //1 is taited
	else  //((node->state>>section)&0x1) ==0
		return 0; //0 is not taited
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
	if(address<minAddress||address>maxAddress)
		return false; //wrong memory address
	int location=(address-minAddress)/sizeOfPage;
	int startNodeAddress=address-address%32;
	int _state=0|(int)(pow(2.0,(double)(address%32)));
   
	List list=memoryList[location];
	ListItr it(list);
	if(list.IsEmpty()){
		it.Insert(_state,startNodeAddress);
		return true;
	}
	int a=it.Find(address);
	if(a==0){
		it.Insert(_state,startNodeAddress);
		return true;
	}
	else{
		int section=address-(it.Current->address);
		if( ((it.Current->state>>section)&0x1) ==1)
			return true;//The memory in the address is already tainted.
		else{ // ((it.Current->state>>section)&0x1) ==0	
			it.Current->state=it.Current->state|(int)(pow(2.0,(double)section));
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
	
    List list=memoryList[location];
	ListItr it(list);
	if(list.IsEmpty()){
		return true;
	}
	int a=it.Find(address);
	if(a==0){
		return true;
	}
	else{
		int section=address-(it.Current->address);
		if( ((it.Current->state>>section)|0x0) ==0)
			return true;//The memory in the address is not tainted.	
		else{ // ((it.Current->state>>section)&0x1) ==1         
			it.Current->state=it.Current->state&(0xFFFFFFFF-(int)(pow(2.0,(double)section)));
			if(it.Current->state!=0)
				return true;//Dismark it successfully
			else{ //state is 0,delete this node
				it.Remove(address);
				return true;
			    }
		    }
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
bool MemoryRecorder::markTaintedBlock(unsigned int address, int length)
{   
	if(length==1){
		markTaintedMemory(address);
	}
	if(address<minAddress||address>maxAddress)
		return false; //wrong memory address
	int startLocation=(address-minAddress)/sizeOfPage;
	int endLocation=(address+length-1-minAddress)/sizeOfPage;
	int listNumberBetween=endLocation-startLocation-1;
	/*** Case 1:The start address and the end address are not in the same list.***/
	if(startLocation!=endLocation){
		int startNodeAddress=address-address%32;
		int x=address%32;
		int value=0;
		for(int i=x;i<32;i++){
		    value=value+(int)(pow(2.0,(double)i));
		}
		int y=(address+length-1)%32;
		int _value=0;
	    for(int i=0;i<=y;i++){
		    _value=_value+(int)(pow(2.0,(double)i));
		}
	unsigned int endNodeAddress=(address+length-1)-y;
	unsigned int endAddress=address+length-1;
		/*Operations in the list which the start address located in
		*/
	List list=memoryList[startLocation];
	ListItr it(list);
	if(list.IsEmpty()){
		it.Insert(value,startNodeAddress);
	}
	int flag=it.RemoveBiggerThan(address);
	while(flag!=0){
		flag=it.RemoveBiggerThan(address);
	}
	int a=it.Find(address);
	if(a==0){
		it.Insert(value,startNodeAddress);
	}
	else{
		it.Current->state=(it.Current->state)|value;
		}
	int nodeNumberLeft=((startLocation+1)*sizeOfPage-( startNodeAddress+32))/32;
	if(nodeNumberLeft!=0){
		for(int i=1;i<=nodeNumberLeft;i++){
			int address_=startNodeAddress+32*i;
			int state_=0xFFFFFFFF;
			it.Insert(state_,address_);
		}
	}
		/*Operations in the lists that between the start list and the end list.
		*/
	for(int i=0;i<listNumberBetween;i++){
		memoryList[startLocation+i+1].MakeEmpty();
		int _state=0xFFFFFFFF;
		List list2=memoryList[startLocation+i+1];
		ListItr it2(list2);
		for(int j=0;j<(sizeOfPage/32);j++){
			int address_=(startLocation+i+1)*sizeOfPage+32*j;
			int state_=0xFFFFFFFF;
			it2.Insert(state_,address_);
		}
	}
		/*Operations in the list which the end address located in
		*/
	List list3=memoryList[endLocation];
	ListItr it3(list3);
	if(list3.IsEmpty()){
		it3.Insert(_value,endNodeAddress);
	}
	int flag2=it3.RemoveSmallerThan(endAddress);
	while(flag2!=0){
		flag2=it3.RemoveSmallerThan(endAddress);
	}
	int b=it3.Find(endAddress);
	if(b==0){
		it3.Insert(_value,endNodeAddress);
	}
	else{
		it3.Current->state=(it3.Current->state)|_value;
		}
	int nodeNumberLeft2=(endAddress-endLocation*sizeOfPage)/32;
		if(nodeNumberLeft2!=0){
			for(int i=1;i<=nodeNumberLeft2;i++){
			int address_=endAddress-32*i;
			int state_=0xFFFFFFFF;
			it3.Insert(state_,address_);
			}	
		}
		return true;
	}
	/*** Case 2:The start address and the end address are in the same list.***/
	/*If the start address and the end address are in the same node.
	 */
	if(address/32==(address+length-1)/32){
		int startNodeAddress=address-address%32;
		int x=address%32;
		int y=(address+length-1)%32;
		int value=0;
		for(int i=x;i<=y;i++){
			value=value+(int)(pow(2.0,(double)i));
		}
    List list=memoryList[startLocation];
	ListItr it(list);
	if(list.IsEmpty()){
		it.Insert(value,startNodeAddress);
	}
	int a=it.Find(address);
	if(a==0){
		it.Insert(value,startNodeAddress);
	}
	else{
		it.Current->state=(it.Current->state)|value;
		}
		return true;
	}
	/*If the start address and the end address are not in the same node(but in the same list).
	 */
	else{	
		int startNodeAddress=address-address%32;
		int x=address%32;
		int value=0;
		for(int i=x;i<32;i++){
			value=value+(int)(pow(2.0,(double)i));
		}
		int y=(address+length-1)%32;
		int _value=0;
		for(int i=0;i<=y;i++){
			_value=_value+(int)(pow(2.0,(double)i));
		}
		unsigned int endNodeAddress=(address+length-1)-y;
		unsigned int endAddress=address+length-1;

		List list=memoryList[startLocation];
		ListItr it(list);
		if(list.IsEmpty()){
			it.Insert(value,startNodeAddress);
		}
		int flag=it.RemoveBetween(address,endAddress);
		while(flag!=0){
			flag=it.RemoveBetween(address,endAddress);
		}
		int a=it.Find(address);
		if(a==0){
			it.Insert(value,startNodeAddress);
		}
		else{
			it.Current->state=(it.Current->state)|value;
			}
		int b=it.Find(endAddress);
		if(b==0){
			it.Insert(_value,endNodeAddress);
		}
		else{
			it.Current->state=(it.Current->state)|_value;
			}
		int nodeNumberBetween=(endNodeAddress-( startNodeAddress+32))/32;
			if(nodeNumberBetween!=0){
				for(int i=1;i<=nodeNumberBetween;i++){
					int address_=startNodeAddress+32*i;
					int state_=0xFFFFFFFF;
					it.Insert(state_,address_);
				}
			}
		return true;
	}
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
bool MemoryRecorder::dismarkTaintedBlock(unsigned int address, int length)
{   
	if(length==1){
		dismarkTaintedMemory(address);
	}
	if(address<minAddress||address>maxAddress)
		return false; //wrong memory address
	int startLocation=(address-minAddress)/sizeOfPage;
	int endLocation=(address+length-1-minAddress)/sizeOfPage;
	int listNumberBetween=endLocation-startLocation-1;
	/*** Case 1:The start address and the end address are not in the same list.***/
	if(startLocation!=endLocation){
		int startNodeAddress=address-address%32;
		int x=address%32;
		int value=0;
		for(int i=x;i<32;i++){
		    value=value+(int)(pow(2.0,(double)i));
		}
		value=value^0xFFFFFFFF;
		int y=(address+length-1)%32;
		int _value=0;
	    for(int i=0;i<=y;i++){
		    _value=_value+(int)(pow(2.0,(double)i));
		}
		_value=_value^0xFFFFFFFF;
	unsigned int endNodeAddress=(address+length-1)-y;
	unsigned int endAddress=address+length-1;	
		/*Operations in the list which the start address located in
		*/
	List list=memoryList[startLocation];
	ListItr it(list);
	if(list.IsEmpty()){
		;
	}
	int flag=it.RemoveBiggerThan(address);
	while(flag!=0){
		flag=it.RemoveBiggerThan(address);
	}
	int a=it.Find(address);
	if(a==0){
		;
	}
	else{
		it.Current->state=(it.Current->state)&value;
		}
		/*Operations in the lists that between the start list and the end list.
		*/
	for(int i=0;i<listNumberBetween;i++){
		memoryList[startLocation+i+1].MakeEmpty();
	}	
		/*Operations in the list which the end address located in
		*/
	List list2=memoryList[endLocation];
	ListItr it2(list2);
	if(list2.IsEmpty()){
		;
	}
	int flag2=it2.RemoveSmallerThan(endAddress);
	while(flag2!=0){
		flag2=it2.RemoveSmallerThan(endAddress);
	}
	int b=it2.Find(endAddress);
	if(b==0){
		;
	}
	else{
		it2.Current->state=(it2.Current->state)&_value;
		}
		return true;
	}
	/*** Case 2:The start address and the end address are in the same list.***/
	/*If the start address and the end address are in the same node.
	 */
	if(address/32==(address+length-1)/32){
		int startNodeAddress=address-address%32;
	    int x=address%32;
		int y=(address+length-1)%32;
	    int value=0;
		for(int i=x;i<=y;i++){
			value=value+(int)(pow(2.0,(double)i));
		}
		value=value^0xFFFFFFFF;
	List list=memoryList[startLocation];
	ListItr it(list);
	if(list.IsEmpty()){
		;
	}
	int a=it.Find(address);
	if(a==0){
		;
	}
	else{
		it.Current->state=(it.Current->state)&value;
		}
		return true;
	}	 
	/*If the start address and the end address are not in the same node(but in the same list).
	 */
	else{
		int startNodeAddress=address-address%32;
		int x=address%32;
		int value=0;
		for(int i=x;i<32;i++){
			value=value+(int)(pow(2.0,(double)i));
		}
		value=value^0xFFFFFFFF;
		int y=(address+length-1)%32;
		int _value=0;
		for(int i=0;i<=y;i++){
			_value=_value+(int)(pow(2.0,(double)i));
		}
		_value=_value^0xFFFFFFFF;
		unsigned int endNodeAddress=(address+length-1)-y;
		unsigned int endAddress=address+length-1;

		List list=memoryList[startLocation];
		ListItr it(list);
		if(list.IsEmpty()){
			;
		}
		int flag=it.RemoveBetween(address,endAddress);
		while(flag!=0){
			flag=it.RemoveBetween(address,endAddress);
		}
		int a=it.Find(address);
		if(a==0){
			;
		}
		else{
			it.Current->state=(it.Current->state)&value;
			}
		int b=it.Find(endAddress);
		if(b==0){
			;
		}
		else{
			it.Current->state=(it.Current->state)&_value;
			}
		return true;
	}
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
bool MemoryRecorder::dismarkTaintedBlock(unsigned int address, int length,int state)
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
void MemoryRecorder::clearState()
{
	int length=amountOfPage;
	for(int i=0;i<length;i++){
	  memoryList[i].MakeEmpty();
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
void MemoryRecorder::printState(FILE *output)
{
	for(int i=0;i<amountOfPage;i++){
		List list = this->memoryList[i];
		ListItr it(list);
		while(!list.IsEmpty()){
			fprintf(output,"taint at 0x%x to 0x%x\n",it.Current->address,it.Current->address+31);
			for(int j=0;j<32;j++){
				unsigned int tmp = 1;
				if((it.Current->state&(tmp<<j))!=0){
					fprintf(output,"0x%x ",it.Current->address+j);
				}
			}
			fprintf(output,"\n");
			it.Current = it.Current->Next;
			if(it.Current==NULL)
				break;
		}
	}
}