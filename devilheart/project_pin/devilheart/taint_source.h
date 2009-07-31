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