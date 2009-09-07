/*******************************************************************

 Title:ListItr.cpp
 Function:To implement functions of class ListItr
 Description:
 Source file to implement functions of class ListItr
 Version: 1.2
 Date and author: 2009.08.16 hsqfire, Jiang Bo
*******************************************************************/
#include "mem_recorder.h"

/******************************************************************
 Title:Find
 Function:Find the node in the list
 Input:
 unsigned int address
 Output:
 int
 Return value:1 is successful, 0 means not found
******************************************************************/
int ListItr::Find(unsigned int address){
	Node *Ptr=head->Next;
	while( Ptr!=NULL   ){
		if((address>(Ptr->address+31)) || (address<(Ptr->address)))
			Ptr=Ptr->Next;
		else break;
	}
	if(Ptr==NULL) return 0;
	Current=Ptr;
	return 1;
}

/******************************************************************
 Title:Insert
 Function:Insert a node in a list
 Input:
 unsigned int state:The state of the node.
 unsigned int address:The location to insert the node.
 Output:
 ******************************************************************/
void ListItr::Insert(unsigned int state, unsigned int address){
	//Exception(Current==NULL,"The location is illegal!");
	Node *p;
	p=new Node(state,address,Current->Next);
	Current=Current->Next=p;
}

/******************************************************************
 Title:Remove
 Function:Remove the node in the address
 Input:
 unsigned int address:The address in the node
 Output:
 int
 Return value:1 is successful, 0 means not found
******************************************************************/
int ListItr::Remove(unsigned int address){
	Node *Ptr=head;
	while( (Ptr->Next!=NULL) && ((address>(Ptr->Next->address+31)) || (address<(Ptr->Next->address))) )
		Ptr=Ptr->Next;
	if(Ptr->Next==NULL) return 0;//not found,delete failed.
	Node * P=Ptr->Next;
	Ptr->Next=Ptr->Next->Next;
	delete P;
	Current=head;
	return 1;

}

/******************************************************************
 Title:RemoveBiggerThan
 Function:Remove the nodes whose addresses are bigger than the given address
 Input:
 unsigned int address
 Output:
 int
 Return value:1 is successful, 0 means not found
******************************************************************/
int ListItr::RemoveBiggerThan(unsigned int address){
	Node *Ptr=head;
	while( (Ptr->Next!=NULL) && !(address<(Ptr->Next->address)) )
		Ptr=Ptr->Next;
	if(Ptr->Next==NULL) return 0;//not found,delete failed.
	Node * P=Ptr->Next;
	Ptr->Next=Ptr->Next->Next;
	delete P;
	Current=head;
	return 1;

}

/******************************************************************
 Title:RemoveSmallerThan
 Function:Remove the nodes whose addresses are smaller than the given address
 Input:
 unsigned int address
 Output:
 int
 Return value:1 is successful, 0 means not found
******************************************************************/
int ListItr::RemoveSmallerThan(unsigned int address){
	Node *Ptr=head;
	while( (Ptr->Next!=NULL) && !(address>(Ptr->Next->address+31))  )
		Ptr=Ptr->Next;
	if(Ptr->Next==NULL) return 0;//not found,delete failed.
	Node * P=Ptr->Next;
	Ptr->Next=Ptr->Next->Next;
	delete P;
	Current=head;
	return 1;

}

/******************************************************************
 Title:RemoveBetween
 Function:Remove the nodes whose addresses are between the given addresses
 Input:
 unsigned int address
 Output:
 int
 Return value:1 is successful, 0 means not found
******************************************************************/
int ListItr::RemoveBetween(unsigned int address,unsigned int address2){
	Node *Ptr=head;
	while( (Ptr->Next!=NULL) && ((address>(Ptr->Next->address)) || (address2<(Ptr->Next->address+31))) )
		Ptr=Ptr->Next;
	if(Ptr->Next==NULL) return 0;//not found,delete failed.
	Node * P=Ptr->Next;
	Ptr->Next=Ptr->Next->Next;
	delete P;
	Current=head;
	return 1;

}