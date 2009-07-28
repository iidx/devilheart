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
#include "test_recorder.h"


/*File to save data for this application*/
FILE * trace;

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
	fprintf(trace,"ES:%d  ",es);
	fprintf(trace,"DS:%d  ",ds);
	fprintf(trace,"SI:%d  ",si);
	fprintf(trace,"DI:%d  ",di);
	fprintf(trace,"CX:%d\n",cx);
}

VOID decode(INS ins)
{
	OPCODE opcode  = INS_Opcode(ins);
	UINT32 operandCount = INS_OperandCount(ins);
	UINT insExt = INS_Extension(ins);
	unsigned int realOpcode = opcode&0xffff;
	unsigned int insKind = INSNUM(realOpcode,1);
	for(int i = 0;i<operandCount;i++){
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
	}
	fprintf(trace,"Opcode:%d | operand count:%d\n",realOpcode,operandCount);
	
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
	/*Check whether the current instruction is what we need*/
	string insName = INS_Disassemble(ins);
	//if (insName.find("rep movsb")!=string::npos)
 //   {
 //       /*Insert a call to printip after rep movesb instruction*/
	//	INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)printRegisters, 
	//		IARG_REG_VALUE,REG_SEG_ES, 
	//		IARG_REG_VALUE,REG_SEG_DS , 
	//		IARG_REG_VALUE,REG_ESI , 
	//		IARG_REG_VALUE,REG_EDI ,
	//		IARG_REG_VALUE,REG_CX,
	//		IARG_END);
 //   }
	fprintf(trace,insName.c_str());
	fprintf(trace,"\n");
	decode(ins);
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
    fprintf(trace, "#eof\n");
    fclose(trace);
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
    trace = fopen("itrace.out", "w");
    
    /* Initialize pin */
    PIN_Init(argc, argv);

    /* Register instruction to be called to instrument instruction */
    INS_AddInstrumentFunction(instruction, 0);

    /* Register fini to be called when the application exits */
    PIN_AddFiniFunction(fini, 0);
    
    /* Start the program, never returns */
    PIN_StartProgram();
    
    return 0;
}
