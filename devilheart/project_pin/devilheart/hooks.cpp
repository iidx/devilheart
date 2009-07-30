#include "hooks.h"

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

VOID repMovsbHandler(int ecx,ADDRINT *srcAddr,ADDRINT *dstAddr)
{
	unsigned int realSrcAddress = (int)srcAddr;
	unsigned int realDstAddress = (int)dstAddr;
	for(int i=0;i<ecx;i++)
	{
		if(memManager->isTainted(realSrcAddress+i)){
			memManager->markTaintedMemory(realDstAddress+i);
		}
	}
}