/*******************************************************************

 Title:list.cpp
 Function:To implement functions of class List
 Description:
 Source file to implement functions of class List
 Version: 1.2
 Date and author: 2009.08.16 hsqfire, Jiang Bo
*******************************************************************/
#include "mem_recorder.h"

/******************************************************************
 Title:MakeEmpty
 Function:Mark the list an empty list
 Input:
 Output:
 ******************************************************************/
void List::MakeEmpty(){
	Node * Ptr;
	Node * NextNode;
	for(Ptr=head->Next;Ptr!=NULL;Ptr=NextNode){
		NextNode=Ptr->Next;
		delete Ptr;
	}
	head->Next=NULL;
}