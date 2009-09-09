/*******************************************************************

 Title:hooks.cpp
 Function:Implement some hook function to handle some instructions
 Description:
 Implement some hook function to handle some instructions
 Version: 1.0
 Date and author: 2009.07.30 hsqfire
*******************************************************************/


#include "hooks.h"


/******************************************************************
 Title:movRMHook
 Function:Hook to handle instruction "mov REG [mem addr]"
 Input:
 REG dstReg:dst register
 ADDRINT *addr:src memory address
 Output:
 VOID
******************************************************************/
VOID movRMHook(REG dstReg,ADDRINT * addr)
{
	unsigned int realAddress = (int)addr;
	int state = memManager->isTainted(realAddress);
	//int state = 0;
	//fprintf(log,"Read address:0x%x\n",realAddress);
	if(state==1){
		if(REG_valid(dstReg)){
			regState[dstReg] = 1;
		}
	}else{
		if(REG_valid(dstReg)){
			regState[dstReg] = 0;
		}
	}
}


/******************************************************************
 Title:movMRHook
 Function:Hook to handle instruction "mov [mem addr],REG"
 Input:
 REG srcReg:src register
 ADDRINT *addr:dst memory address
 Output:
 VOID
******************************************************************/
VOID movMRHook(REG srcReg,ADDRINT * addr)
{
	unsigned int realAddress = (int)addr;
	//fprintf(log,"write Add:0x%x\n",realAddress);
	if(!REG_valid(srcReg)){
		return ;
	}
	int state = regState[srcReg];
	//int state = 1;
	if(state==1){
		memManager->markTaintedMemory(realAddress);
	}else{
		memManager->dismarkTaintedMemory(realAddress);
	}
}


/******************************************************************
 Title:repMovsbHook
 Function:Hook to handle instruction "rep movsb"
 Input:
 int ecx:value of ECX register
 ADDRINT *srcAddr:src memory address
 ADDRINT *dstAddr:dst memory address
 Output:
 VOID
******************************************************************/
VOID repMovsbHook(int ecx,ADDRINT *srcAddr,ADDRINT *dstAddr)
{
	unsigned int realSrcAddress = (int)srcAddr;
	unsigned int realDstAddress = (int)dstAddr;
	
	for(int i=0;i<ecx;i++)
	{
		//fprintf(output,"mov data from memory at 0x%x to 0x%x\n",realSrcAddress+i,realDstAddress+i);
		if(memManager->isTainted(realSrcAddress+i)){
			memManager->markTaintedMemory(realDstAddress+i);
		}
	}
}