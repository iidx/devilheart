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


/* ===================================================================== */
/* Analysis routines                                                     */
/* ===================================================================== */
 
VOID FindObjectByName(wchar_t *name)
{
    
	//用于比较文件名的字符串
	string NameStr="";
	//记录原指针
	wchar_t* name0=name;
	//将字符串内容读入NameStr以便比较
	for(;*name!='\0';name++)
	{
		NameStr+=*name;
	}
    //记录原指针
	name=name0;
    //如果确认读入目标文件则进行处理
	if(NameStr.find(FILE_NAME)!=string::npos)
	{
        int i;
        //找到第一个未用结构的位置
        for(i=0;CFWdata[i].sign !=0;i++)
            ;
        //将返回值设置为-2，作为标记通知此处应该赋返回值
        CFWdata[i].CFWHandle = -2;
        CFWdata[i].sign = 1;
        CFWdata[i+1].sign = 0;
	}
}
VOID SetCFWReturnValue(ADDRINT fileHandle)
{
    //记录CreateFileW的返回值
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

VOID FindMatchingCFMW(ADDRINT hfile,ADDRINT offsethigh,ADDRINT offsetlow)
{

    //判断CreateFileMapping参数是否与CreateFileW返回值匹配，如匹配则进行处理
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
VOID SetCFMWReturnValue(UINT32 mappingHandle)
{

	//对每个标志位不为0的CFMWdata进行扫描，找到handle被标志为-2的那个进行赋值
    int i;
    for(i=0;CFMWdata[i].sign!=0;i++)
    {
        if(CFMWdata[i].CFMWHandle == -2)
        {
            CFMWdata[i].CFMWHandle = mappingHandle;
        }
    }
}
VOID FindMachingMVF(ADDRINT mappingHandle)
{

	//找到匹配的MapViewOfFile进行赋值和标记
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
VOID SetMappingBase(ADDRINT base)
{
	
	//搜索数组，找到被标记的结构进行赋值
    int i;
    for(i=0;MVFdata[i].sign!=0;i++)
    {
		if(MVFdata[i].MVFReturnHandle==-2){
            MVFdata[i].MVFReturnHandle=base;
			flag=1;
			fprintf(output,"****************************************************\n");
			fprintf(output,"Before the application\n");
			memManager->printState(output);
		}
    }
	
}

ADDRINT getAddr()
{
	return MVFdata[0].MVFReturnHandle;
}

ADDRINT getSizeH()
{
	return MVFdata[0].FileMappingdata->sizeHigh;
}

ADDRINT getSizeL()
{
	return MVFdata[0].FileMappingdata->sizeLow;
}
 

