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
	if (insName.find("rep movsb")!=string::npos)
    {
        /*Insert a call to printip before rep movesb instruction*/
		INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)printRegisters, 
			IARG_REG_VALUE,REG_SEG_ES, 
			IARG_REG_VALUE,REG_SEG_DS , 
			IARG_REG_VALUE,REG_ESI , 
			IARG_REG_VALUE,REG_EDI ,
			IARG_REG_VALUE,REG_CX,
			IARG_END);
    }
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
