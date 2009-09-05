/*******************************************************************
 Title:TaintSource.cpp
 Function:to find the taintsource in program and record the in memory
 Description:
 Define some data structors to record the state of memory in size of
 4G at most.
 Version: 1.1
 Date and author: 2009.07.24 ethenjean
*******************************************************************/

#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include "pin.H"
#include <iostream>

/*define the file name*/ 
#define FILE_NAME "333.txt"

/*the flag of tainted source*/
int flag=0;

/*record the size of file*/
ADDRINT sizeH;
ADDRINT sizeL;

/*record the base address of file mapping to memory*/
ADDRINT baseaddr;

/*record the data of function CreatFileW*/
struct CreateFileWData
{
	int sign ;				// flag 
	ADDRINT CFWHandle;		// return value
};

CreateFileWData CFWdata[50];

//record the data of function CreateFileMappingW
struct CreateFileMappingWData
{
	int sign ;				// flag
	ADDRINT CFMWHandle;		// return value
	ADDRINT sizeHigh;		// high 8 bit of file size
	ADDRINT sizeLow;		// low  8 bit of file size
    CreateFileWData * Filedata;// point to CreateFileW
};
CreateFileMappingWData CFMWdata[50];

//record the data of function MapViewOfFile
struct MapViewOfFileData
{
	int sign ;				// flag
	ADDRINT MVFReturnHandle;// return value
    CreateFileMappingWData * FileMappingdata;// point to CreateFileMappingW
};
MapViewOfFileData MVFdata[50];


/*find the handle match with the aim file name and sign the CreateFileW to -2*/
VOID FindObjectByName(wchar_t *name);

/*set the CreateFileWData which handle value is -2 to filehandle*/
VOID SetCFWReturnValue(ADDRINT fileHandle);

/*find if the args of hfile match with the return value of function CreateFileW and do some process*/
VOID FindMatchingCFMW(ADDRINT hfile,ADDRINT offsethigh,ADDRINT offsetlow);

/*set the CreateFileMappintW which value is -2 to mappingHandle*/
VOID SetCFMWReturnValue(UINT32 mappingHandle);

/*find the matching CreateFileMappintW data and sign */
VOID FindMachingMVF(ADDRINT mappingHandle);

/*set the MapViewOfFile data which value is -2 to base*/
VOID SetMappingBase(ADDRINT base);

/*get the base address of file*/
ADDRINT getAddr();

/*get the high 8 bit of memory of file*/
ADDRINT getSizeH();

/*get the low 8 bit of memory of file*/
ADDRINT getSizeL();

