#include "mem_recorder.h"

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

void ListItr::Insert(unsigned int state, unsigned int address){
	//Exception(Current==NULL,"The location is illegal!");
	Node *p;
	p=new Node(state,address,Current->Next);
	Current=Current->Next=p;
}

int ListItr::Remove(unsigned int address){
	Node *Ptr=head;
	while( (Ptr->Next!=NULL) && ((address>(Ptr->Next->address+31)) || (address<(Ptr->Next->address))) )
		Ptr=Ptr->Next;
	if(Ptr->Next==NULL) return 0;//Î´ÕÒµ½£¬É¾³ıÊ§°Ü¡£
	Node * P=Ptr->Next;
	Ptr->Next=Ptr->Next->Next;
	delete P;
	Current=head;
	return 1;

}

int ListItr::RemoveBiggerThan(unsigned int address){
	Node *Ptr=head;
	while( (Ptr->Next!=NULL) && !(address<(Ptr->Next->address)) )
		Ptr=Ptr->Next;
	if(Ptr->Next==NULL) return 0;//Î´ÕÒµ½£¬É¾³ıÊ§°Ü¡£
	Node * P=Ptr->Next;
	Ptr->Next=Ptr->Next->Next;
	delete P;
	Current=head;
	return 1;

}

int ListItr::RemoveSmallerThan(unsigned int address){
	Node *Ptr=head;
	while( (Ptr->Next!=NULL) && !(address>(Ptr->Next->address+31))  )
		Ptr=Ptr->Next;
	if(Ptr->Next==NULL) return 0;//Î´ÕÒµ½£¬É¾³ıÊ§°Ü¡£
	Node * P=Ptr->Next;
	Ptr->Next=Ptr->Next->Next;
	delete P;
	Current=head;
	return 1;

}

int ListItr::RemoveBetween(unsigned int address,unsigned int address2){
	Node *Ptr=head;
	while( (Ptr->Next!=NULL) && ((address>(Ptr->Next->address)) || (address2<(Ptr->Next->address+31))) )
		Ptr=Ptr->Next;
	if(Ptr->Next==NULL) return 0;//Î´ÕÒµ½£¬É¾³ıÊ§°Ü¡£
	Node * P=Ptr->Next;
	Ptr->Next=Ptr->Next->Next;
	delete P;
	Current=head;
	return 1;

}