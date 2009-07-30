/*******************************************************************

 Title:ins_handler.cpp
 Function:To implement handler functions
 Description:
 Source file to implement handler functions
 Version: 1.4
 Date and author: 2009.07.26 hsqfire
*******************************************************************/

#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include "ins_handler.h"
#include "hooks.h"

/* Define src and dst operand*/
unsigned int srcA,srcB,srcC;
unsigned int dstA,dstB,dstC;

HandlerTable handlerTable;

/* Define handler functions
 * Function prototype:int func(INS,int,int,int,int,int,int)
 * New handler function can be add here
 */
int defaultHandler(INS,int,int,int,int,int,int);
int popRHandler(INS,int,int,int,int,int,int);
int pushRHandler(INS,int,int,int,int,int,int);
int movIRHandler(INS,int,int,int,int,int,int);
int movRMHandler(INS,int,int,int,int,int,int);
int movMRHandler(INS,int,int,int,int,int,int);
int movRRHandler(INS,int,int,int,int,int,int);
int callMHandler(INS,int,int,int,int,int,int);
int returnIHandler(INS,int,int,int,int,int,int);
int leaMRHandler(INS,int,int,int,int,int,int);
int leaRMHandler(INS,int,int,int,int,int,int);
int movRIHandler(INS,int,int,int,int,int,int);
int movMIHandler(INS,int,int,int,int,int,int);
int repMovsbHandler(INS,int,int,int,int,int,int);

/* define handler table*/
int (*handlerFun[])(INS ins,int srcA,int srcB,int srcC,
				int dstA,int dstB,int dstC)={
		defaultHandler,	//#0
		popRHandler,	//#1
		pushRHandler,
		movIRHandler,
		movRMHandler,
		movMRHandler,	//#5
		movRRHandler,
		callMHandler,
		returnIHandler,
		leaMRHandler,
		leaRMHandler,	//#10
		movRIHandler,
		movMIHandler,
		repMovsbHandler
};

/* handle result output file*/
FILE *output;

/* handle log file*/
FILE *log;

/* temporate variable*/
int regValue;
int memAddr;

/* accumulator*/
int countHandledIns;
int countAllIns;

/* define data structor to record the state of registers*/
#define REGNUM 100
int *regState;


/******************************************************************
 Title:getRegisterValue
 Function:Get the value of the register
 Input:
 int value:Value of some a register
 Output:
******************************************************************/
VOID getRegisterValue(int value)
{
	regValue = value;
}

/******************************************************************
 Title:getMemAddress
 Function:Get the memory address
 Input:
 int value:Memory address
 Output:
******************************************************************/
VOID getMemAddress(ADDRINT addr)
{
	//memAddr = (int)addr;
	fprintf(log,"Address ins:0x%x\n",addr);
	PIN_SafeCopy(&memAddr, &addr, sizeof(ADDRINT));

}

/******************************************************************
 Title:defaultHandler
 Function:Default handler to handle instruction
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int defaultHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	string disIns = INS_Disassemble(ins);
	fprintf(log,"Unhandle instruction: %s\n",disIns.c_str());
	countAllIns++;
	return 0;
}

/******************************************************************
 Title:popRHandler
 Function:Handler to handle instruction "Pop REG"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int popRHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	countAllIns++;
	countHandledIns++;
	return 0;
}


/******************************************************************
 Title:pushRHandler
 Function:Handler to handle instruction "Push REG"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int pushRHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	countAllIns++;
	countHandledIns++;
	return 0;
}


/******************************************************************
 Title:movIRHandler
 Function:Handler to handle instruction "mov immd REG"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int movIRHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	countAllIns++;
	countHandledIns++;
	return 0;
}


/******************************************************************
 Title:movRMHandler
 Function:Handler to handle instruction "mov REG [mem addr]"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int movRMHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	REG baseReg = INS_OperandMemoryBaseReg(ins,1);
	INT64 displacement = INS_OperandMemoryDisplacement(ins,1);
	REG indexReg = INS_OperandMemoryIndexReg(ins,1);
	UINT32 scale = INS_OperandMemoryScale(ins,1);
	if(REG_valid(baseReg)){
		INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)getRegisterValue, 
				IARG_REG_VALUE,baseReg,
				IARG_END);
	}
	int valueBaseReg = regValue;
	if(REG_valid(indexReg)){
		INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)getRegisterValue, 
				IARG_REG_VALUE,indexReg,
				IARG_END);
	}
	int valueIndexReg = regValue;
	unsigned int realAddress = displacement+valueBaseReg+valueIndexReg*scale;
	if(INS_IsMemoryRead(ins)){
		INS_InsertCall(ins,
						   IPOINT_BEFORE,
						   AFUNPTR(movRMHook),
						   IARG_UINT32,
                           REG(INS_OperandReg(ins, 0)),
                           IARG_MEMORYREAD_EA,
						   IARG_END);
	}else{
		fprintf(log,"Error at reading memory\n");
		return -1;
	}
	countAllIns++;
	countHandledIns++;
	return 0;
}


/******************************************************************
 Title:movMRHandler
 Function:Handler to handle instruction "mov [mem addr] REG"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int movMRHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	REG baseReg = INS_OperandMemoryBaseReg(ins,0);
	INT64 displacement = INS_OperandMemoryDisplacement(ins,0);
	REG indexReg = INS_OperandMemoryIndexReg(ins,0);
	UINT32 scale = INS_OperandMemoryScale(ins,0);
	if(REG_valid(baseReg)){
		INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)getRegisterValue, 
				IARG_REG_VALUE,baseReg,
				IARG_END);
	}
	//regValue = 10;
	int valueBaseReg = regValue;
	if(REG_valid(indexReg)){
		INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)getRegisterValue, 
				IARG_REG_VALUE,indexReg,
				IARG_END);
	}
	int valueIndexReg = regValue;
	unsigned int realAddress = displacement+valueBaseReg+valueIndexReg*scale;
	if(INS_IsMemoryWrite(ins)){
		INS_InsertCall(ins,
						   IPOINT_BEFORE,
						   AFUNPTR(movMRHook),
						   IARG_UINT32,
						   REG(INS_OperandReg(ins, 1)),
						   IARG_MEMORYWRITE_EA,
						   IARG_END);
	}else{
		fprintf(log,"Error at writing memory\n");
		return -1;
	}
	countAllIns++;
	countHandledIns++;
	return 0;
}


/******************************************************************
 Title:movRRHandler
 Function:Handler to handle instruction "mov REG REG"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int movRRHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	REG dstReg = INS_OperandMemoryBaseReg(ins,0);
	REG srcReg = INS_OperandReg(ins,1);
	int state = regState[srcReg];
	if(state==1){
		regState[dstReg]=1;
	}else{
		regState[dstReg]=0;
	}
	countAllIns++;
	countHandledIns++;
	return 0;
}


/******************************************************************
 Title:callMHandler
 Function:Handler to handle instruction "call address"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int callMHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	countAllIns++;
	countHandledIns++;
	return 0;
}


/******************************************************************
 Title:returnIHandler
 Function:Handler to handle instruction "ret immd"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int returnIHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	countAllIns++;
	countHandledIns++;
	return 0;
}


/******************************************************************
 Title:leaMRHandler
 Function:Handler to handle instruction "lea [mem addr],REG"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int leaMRHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	countAllIns++;
	countHandledIns++;
	return 0;
}

/******************************************************************
 Title:leaRMHandler
 Function:Handler to handle instruction "lea REG,[mem addr]"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int leaRMHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	/*unsigned int realAddress = INS_OperandImmediate(ins,1);
	int state = memManager->isTainted(realAddress);
	if(state==1){
		REG dstReg = INS_OperandReg(ins,0);
		regState[dstReg] = 1;
	}else{
		REG dstReg = INS_OperandReg(ins,0);
		regState[dstReg] = 1;
	}*/
	/*if(INS_IsMemoryRead(ins)){
		fprintf(log,"lea ins read memory\n");
	}else if(INS_IsMemoryWrite(ins)){
		fprintf(log,"lea ins write memory\n");
	}*/
	countAllIns++;
	countHandledIns++;
	return 0;
}


/******************************************************************
 Title:movRIHandler
 Function:Handler to handle instruction "mov REG,immd"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int movRIHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	countAllIns++;
	countHandledIns++;
	return 0;
}


/******************************************************************
 Title:movMIHandler
 Function:Handler to handle instruction "mov [mem addr] immd"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int movMIHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	countAllIns++;
	countHandledIns++;
	return 0;
}


/******************************************************************
 Title:repMovsbHandler
 Function:Handler to handle instruction "rep movsb"
 Input:
 INS ins:Instruction to be handled.
 int srcA:The 1st src operand.
 int srcB:The 2nd src operand.
 int srcC:The 3rd src operand.
 int dstA:The 1st dst operand.
 int dstB:The 2nd dst operand.
 int dstC:The 3rd dst operand.
 Output:
 int
 Return value:-1 means unable to handle the instruction
******************************************************************/
int repMovsbHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
	if(INS_IsMemoryWrite(ins)&&INS_IsMemoryRead(ins)){
		INS_InsertCall(ins,
						   IPOINT_BEFORE,
						   AFUNPTR(movMRHook),
						   IARG_UINT32,
						   REG_ECX,
						   IARG_MEMORYREAD_EA,
						   IARG_MEMORYWRITE_EA,
						   IARG_END);
	}else{
		fprintf(log,"Error at writing memory\n");
		return -1;
	}
	countAllIns++;
	countHandledIns++;
	return 0;
}


/******************************************************************
 Title:initHandlerFuns
 Function:To init ins<->handler table
 Input:
 void
 Output:
******************************************************************/
void initHandlerFuns()
{
	//handlerFun[0] =	0	//defaultHandler	#0
	//handlerFun[1] =	1	//popRHandler
	//handlerFun[2] =	2	//pushRHandler
	//handlerFun[3] =	3	//movIRHandler
	//handlerFun[4] =	4	//movRMHandler
	//handlerFun[5] =	5	//movMRHandler	#5
	//handlerFun[6] =	6	//movRRHandler
	//handlerFun[7] =	7	//callMHandler
	//handlerFun[8] =	8	//returnIHandler
	//handlerFun[9] =	9	//leaMRHandler
	//handlerFun[10] =10	//leaRMHandler	#10
	//handlerFun[11] =11	//movRIHandler
	//handlerFun[12] =12	//movMIHandler
}


/******************************************************************
 Title:initHandlerTable
 Function:To init handler: table handlerTable[insNum]=handlerNum
 Input:
 void
 Output:
******************************************************************/
void initHandlerTable()
{
	handlerTable[76579]=5;	//mov [mem addr] REG
	handlerTable[76578]=6;	//mov REG REG
	handlerTable[134706]=2;	//push REG
	handlerTable[68146]=10;	//lea REG [mem addr]
	handlerTable[9763]=7;	//call addr
	handlerTable[121394]=1;	//pop REG
	handlerTable[76594]=4;	//mov REG [mem addr]
	handlerTable[138785]=8;	//ret immd
	handlerTable[76562]=11;	//mov REG immd
	handlerTable[76563]=12;	//mov [mem addr] immd
	handlerTable[83507]=13;	//rep movsb
}


/******************************************************************
 Title:handlerInsProxy
 Function:To to handle the instruction
 Input:
 unsigned int insNum:ins index to look for the handler
 INS ins:The instrcution to be handled
 Output:
******************************************************************/
void handlerInsProxy(unsigned int insNum,INS ins)
{
	HandlerTable::iterator i;
	i = handlerTable.find(insNum);
	if(i == handlerTable.end()){
		int (*handler)(INS,int,int,int,int,int,int);
		handler = handlerFun[0];
		int result = handler(ins,srcA,srcB,srcC,dstA,dstB,dstC);
	}else{
		int handlerNum = handlerTable[insNum];
		int (*handler)(INS,int,int,int,int,int,int);
		handler = handlerFun[handlerNum];
		int result = handler(ins,srcA,srcB,srcC,dstA,dstB,dstC);
	}
	//int (*handler)(INS,int,int,int,int,int,int);
	//handler = handlerFun[0];
	//int result = handler(ins,srcA,srcB,srcC,dstA,dstB,dstC);
}


/******************************************************************
 Title:beginHandle
 Function:Define function to begin handling instruction
 Input:
 void
 Output:
******************************************************************/
void beginHandle()
{
	regState = (int*)malloc(sizeof(int)*REGNUM);
	for(int i=0;i<REGNUM;i++){
		regState[i]=0;
	}
	output = fopen("TaintResult.out", "w");
	log = fopen("TaintLog.out","w");
	countHandledIns = 0;
	countAllIns = 0;
	regValue = 0;
}


/******************************************************************
 Title:endHandle
 Function:Define function to end handling instruction
 Input:
 void
 Output:
******************************************************************/
void endHandle()
{	
	/* print out the log			*/
	fprintf(log,"*****************************************************\n");
	fprintf(log,"Count of instruction:%d\n",countAllIns);
	fprintf(log,"Handle %d instruction successfully!\n",countHandledIns);
	fprintf(log,"#eof");
	fclose(log);

	/* print out the state of memory*/
	fprintf(output,"****************************************************\n");
	fprintf(output,"After the application\n");
	memManager->printState(output);
	fprintf(output,"#eof");
	fclose(output);
	
}

