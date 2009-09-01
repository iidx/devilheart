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
	memoryList = (MemNode**)malloc(sizeof(MemNode*)*amountOfPage);//待解决
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
	memoryList = (MemNode**)malloc(sizeof(MemNode*)*amountOfPage);//待解决
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
	memoryList = (MemNode**)malloc(sizeof(MemNode*)*amountOfPage);//待解决
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

	//MemNode* node = memoryList[location];
	//if (node==NULL){
	//	return 0; //The node does not exist
	//}
	//while( ((address>(node->address+31)) || (address<(node->address)))&&
	//	node!=NULL)
	//	node=node->nextNode;
	//if (node==NULL)
	//	return 0; //The node containing this address does not exist
	//int section=address-(node->address);
	//if( ((node->state>>section)&0x1) ==1)
	//	return 1; //1 is taited
	//else  //((node->state>>section)&0x1) ==0
	//	return 0; //0 is not taited

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

	//MemNode* node = memoryList[location];
	////The list is empty
 //   if (node==NULL){
	//	int startNodeAddress=address-address%32;
	//	int _state=0|(int)(pow(2.0,(double)(address%32)));
	//	/*MemNode n;    
	//	
	//	n.address=startNodeAddress;
	//	n.state=_state;	 
	//	n.nextNode = NULL;                                                   
	//	memoryList[location]=&n;
	//	return true;*/
	//	memoryList[location]=(MemNode*)malloc(sizeof(MemNode));
	//	memoryList[location]->address=startNodeAddress;
	//	memoryList[location]->state=_state;	 
	//	memoryList[location]->nextNode = NULL;  
	//	return true;
	//}
	//MemNode* a=node; //Pre node of the current node
	////Find the memory node in the address	
	//while( (node!=NULL) && ((address>(node->address+31)) || (address<(node->address)))  ){ 	
	//	a = node;
	//	node=node->nextNode;
	//	//node=a;
	//} 
	////The memory node in the address is not existed
	//if( node==NULL ){      
	//	 int startNodeAddress=address-address%32;
	//	 int _state=0|(int)(pow(2.0,(double)(address%32)));
	//	 /* MemNode n; 
	//	 n.address=startNodeAddress;
	//	 n.state=_state;
	//	 n.nextNode = NULL;
	//	 a->nextNode=&n;*/
	//	 a->nextNode=(MemNode*)malloc(sizeof(MemNode));
	//	 a->nextNode->address=startNodeAddress;
	//	 a->nextNode->nextNode=NULL;
	//	 a->nextNode->state=_state;
	//	 return true;
	//}
	//else{	
	//	int section=address-(node->address);
	//	if( ((node->state>>section)&0x1) ==1)
	//		return false;//The memory in the address is already tainted.
	//	else{ // ((node->state>>section)&0x1) ==0	
	//		node->state=node->state|(int)(pow(2.0,(double)section));
	//		return true;//Mark it tainted successfully
	//	}
	//}
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
		if( ((it.Current->state>>section)&0x1) ==1)
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
	
	//MemNode* node = memoryList[location];
	//if (node==NULL){
	//	return true; //The node does not exist
	//}
	//MemNode* a=node; //Pre node of the current node
	////Find the memory node in the address

	//while( (node!=NULL) && ((address>(node->address+31)) || (address<(node->address)))  ){ 
 //       a = node;
	//	node = node->nextNode;
	//}
	////The memory node in the address is not existed
	//if( node==NULL ){       
	//	return true;
	//}
	//else{	
	//	int section=address-(node->address);	
	//	if( ((node->state>>section)&0x1) ==0)
	//		return true;//The memory in the address is not tainted.	
	//	else{ // ((node->state>>section)&0x1) ==1         
	//		node->state=node->state&(0xFFFFFFFF-(int)(pow(2.0,(double)section)));
	//		if(node->state!=0)
	//			return true;//Dismark it successfully
	//		else{ //state is 0,delete this node
	//			a->nextNode=node->nextNode;
	//			delete node;
	//			return true;
	//		}
	//	}
	//}
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
	
	/***第一种情况（起始地址和末地址不在同一条链表上）***/
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
		/*对起始地址所在链表进行的操作
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
	    //MemNode* node = memoryList[startLocation];
		////The list is empty
		//if (node==NULL){
		//	int _state=0|value;
		//	/*MemNode n;  
		//	n.address=startNodeAddress;
		//	n.state=_state;	 
		//	n.nextNode = NULL; */                                                  
		//	memoryList[startLocation]= (MemNode*)malloc(sizeof(MemNode));
		//	memoryList[startLocation]->address=startNodeAddress;
		//	memoryList[startLocation]->state=_state;
		//	memoryList[startLocation]->nextNode=NULL;
		//}

		//MemNode* a=node; //Pre node of the current node
		////Find the memory node in the address	
		//while( (node!=NULL) && ((address>(node->address+31)) || (address<(node->address)))  ){ 	
		//	a = node;
		//	if((node->address)>address){
		//		MemNode *temp=node;
		//		MemNode *it=node->nextNode;
		//		node=node->nextNode;
		//		a->nextNode=it; 
		//		delete temp;
		//		continue;
		//	}
		//	node=node->nextNode;
		//	//node=a;
		//} 
		////The memory node in the address is not existed
		//if( node==NULL ){      
		//	 MemNode n;    
		//	 int _state=0|value;
		//	 n.address=startNodeAddress;
		//	 n.state=_state;
		//	 n.nextNode = NULL;
		//	 a->nextNode= (MemNode*)malloc(sizeof(MemNode));
		//	 a->nextNode->address=startNodeAddress;
		//	 a->nextNode->state=_state;
		//	 a->nextNode->nextNode=NULL;
		//}
		//else{	
		//	 node->state=(node->state)|value;
		//}
		int nodeNumberLeft=((startLocation+1)*sizeOfPage-( startNodeAddress+32))/32;
		if(nodeNumberLeft!=0){
			for(int i=1;i<=nodeNumberLeft;i++){
				int address_=startNodeAddress+32*i;
				int state_=0xFFFFFFFF;
				it.Insert(state_,address_);
				
		//		MemNode m;
		//		int address_=startNodeAddress+32*i;
		//		int state_=0xFFFFFFFF;
		//		m.address=address_;
		//		m.state=state_;
		//		m.nextNode=NULL;
		//		//node->nextNode=&m;
		//		node->nextNode= (MemNode*)malloc(sizeof(MemNode));
		//		node->nextNode->address=startNodeAddress+32*i;
		//		node->nextNode->state=state_;
		//		node->nextNode->nextNode=NULL;
		//		node=node->nextNode;
			}
		}
		/*对起始地址所在链表和末地址所在链表之间的链表的操作
		*/
		for(int i=0;i<listNumberBetween;i++){
			memoryList[startLocation+i+1]=NULL;//待解决
			int _state=0xFFFFFFFF;
			List list2=memoryList[startLocation+i+1];
			ListItr it2(list2);
			for(int j=0;j<(sizeOfPage/32);j++){
				int address_=(startLocation+i+1)*sizeOfPage+32*j;
				int state_=0xFFFFFFFF;
				it2.Insert(state_,address_);
			}
			
			
		//	memoryList[startLocation+i+1]=(MemNode*)malloc(sizeof(MemNode));
		//	memoryList[startLocation+i+1]->address=(startLocation+i+1)*sizeOfPage;
		//	memoryList[startLocation+i+1]->nextNode = NULL;
		//	memoryList[startLocation+i+1]->state = _state;
		//	MemNode* node2 = memoryList[startLocation+i+1];
		//	for(int j=0;j<(sizeOfPage/32);j++){
		//		int address_=(startLocation+i+1)*sizeOfPage+32*j;
		//		int state_=0xFFFFFFFF;
		//		/*MemNode m;
		//		m.address=address_;
		//		m.state=state_;
		//		m.nextNode=NULL;*/
		//		node2->nextNode=(MemNode*)malloc(sizeof(MemNode));
		//		node2->nextNode->address = address;
		//		node2->nextNode->nextNode = NULL;
		//		node2->nextNode->state = state_;
		//		node2=node2->nextNode;
		//	}
		}
		/*对末地址所在链表进行的操作
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
	
		
		
		
		//MemNode* node3 = memoryList[endLocation];

		////The list is empty
		//if (node3==NULL){
		//	MemNode n;    
		//	int _state=0|_value;
		//	n.address=endNodeAddress;
		//	n.state=_state;	 
		//	n.nextNode = NULL;                                                   
		//	memoryList[endLocation]=(MemNode*)malloc(sizeof(MemNode));
		//	memoryList[endLocation]->address = endNodeAddress;
		//	memoryList[endLocation]->nextNode = NULL;
		//	memoryList[endLocation]->state = _state;
		//}
		//MemNode* b=node3; //Pre node of the current node
		////Find the memory node in the address	
		//while( (node3!=NULL) && ((endAddress>(node3->address+31)) || (endAddress<(node3->address)))  ){ 	
		//	b = node3;
		//	if((node3->address+31)<endAddress){
		//		MemNode *temp=node3;
		//		MemNode *it=node3->nextNode;
		//		node3=node3->nextNode;
		//		b->nextNode=it; 
		//		delete temp;
		//		continue;
		//	}
		//	node3=node3->nextNode;
		//	//node3=a;
		//} 
		////The memory node in the address is not existed
		//if( node3==NULL ){      
		//	 /*MemNode n;   */ 
		//	 int _state=0|_value;
		//	 /*n.address=endAddress;
		//	 n.state=_state;
		//	 n.nextNode = NULL;*/
		//	 b->nextNode=(MemNode*)malloc(sizeof(MemNode));
		//	 b->nextNode->address = endAddress;
		//	 b->nextNode->nextNode = NULL;
		//	 b->nextNode->state = _state;
		//	 
		//}
		//else{	
		//	 node3->state=(node3->state)|_value;
		//}
	     
		int nodeNumberLeft2=(endAddress-endLocation*sizeOfPage)/32;
			 if(nodeNumberLeft2!=0){
			    
				for(int i=1;i<=nodeNumberLeft2;i++){
				int address_=endAddress-32*i;
				int state_=0xFFFFFFFF;
				it3.Insert(state_,address_);
				/*node3->nextNode=(MemNode*)malloc(sizeof(MemNode));
				node3->nextNode->address=address;
				node3->nextNode->nextNode=NULL;
				node3->nextNode->state=state_;
				node3=node3->nextNode;*/
				}	
		}
		return true;
	}
	/***第二种情况（起始地址和末地址在同一条链表上）***/
	
	/*如果起始地址和末地址在一个结点上进行的操作
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
		
	 //   MemNode* node = memoryList[startLocation];
		////The list is empty
		//if (node==NULL){
		//	//MemNode n;    
		//	int _state=0|value;
		//	/*n.address=startNodeAddress;
		//	n.state=_state;	 
		//	n.nextNode = NULL; */                                                  
		//	memoryList[startLocation]=(MemNode*)malloc(sizeof(MemNode));
		//	memoryList[startLocation]->address=startNodeAddress;
		//	memoryList[startLocation]->nextNode=NULL;
		//	memoryList[startLocation]->state=_state;
		//}

		//MemNode* a=node; //Pre node of the current node
		////Find the memory node in the address	
		//while( (node!=NULL) && ((address>(node->address+31)) || (address<(node->address)))  ){ 	
		//	a = node;
		//	node=node->nextNode;
		//	//node=a;
		//} 
		////The memory node in the address is not existed
		//if( node==NULL ){      
		//	/*MemNode n;  */  
		//	int _state=0|value;
		//	/*n.address=startNodeAddress;
		//	n.state=_state;
		//	n.nextNode = NULL;*/
		//	a->nextNode=(MemNode*)malloc(sizeof(MemNode));
		//	a->nextNode->address=startNodeAddress;
		//	a->nextNode->nextNode=NULL;
		//	a->nextNode->state=_state;
		//}
		//else{	
		//	node->state=(node->state)|value;
		//}
		return true;
	}
	
	/*如果起始地址和末地址不在同一个结点上(但在同一条链表上)进行的操作
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

		//MemNode* node = memoryList[startLocation];
		////The list is empty
		//if (node==NULL){
		//	//MemNode n;    
		//	int _state=0|value;
		//	/*n.address=startNodeAddress;
		//	n.state=_state;	 
		//	n.nextNode = NULL;*/                                                   
		//	memoryList[startLocation]=(MemNode*)malloc(sizeof(MemNode));
		//	memoryList[startLocation]->address=startNodeAddress;
		//	memoryList[startLocation]->nextNode=NULL;
		//	memoryList[startLocation]->state=_state;
		//}
		//MemNode* a=node; //Pre node of the current node
		////Find the memory node in the address	
		//while( (node!=NULL) && ((address>(node->address+31)) || (address<(node->address)))  ){ 	
		//	a = node;
		//	if( ((node->address)>address)&& ((node->address)<endNodeAddress) ){
		//		MemNode *temp=node;
		//		MemNode *it=node->nextNode;
		//		node=node->nextNode;
		//		a->nextNode=it; 
		//		delete temp;
		//		continue;
		//	}
		//	node=node->nextNode;
		//	//node=a;
		//	} 
		//	//The memory node in the address is not existed
		//	if( node==NULL ){      
		//		/*MemNode n;  */  
		//		int _state=0|value;
		//		/*n.address=startNodeAddress;
		//		n.state=_state;
		//		n.nextNode = NULL;*/
		//		a->nextNode=(MemNode*)malloc(sizeof(MemNode));
		//		a->nextNode->address=startNodeAddress;
		//		a->nextNode->nextNode=NULL;
		//		a->nextNode->state=_state;
		//	}
		//	else{	
		//		node->state=(node->state)|value;
		//	}

			int nodeNumberBetween=(endNodeAddress-( startNodeAddress+32))/32;
				if(nodeNumberBetween!=0){
					for(int i=1;i<=nodeNumberBetween;i++){
						int address_=startNodeAddress+32*i;
						int state_=0xFFFFFFFF;
						it.Insert(state_,address_);
						/*node->nextNode=(MemNode*)malloc(sizeof(MemNode));
						node->nextNode->address=startNodeAddress+32*i;
						node->nextNode->nextNode=NULL;
						node->nextNode->state=state_;
						node=node->nextNode;*/
					}
			}

			//MemNode* node2=memoryList[startLocation];

			//MemNode* b=node2; //Pre node of the current node
			////Find the memory node in the address 
			//while( (node2!=NULL) && ((endAddress>(node2->address+31)) || (endAddress<(node2->address)))  ){ 	
			//	b=node2;
			//	node2=node2->nextNode;
			////node2=b;
			//} 
			////The memory node in the address is not existed
			//if( node2==NULL ){      
			//	/*MemNode n;  */  
			//	int _state=0|_value;
			//	/*n.address=endNodeAddress;
			//	n.state=_state;
			//	n.nextNode = NULL;*/
			//	b->nextNode=(MemNode*)malloc(sizeof(MemNode));
			//	b->nextNode->address=endNodeAddress;
			//	b->nextNode->nextNode=NULL;
			//	b->nextNode->state=_state;
			//}
			//else{	
			//	node2->state=(node2->state)|_value;
			//}
		

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
	
	/***第一种情况（起始地址和末地址不在同一条链表上）***/

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
		/*对起始地址所在链表进行的操作
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
		
		//MemNode* node = memoryList[startLocation];
		////The list is empty
		//if (node==NULL){
		//	;
		//}
		//MemNode* a=node; //Pre node of the current node
		////Find the memory node in the address	
		//while( (node!=NULL) && ((address>(node->address+31)) || (address<(node->address)))  ){ 	
		//	a = node;
		//	if((node->address)>address){
		//		MemNode *temp=node;
		//		MemNode *it=node->nextNode;
		//		node=node->nextNode;
		//		a->nextNode=it; 
		//		delete temp;
		//		continue;
		//	}
		//	node=node->nextNode;
		//	//node=a;
		//} 
		////The memory node in the address is not existed
		//if( node==NULL ){      
		//	 ;
		//	 
		//}
		//else{	
		//	node->state=(node->state)|value;
		//}
		/*对起始地址所在链表和末地址所在链表之间的链表的操作
		 */
		for(int i=0;i<listNumberBetween;i++){
			memoryList[startLocation+i+1]=NULL;//待解决

		}	
		/*对末地址所在链表进行的操作
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
		
		//MemNode* node2 = memoryList[endLocation];

		////The list is empty
		//if (node2==NULL){
		//	   ;
		//}
		//MemNode* b=node2; //Pre node of the current node
		////Find the memory node in the address	
		//while( (node2!=NULL) && ((endAddress>(node2->address+31)) || (endAddress<(node2->address)))  ){ 	
		//	b = node2;
		//	if((node2->address+31)<endAddress){
		//		MemNode *temp=node2;
		//		MemNode *it=node2->nextNode;
		//		node2=node2->nextNode;
		//		b->nextNode=it; 
		//		delete temp;
		//		continue;
		//	}
		//	node2=node2->nextNode;
		//	//node2=a;
		//} 
		////The memory node in the address is not existed
		//if( node2==NULL ){      
		//	 ;
		//	 
		//}
		//else{	
		//	 node2->state=(node2->state)|_value;
		//}
		return true;
	}

	
	/***第二种情况（起始地址和末地址在同一条链表上）***/
     
    
		/*如果起始地址和末地址在一个结点上进行的操作
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
			//MemNode* node = memoryList[startLocation];
			////The list is empty
			//if (node==NULL){
			//   ;
			//}
			//MemNode* a=node; //Pre node of the current node
			////Find the memory node in the address	
			//while( (node!=NULL) && ((address>(node->address+31)) || (address<(node->address)))  ){ 	
			//	a = node;
			//	node=node->nextNode;
			//	//node=a;
			//} 
			////The memory node in the address is not existed
			//if( node==NULL ){      
			//	 ;
			//}
			//else{	
			//	 node->state=(node->state)|value;
			//}
		return true;
	}	 
	/*如果起始地址和末地址不在同一个结点上(但在同一条链表上)进行的操作
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

		//MemNode* node = memoryList[startLocation];
		//	//The list is empty
		//	if (node==NULL){
		//	   ;
		//	}

		//	MemNode* a=node; //Pre node of the current node
		//	//Find the memory node in the address	
		//	while( (node!=NULL) && ((address>(node->address+31)) || (address<(node->address)))  ){ 	
		//		a = node;
		//		if( ((node->address)>address)&& ((node->address)<endNodeAddress) ){
		//			MemNode *temp=node;
		//			MemNode *it=node->nextNode;
		//			node=node->nextNode;
		//			a->nextNode=it; 
		//			delete temp;
		//			continue;
		//		}
		//		node=node->nextNode;
		//		//node=a;
		//	} 
		//	//The memory node in the address is not existed
		//	if( node==NULL ){      
		//		 ;

		//	}
		//	else{	
		//		 node->state=(node->state)|value;
		//	}
	 //    
		//	MemNode* node2=memoryList[startLocation];

		//	MemNode* b=node2; //Pre node of the current node
		//	//Find the memory node in the address 
		//	while( (node2!=NULL) && ((endAddress>(node2->address+31)) | (endAddress<(node2->address)))  ){ 	
		//		b=node2;
		//	
		//		node2=node2->nextNode;
		//		//node2=b;
		//	} 
		//	//The memory node in the address is not existed
		//	if( node2==NULL ){      
		//		 ;
		//	}
		//	else{	
		//		 node2->state=(node2->state)|_value;
		//	}

		
    
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
	  memoryList[i]=NULL;//待解决
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
		MemNode *node = this->memoryList[i];
		while(node!=NULL){
			fprintf(output,"taint at 0x%x to 0x%x\n",node->address,node->address+31);
			for(int j=0;j<32;j++){
				unsigned int tmp = 1;
				if((node->state&(tmp<j))==1){
					fprintf(output,"0x%x ",node->address+j);
				}
			}
			fprintf(output,"\n");
		}
	}
}