/*******************************************************************

 Title:ins_handler.cpp
 Function:To implement handler functions
 Description:
 Source file to implement handler functions
 Version: 1.0
 Date and author: 2009.07.26 hsqfire
*******************************************************************/

#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include "ins_handler.h"

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

/* define handler table*/
int (*handlerFun[])(INS ins,int srcA,int srcB,int srcC,
				int dstA,int dstB,int dstC)={
					defaultHandler,
					popRHandler,
					pushRHandler,
					movIRHandler,
					movRMHandler,
					movMRHandler,
					movRRHandler,
					callMHandler,
					returnIHandler,
					leaMRHandler,
					leaRMHandler
};

/* handle result output file*/
FILE *output;

/* temporate variable*/
int regValue;

/* define data structor to record the state of registers*/
#define REGNUM 30
int regState[REGNUM];


/******************************************************************
 Title:defaultHandler
 Function:Default handler to handle instruction
 Input:
 int value:Value of some a register
 Output:
******************************************************************/
VOID getRegisterValue(int value)
{
	regValue = value;
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
	INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)getRegisterValue, 
			IARG_REG_VALUE,baseReg,
			IARG_END);
	int valueBaseReg = regValue;
	INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)getRegisterValue, 
			IARG_REG_VALUE,indexReg,
			IARG_END);
	int valueIndexReg = regValue;
	unsigned int realAddress = displacement+valueBaseReg+valueIndexReg;
	int state = memManager->isTainted(realAddress);
	if(state==1){
		REG dstReg = INS_OperandReg(ins,0);
		regState[dstReg] = 1;
	}else{
		REG dstReg = INS_OperandReg(ins,0);
		regState[dstReg] = 1;
	}
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
	INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)getRegisterValue, 
			IARG_REG_VALUE,baseReg,
			IARG_END);
	int valueBaseReg = regValue;
	INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)getRegisterValue, 
			IARG_REG_VALUE,indexReg,
			IARG_END);
	int valueIndexReg = regValue;
	unsigned int realAddress = displacement+valueBaseReg+valueIndexReg;
	REG srcReg = INS_OperandReg(ins,1);
	int state = regState[srcReg];
	if(state==1){
		memManager->markTaintedMemory(realAddress);
	}else{
		memManager->dismarkTaintedMemory(realAddress);
	}
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
	REG baseReg = INS_OperandMemoryBaseReg(ins,0);
	INT64 displacement = INS_OperandMemoryDisplacement(ins,0);
	REG indexReg = INS_OperandMemoryIndexReg(ins,0);
	UINT32 scale = INS_OperandMemoryScale(ins,0);
	INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)getRegisterValue, 
			IARG_REG_VALUE,baseReg,
			IARG_END);
	int valueBaseReg = regValue;
	INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)getRegisterValue, 
			IARG_REG_VALUE,indexReg,
			IARG_END);
	int valueIndexReg = regValue;
	unsigned int realAddress = displacement+valueBaseReg+valueIndexReg;
	int state = memManager->isTainted(realAddress);
	if(state==1){
		REG dstReg = INS_OperandReg(ins,0);
		regState[dstReg] = 1;
	}else{
		REG dstReg = INS_OperandReg(ins,0);
		regState[dstReg] = 1;
	}
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
	handlerFun[0] = defaultHandler;	//#0
	handlerFun[1] = popRHandler;
	handlerFun[2] = pushRHandler;
	handlerFun[3] = movIRHandler;
	handlerFun[4] = movRMHandler;
	handlerFun[5] = movMRHandler;	//#5
	handlerFun[6] = movRRHandler;
	handlerFun[7] = callMHandler;
	handlerFun[8] = returnIHandler;
	handlerFun[9] = leaMRHandler;
	handlerFun[10] = leaRMHandler;	//#10
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
	handlerTable[76547]=5;	//mov [mem addr] REG
	handlerTable[76546]=6;	//mov REG REG
	handlerTable[134914]=2;	//push REG
	handlerTable[68354]=10;	//lea REG [mem addr]
	handlerTable[9731]=7;	//call addr
	handlerTable[121602]=1;	//pop REG
	handlerTable[76546]=4;	//mov REG [mem addr]
	handlerTable[138753]=8;	//ret immd
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
	
}


/******************************************************************
 Title:handlerInsProxy
 Function:Define function to begin handling instruction
 Input:
 void
 Output:
******************************************************************/
void begin()
{
	for(int i=0;i<REGNUM;i++){
		regState[i]=0;
	}
	output = fopen("TaintResult.out", "w");
}


/******************************************************************
 Title:handlerInsProxy
 Function:Define function to end handling instruction
 Input:
 void
 Output:
******************************************************************/
void end()
{
	fclose(output);
}

