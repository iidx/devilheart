/*******************************************************************

 Title:MyPinTool.cpp
 Function:To build a simple pin tool.
 Description:
 This tool is to print out the value of ES,DS,SI,DI and CX before
 rep movsb instruction executing
 Version: 1.0
 Date and author: 2009.07.07 hsqfire
*******************************************************************/

#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include "pin.H"
#include "decoder.h"
#include "mem_recorder.h"
#include "test_recorder.h"


/* File to save data for this application*/
//FILE * trace;

/* Data strctutor to record the state of memory*/
MemoryRecorder *memManager;

/******************************************************************
 Title:printRegisters
 Function:This function is called to print value of some registers.
 Input:
 int es:Value of register ES.
 int ds:Value of register DS.
 int si:Value of register SI.
 int di:Value of register DI.
 int cx:Value of register CX.
 Output:
 VOID
******************************************************************/
VOID printRegisters(int es,int ds,int si,int di,int cx )
{
	/*fprintf(trace,"ES:%d  ",es);
	fprintf(trace,"DS:%d  ",ds);
	fprintf(trace,"SI:%d  ",si);
	fprintf(trace,"DI:%d  ",di);
	fprintf(trace,"CX:%d\n",cx);*/
}

VOID decode(INS ins)
{
	OPCODE opcode  = INS_Opcode(ins);
	UINT32 operandCount = INS_OperandCount(ins);
	UINT insExt = INS_Extension(ins);
	unsigned int realOpcode = opcode&0xffff;
	unsigned int insKind = INSNUM(realOpcode,1);
	/*for(int i = 0;i<operandCount;i++){
		if(INS_OperandIsAddressGenerator(ins,i))
			fprintf(trace,"operand%d is address generator\n",i);
		else if(::INS_OperandIsMemory(ins,i))
			fprintf(trace,"operand%d is address\n",i);
		else if(::INS_OperandIsImmediate(ins,i))
			fprintf(trace,"operand%d is immediate\n",i);
		else if(::INS_OperandIsReg(ins,i))
			fprintf(trace,"operand%d is register\n",i);
		else if(INS_OperandIsBranchDisplacement(ins,i))
			fprintf(trace,"operand%d is branch displacement\n",i);
		else fprintf(trace,"operand%d is other type\n",i);
	}*/
	/*fprintf(trace,"Opcode:%d | operand count:%d\n",realOpcode,operandCount);
	OperandKind kind = getOperandKind(ins);
	fprintf(trace,"insNum:%d\n",INSNUM(opcode,kind));*/
}

void manulMarkTainted()
{
	//memManager->markTaintedBlock(0x0000,0x00001234);
	unsigned int taintedAddress[]={
		0x0000ABCD,0xABCD0000,0xDCBA0000,0x32165498,0x74185296,0x96385274,0x54862139,0x24753689,0x15962384,0x78415962,
		0x12ff5c,0x7ffdf000,0x12ffdc,0x77d9446c,0x7ffdf030,0x12fff8,
		0x403000,0x403001,0x403002,0x403003,0x403004,0x403005,0x403006
	};
	for(int i=0;i<23;i++){
		memManager->markTaintedMemory(taintedAddress[i]);
	}
}

/******************************************************************
 Title:instruction
 Function:Pin calls this function every time a new instruction is 
 executed
 Input:
 RTN rtn:The current instruction.
 VOID *v:The second argument.
 Output:
 VOID
******************************************************************/
VOID instruction(INS ins, VOID *v)
{
	/*fprintf(trace,insName.c_str());
	fprintf(trace,"\n");
	decode(ins);*/
	OPCODE opcode  = INS_Opcode(ins);
	UINT32 operandCount = INS_OperandCount(ins);
	UINT insExt = INS_Extension(ins);
	unsigned int realOpcode = opcode&0xffff;
	OperandKind kind = getOperandKind(ins);
	unsigned int insKind = INSNUM(realOpcode,kind);
	handleIns(insKind,ins);
}


/******************************************************************
 Title:fini
 Function:This function is called when the application exits.
 Input:
 INT32 code:The first argument.
 VOID *v:The second argument.
 Output:
 VOID
******************************************************************/
VOID fini(INT32 code, VOID *v)
{
	endHandle();
    /*fprintf(trace, "#eof\n");
    fclose(trace);*/
	/*fprintf(log,"#eof\n");
	fclose(log);*/
}


/******************************************************************
 Title:main
 Function:Entrance function of the application
 Input:
 int argc:The number of the arguments
 char * argv[]:The arguments list passed by command line
 Output:
 int
 return value:0 is correct, negative means a exception
*******************************************************************/
int main(int argc, char * argv[])
{
	MemoryRecorder recorder;
	memManager = &recorder;
	manulMarkTainted();
	/* print out the state of memory*/
	

	initHandlerFuns();
	initHandlerTable();
	beginHandle();

	fprintf(output,"****************************************************\n");
	fprintf(output,"Before the application\n");
	memManager->printState(output);

    /* Initialize pin */
    PIN_Init(argc, argv);

    /* Register instruction to be called to instrument instruction */
    INS_AddInstrumentFunction(instruction, 0);

    /* Register fini to be called when the application exits */
    PIN_AddFiniFunction(fini, 0);
    
    /* Start the program, never returns */
    PIN_StartProgram();
    
	//endHandle();
    return 0;
}
