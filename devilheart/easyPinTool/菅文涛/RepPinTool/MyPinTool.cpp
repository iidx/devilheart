#include <stdio.h>
#include "pin.H"
#include "pin_isa.H"
#include <iostream>
#include <fstream>

std::ofstream* out = 0;

//=======================================================
//  Analysis routines
//=======================================================

// Move from memory to register
void ShowRegValue(ADDRINT * es,ADDRINT * ds,ADDRINT * si,ADDRINT * di,ADDRINT * cx)
{
	*out<<"Register value"<<endl;
	*out <<"ES:"<<es<<endl;
	*out<<"DS:"<<ds<<endl;
	*out<<"ESI:"<<si<<endl;
	*out<<"EDI:"<<di<<endl;
	*out<<"ECX:"<<cx<<endl;
}

//=======================================================
// Instrumentation routines
//=======================================================

VOID GetReginfo(INS ins, VOID* v)
{
    string insstring=INS_Disassemble(ins);
	if (insstring.at(0)=='r'&&insstring.at(1)=='e'&&insstring.at(2)=='p')
    {
        INS_InsertCall(ins,
                       IPOINT_BEFORE,
                       AFUNPTR(ShowRegValue),
                       IARG_REG_VALUE,
                       REG_SEG_ES, //es
                       IARG_REG_VALUE,
                       REG_SEG_DS, 	//ds	
					   IARG_REG_VALUE,
					   REG_ESI,		//si
					   IARG_REG_VALUE,
					   REG_EDI, 			//di
					   IARG_REG_VALUE,
					   REG_ECX,		//cx
                       IARG_END);
		INS_InsertCall(ins,
                       IPOINT_AFTER,
                       AFUNPTR(ShowRegValue),
                       IARG_REG_VALUE,
                       REG_SEG_ES, //es
                       IARG_REG_VALUE,
                       REG_SEG_DS, 	//ds	
					   IARG_REG_VALUE,
					   REG_ESI,		//si
					   IARG_REG_VALUE,
					   REG_EDI, 			//di
					   IARG_REG_VALUE,
					   REG_ECX,		//cx
                       IARG_END);
    }
}

int main(int argc, char * argv[])
{
    // Write to a file since cout and cerr maybe closed by the application
    out = new std::ofstream("regsinfo.out");

    // Initialize pin & symbol manager
    PIN_Init(argc, argv);
    PIN_InitSymbols();

    // Register EmulateLoad to be called to instrument instructions
    INS_AddInstrumentFunction(GetReginfo, 0);

    // Never returns
    PIN_StartProgram();   
    return 0;
}

