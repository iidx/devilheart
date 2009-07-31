/*******************************************************************
 Title:TaintSource.cpp
 Function:to find the taintsource in program and record the in memory
 Description:
 Define some data structors to record the state of memory in size of
 4G at most.
 Version: 1.1
 Date and author: 2009.07.24 ethenjean
*******************************************************************/

#include "pin.H"
#include <iostream>
#include <fstream>

namespace WINDOWS
{
#include <windows.h>
}

/******************************************************************
 define the function name that when notepad.exe open a file 
 they are createfile createfilemapping mapviewoffile
******************************************************************/
#ifdef UNICODE
#define CreateFileMapping "CreateFileMappingW"
#else
#define CreateFileMapping "CreateFileMappingA"
#endif
#define CreateFile "CreateFileW"
#define MapViewOfFile "MapViewOfFile"
#define MapViewOfFileEx "MapViewOfFileEx"

#define FileName	"filename.txt"

/******************************************************************
 get the number of bytes of  tainted source
******************************************************************/
long getBytes();

/******************************************************************
 get the start address of tainted source mapping in memory
******************************************************************/
ADDRINT getAddr();