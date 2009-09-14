/*******************************************************************
 Title:TaintSource.cpp
 Function:to find the taintsource in program and record the in memory
 Description:
 Define some data structors to record the state of memory in size of
 4G at most.
 Version: 1.1
 Date and author: 2009.07.24 ethenjean
*******************************************************************/

#include "taint_source.h"
#include "decoder.h"

/*the flag of tainted source*/
int flag=0;

/*record the size of file*/
ADDRINT sizeH;
ADDRINT sizeL;

/*record the base address of file mapping to memory*/
ADDRINT baseaddr;

CreateFileWData CFWdata[50];
CreateFileMappingWData CFMWdata[50];
MapViewOfFileData MVFdata[50];

/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "malloctrace.out", "specify trace file name");

/* ===================================================================== */

INT32 Usage()
{
    cerr <<
        "This tool produces a trace of calls to malloc.\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}


/******************************************************************
 Title:FindObjectByName
 Function:get the file name from the args
 Input:
 wchar_t name: the source path of file opened
 Output:
******************************************************************/
 
VOID FindObjectByName(wchar_t *name)
{
    
	//store the file file name
	string NameStr="";
	//store the source point
	wchar_t* name0=name;
	//read the content from the args name
	for(;*name!='\0';name++)
	{
		NameStr+=*name;
	}
    //store the source point
	name=name0;
    //compare with the defined file name
	if(NameStr.find(FILE_NAME)!=string::npos)
	{
        int i;
        //find the first place not used
        for(i=0;CFWdata[i].sign !=0;i++)
            ;
        //set the handle value to -2 so we sign it
        CFWdata[i].CFWHandle = -2;
        CFWdata[i].sign = 1;
        CFWdata[i+1].sign = 0;
	}
}

/******************************************************************
 Title:SetCFWReturnValue
 Function:store the infomation from the function createfilew
 Input:
 ADDRINT fileHandle:the file handle returned from createfilew
 Output:
******************************************************************/
VOID SetCFWReturnValue(ADDRINT fileHandle)
{
    //store the return value of function createfilew
	if(fileHandle)
	{
        int i;
        for(i=0;CFWdata[i].sign != 0;i++)
        {
            if(CFWdata[i].CFWHandle==-2)
            {
                CFWdata[i].CFWHandle =fileHandle;
            }
        }
	}
}

/******************************************************************
 Title:FindMatchingCFMW
 Function:find if args of CreateFileMapping match with the return value of CreateFileW
 Input:
 ADDRINT hfile:the file handle from args of CreateFIleMapping
 ADDRINT offsethigh:the size of file high bit value
 ADDRINT offsetlow: the size of file low bit value
 Output:
******************************************************************/
VOID FindMatchingCFMW(ADDRINT hfile,ADDRINT offsethigh,ADDRINT offsetlow)
{
    int i;
    for(i=0;CFWdata[i].sign !=0;i++)
    {
        if(CFWdata[i].CFWHandle == hfile )
        {
            int j;
            for(j=0;CFMWdata[j].sign!=0;j++)
                ;
            CFMWdata[j].sign=1;
            CFMWdata[j+1].sign = 0;
            CFMWdata[j].Filedata = &CFWdata[i];
            CFMWdata[j].sizeHigh = offsethigh;
            CFMWdata[j].sizeLow = offsetlow;
            CFMWdata[j].CFMWHandle = -2;
        }
    }
}

/******************************************************************
 Title:SetCFMWReturnValue
 Function:set the return value from CreateFileMappingW 
 Input:
 UINT32 mappingHandle: the file handle from the args of CreateFileMappingW
 Output:
******************************************************************/
VOID SetCFMWReturnValue(UINT32 mappingHandle)
{

	//find each the handle value is -2 andl set the handle value
    int i;
    for(i=0;CFMWdata[i].sign!=0;i++)
    {
        if(CFMWdata[i].CFMWHandle == -2)
        {
            CFMWdata[i].CFMWHandle = mappingHandle;
        }
    }
}

/******************************************************************
 Title:FindMachingMVF
 Function:find the matched handle of data stored in CFMWdata
 Input:
 ADDRINT mappingHandle:the return value of function MapViewOfFile
 Output:
******************************************************************/
VOID FindMachingMVF(ADDRINT mappingHandle)
{

    int i;
    for(i=0;CFMWdata[i].sign!=0;i++)
    {
        int j;
        if(CFMWdata[i].CFMWHandle == mappingHandle)
        {
            for(j=0;MVFdata[j].sign!=0;j++)
            ;
            MVFdata[j].FileMappingdata = &CFMWdata[i];
            MVFdata[j].sign=1;
            MVFdata[j+1].sign = 0;
            MVFdata[j].MVFReturnHandle = -2;
        }
    }
}

/******************************************************************
 Title:SetMappingBase
 Function:set the matched MVFdata and set value to base
 Input:
 ADDRINT base:the base place of file mapping in memory
 Output:
******************************************************************/
VOID SetMappingBase(ADDRINT base)
{
	
    int i;
    for(i=0;MVFdata[i].sign!=0;i++)
    {
		if(MVFdata[i].MVFReturnHandle==-2){
            MVFdata[i].MVFReturnHandle=base;
			flag=1;
			//fprintf(output,"****************************************************\n");
			//fprintf(output,"Before the application\n");
			//memManager->printState(output);
		}
    }
	
}

/******************************************************************
 Title:getAddr
 Function:return the place of file mappint in memory
 Input:
 Output:MVFReturnHandle
******************************************************************/
ADDRINT getAddr()
{
	return MVFdata[0].MVFReturnHandle;
}
/******************************************************************
 Title:getSizeH
 Function:return the high bit of size of file
 Input:
 Output:sizeHigh
******************************************************************/
ADDRINT getSizeH()
{
	return MVFdata[0].FileMappingdata->sizeHigh;
}
/******************************************************************
 Title:getSizeL
 Function:return the low bit of size of file
 Input:
 Output:sizeLow
******************************************************************/
ADDRINT getSizeL()
{
	return MVFdata[0].FileMappingdata->sizeLow;
}
 

