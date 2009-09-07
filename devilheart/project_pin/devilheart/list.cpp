#include "mem_recorder.h"

void List::MakeEmpty(){
	Node * Ptr;
	Node * NextNode;
	for(Ptr=head->Next;Ptr!=NULL;Ptr=NextNode){
		NextNode=Ptr->Next;
		delete Ptr;
	}
	head->Next=NULL;
}