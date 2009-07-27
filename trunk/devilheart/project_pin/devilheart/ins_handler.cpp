/*******************************************************************

 Title:ins_handler.cpp
 Function:To implement handler functions
 Description:
 Source file to implement handler functions
 Version: 1.0
 Date and author: 2009.07.26 hsqfire
*******************************************************************/

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
					returnMHandler,
					leaMRHandler
};


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
int leaMRHandler(INS ins,int srcA,int srcB,int srcC,int dstA,int dstB,int dstC)
{
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
	handlerFun[0] = defaultHandler;
	handlerFun[1] = popRHandler;
	handlerFun[2] = pushRHandler;
	handlerFun[3] = movIRHandler;
	handlerFun[4] = movRMHandler;
	handlerFun[5] = movMRHandler;
	handlerFun[6] = movRRHandler;
	handlerFun[7] = callMHandler;
	handlerFun[8] = returnMHandler;
	handlerFun[9] = leaMRHandler;
}


/******************************************************************
 Title:initHandlerTable
 Function:To init handler table
 Input:
 void
 Output:
******************************************************************/
void initHandlerTable()
{
	handlerTable[205]=2;
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
	int handlerNum = handlerTable[insNum];
	int (*handler)(INS,int,int,int,int,int,int);
	handler = handlerFun[handlerNum];
	int result = handler(ins,srcA,srcB,srcC,dstA,dstB,dstC);
}

