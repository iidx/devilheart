/*******************************************************************
 Title:TaintSource.cpp
 Function:to find the taintsource in program and record the in memory
 Description:
 Define some data structors to record the state of memory in size of
 4G at most.
 Version: 1.1
 Date and author: 2009.07.24 ethenjean
*******************************************************************/

#include "TaintSource.h"



/******************************************************************
 some global values
******************************************************************/
long bytes;

ADDRINT addr;

std::ofstream TraceFile;

WINDOWS::HANDLE mappinghandle;

WINDOWS::HANDLE createhandle;


/******************************************************************
 command lines
******************************************************************/

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "TaintSourceInfo.out", "specify trace file name");


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
 Title:getBytes
 Function:return the number of tainted bytes 
 Input: 
 Output: 
******************************************************************/
 
long getBytes()
{
	return bytes;
}

/******************************************************************
 Title:Createfile
 Function:return the start address of tainted source
 Input: 
 Output: 
******************************************************************/
ADDRINT getAddr()
{
	return addr;
}

/******************************************************************
 Title:Createfile
 Function:to find the filename and generated handle,then record them
 Input: 
 LPCTSTR:name   path of the file that will be opened
 HANDLE: hfile  the handle createfile generated
 Output: print out the info to log file
******************************************************************/
VOID Createfile(WINDOWS::LPCTSTR  name,WINDOWS::HANDLE hfile)
{
	//get entire filename from path
	string sourcepath="";
	
	for(;*name!='0';name++)
	{
		sourcepath+=*name;
		if( *name=='\\')
			sourcepath="";
	}

	//remove blank from filename
	char c=sourcepath.at(0);
	string file="";
	
	for(int i=0;i<sourcepath.length();i++)
	{
		if(sourcepath.at(i)!=c)
			file+=sourcepath.at(i);
	}

	//get the real file name
	string sour=FileName;
	int size=sour.length();
	
	string filename=file.substr(0,size);

	//record the target file info
	if(filename==FileName)
	{
		createhandle=hfile;
		TraceFile<<"*****get the target file*****"<<endl<<filename<<endl;
		TraceFile<<"Create Handle:"<<hfile<<endl;
		TraceFile<<"Source Handle:"<<createhandle<<endl;
	}
}

/******************************************************************
 Title:Createfilemapping
 Function:find the handle that match with the target handle
 Input:
 HANDLE:chandle the source handle created by creatfile
 HANDLE:mhandle the handle that createfilemapping created
 Output:print out the info to log file
******************************************************************/

VOID Createfilemapping(WINDOWS::HANDLE chandle,WINDOWS::LPCTSTR  name,WINDOWS::HANDLE mhandle)
{	

	TraceFile<<"Source Create Handle:"<<createhandle<<endl;
	TraceFile<<"Current Create Handle:"<<chandle<<endl;
	string sourcepath="";

	TraceFile<<"filename:"<<name<<endl;
	
	if(chandle==createhandle)
	mappinghandle=mhandle;
	TraceFile << "Content:createfilemapping handle:"<<mhandle << endl;
}

/******************************************************************
 Title:Mapviewoffile
 Function:find the mapping handle that match with the target handle
 Input:
 HANDLE:mhandle the source handle created by createfilemapping
 long:num		the number of bytes mapped from file to memory
 ADDRINT:ret	the start address that mapping to file
 Output:	printout the info to log file
******************************************************************/

VOID Mapviewoffile(WINDOWS::HANDLE mhandle,long num,ADDRINT ret)
{	
	TraceFile<<"Source Mapping Handle:"<<mappinghandle<<endl;
	TraceFile<<"Current Mapping Handle:"<<mhandle<<endl;
	if(mappinghandle==mhandle)
	{
		bytes=num;
		addr=ret;
	}
	if(num>0){
		bytes=num;
		addr=ret;
	}
	TraceFile << "Content:mapviewoffile bytes:"<<num<<" addr:" <<ret<<endl;
}

/******************************************************************
 Title:Image
 Function:insert call to program as image
 Input:
 IMG:img  the image that will be inserted
 Void:*v  usually set to 0
 Output:
******************************************************************/
   
VOID Image(IMG img, VOID *v)
{
    
    //  Find the createfile function.
    RTN mallocRtn = RTN_FindByName(img, CreateFile);
    if (RTN_Valid(mallocRtn))
    {
        RTN_Open(mallocRtn);
        RTN_InsertCall(mallocRtn, IPOINT_BEFORE, (AFUNPTR)Createfile,
                       IARG_FUNCARG_ENTRYPOINT_VALUE,0,//the first argument
					   IARG_FUNCRET_EXITPOINT_VALUE,//the return value
                       IARG_END);
        RTN_Close(mallocRtn);
    }
    
	//find the createfilemapping function
	mallocRtn = RTN_FindByName(img, CreateFileMapping);
    if (RTN_Valid(mallocRtn))
    {
		RTN_Open(mallocRtn);

	   
		RTN_InsertCall(mallocRtn, IPOINT_BEFORE, (AFUNPTR)Createfilemapping,
					   IARG_FUNCARG_ENTRYPOINT_VALUE,0,//the first argument
					   IARG_FUNCARG_ENTRYPOINT_VALUE,5,
					   IARG_FUNCRET_EXITPOINT_VALUE,//the return value
					   IARG_END);
		RTN_Close(mallocRtn);
	}

	//find the mapviewoffile function
	mallocRtn = RTN_FindByName(img, MapViewOfFile);
    if (RTN_Valid(mallocRtn))
    {
        RTN_Open(mallocRtn);

        
        RTN_InsertCall(mallocRtn, IPOINT_BEFORE, (AFUNPTR)Mapviewoffile,
						IARG_FUNCARG_ENTRYPOINT_VALUE,0,//the first argument
					   IARG_FUNCARG_ENTRYPOINT_VALUE,4,//the fifth argument
                       IARG_FUNCRET_EXITPOINT_VALUE,//the return value
                       IARG_END);
        RTN_Close(mallocRtn);
    }
	mallocRtn = RTN_FindByName(img, MapViewOfFileEx);
    if (RTN_Valid(mallocRtn))
    {
        RTN_Open(mallocRtn);

        
        RTN_InsertCall(mallocRtn, IPOINT_BEFORE, (AFUNPTR)Mapviewoffile,
						IARG_FUNCARG_ENTRYPOINT_VALUE,0,//the first argument
					   IARG_FUNCARG_ENTRYPOINT_VALUE,4,//the fifth argument
                       IARG_FUNCRET_EXITPOINT_VALUE,//the return value
                       IARG_END);
        RTN_Close(mallocRtn);
    }
}

/******************************************************************
 Title:Fini
 Function:when program exit thie will be called
 Input:
 Output:
******************************************************************/
 
VOID Fini(INT32 code, VOID *v)
{
	TraceFile<<"Address:"<<addr<<endl;
	TraceFile<<"Bytes:"<<bytes<<endl;
    TraceFile.close();
}

/******************************************************************
 Title:Image
 Function:insert call to program as image
 Input:
 IMG:img  the image that will be inserted
 Void:*v  usually set to 0
 Output:
******************************************************************/
 
int main(int argc, char *argv[])
{
    // Initialize pin & symbol manager
    PIN_InitSymbols();
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }
    
    // Write to a file since cout and cerr maybe closed by the application
    TraceFile.open(KnobOutputFile.Value().c_str());
    TraceFile << hex;
    TraceFile.setf(ios::showbase);
    
    // Register Image to be called to instrument functions.
    IMG_AddInstrumentFunction(Image, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}

