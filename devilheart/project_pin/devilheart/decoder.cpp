/*******************************************************************

 Title:decode.h
 Function:Implement interfaces to decode instructions
 Description:
 Implement interfaces to decode instructions
 Version: 1.1
 Date and author: 2009.07.26 hsqfire
*******************************************************************/

#include "decoder.h"


/******************************************************************
 Title:handlerIns
 Function:To handle the instruction
 Input:
 unsigned int insNum:ins index to look for the handler
 INS ins:The instrcution to be handled
 Output:
******************************************************************/
void handleIns(unsigned int insNum,INS ins)
{
	handlerInsProxy(insNum,ins);
}

/******************************************************************
 Title:getOperandKind
 Function:To get the operand kind
 Input:
 INS ins:The instrcution to be handled
 Output:
 OperandKind
 Return value:operand kind to locate the handler function
******************************************************************/
OperandKind getOperandKind(INS ins)
{
	srcA = 0;
	srcB = 0;
	srcC = 0;
	dstA = 0;
	dstB = 0;
	dstC = 0;
	int operands[] = {0,0};
	UINT operandCount = INS_OperandCount(ins);
	if(operandCount == 0)
		return NONE;
	int operandInd = 0;
	for(int i=0;i<operandCount;i++){
		if(operandInd>1)
			break;
		if(INS_OperandIsAddressGenerator(ins,i)){
			operands[operandInd] = 3;
			operandInd++;
		}
		else if(INS_OperandIsMemory(ins,i)){
			operands[operandInd] = 3;
			operandInd++;
		}
		else if(INS_OperandIsImmediate(ins,i)){
			operands[operandInd] = 1;
			operandInd++;
		}
		else if(INS_OperandIsReg(ins,i)){
			operands[operandInd] = 2;
			operandInd++;
		}
		else if(INS_OperandIsBranchDisplacement(ins,i)){
			operands[operandInd] = 2;
			operandInd++;
		}
		else continue;
	}
	unsigned int firstOp = operands[0]&0xF;
	unsigned int secondOp = operands[1]&0xF;
	return (OperandKind)((secondOp<<8)|firstOp);
}