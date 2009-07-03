/*******************************************************************

 Title:MyPinTool.cpp
 Function:To build a simple pin tool.
 Description:
 This tool is to print out the context saved by the notepad to a 
 output file.
 Version: 1.0
 Date and author: 2009.07.02 hsqfire
*******************************************************************/

#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include "pin.H"


/* Define the struct to hold the context of a procedure */
typedef struct RtnCount
{
    string _name;
    string _image;
    ADDRINT _address;
    RTN _rtn;
    UINT64 _rtnCount;
    UINT64 _icount;
    struct RtnCount * _next;
	char* context;
} RTN_COUNT;

/* Linked list of instruction counts for each routine */
RTN_COUNT * RtnList = 0;


/******************************************************************
 Title:docount
 Function:This function is called before every instruction is 
 executed.
 Input:
 UINT64* counter:The number of instructions in a routine.
 Output:
 void
******************************************************************/
VOID docount(UINT64 *counter)
{
    (*counter)++;
}
    

/******************************************************************
 Title:stripPath
 Function:This function is to get the path of the loaded image
 Input:
 const char *path:The path of the loaded image.
 Output:
 char *:The real path of the image
******************************************************************/
const char * stripPath(const char *path)
{
    const char *file = strrchr(path,'/');
    if (file)
        return file+1;
    else
        return path;
}


/******************************************************************
 Title:printContext
 Function:This function is print the context saved by notepad to a
 output file
 Input:
 const char *context:The context saved by the notepad.
 Output:
 VOID
******************************************************************/
VOID printContext(char *context)
{
	ofstream count("proccountTest.out",ios_base::app);
	count<<context<<endl;
	count.flush();
	count.close();
}


/******************************************************************
 Title:stripPath
 Function:Pin calls this function every time a new rtn is executed
 Input:
 RTN rtn:The current routine.
 VOID *v:The second argument.
 Output:
 VOID
******************************************************************/
VOID routine(RTN rtn, VOID *v)
{
    RTN_COUNT * rc = new RTN_COUNT;
    rc->_name = RTN_Name(rtn);
    rc->_image = stripPath(IMG_Name(SEC_Img(RTN_Sec(rtn))).c_str());
    rc->_address = RTN_Address(rtn);
    rc->_icount = 0;
    rc->_rtnCount = 0;
    rc->_next = RtnList;
    RtnList = rc;
            
    RTN_Open(rtn);
	if(rc->_name.compare("WriteFile")==0)
	{
		RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR)printContext,IARG_FUNCARG_ENTRYPOINT_VALUE,1, IARG_END);
	}
    RTN_Close(rtn);
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
******************************************************************/
int main(int argc, char * argv[])
{
    PIN_InitSymbols();

    /* Initialize pin */
    PIN_Init(argc, argv);

    /* Register Routine to be called to instrument rtn */
    RTN_AddInstrumentFunction(routine, 0);

    /* Register Fini to be called when the application exits */
    PIN_AddFiniFunction(fini, 0);
    
    /* Start the program, never returns */
    PIN_StartProgram();
    
    return 0;
}